
#include <stdio.h>
#include "readcmd.h"
#include "csapp.h"
#include "redirection.h"
#include "externCmd.h"
#include "jobs.h"

void seqToChar(struct cmdline *l, char *nomCommande){
	nomCommande[0]='\0';
	int i = 0;
	while (l->seq[i])
	{
		int j=0;
		while (l->seq[i][j])
		{
			strcat(nomCommande,l->seq[i][j]);
			strcat(nomCommande," ");
			j++;
		}
		i++;
	}
}

int commandeExterne(struct cmdline *l, int n, int pipes[2][2], int deb, int fin, Jobs **jobs){
	int pid;
	int fd_out,fd_in;

	char *inNom=l->in;
	char *outNom=l->out;
	char **cmd=l->seq[n];
	int bg=l->bg;

	int fd_term = dup(1);

	int *prevCmdPipe = pipes[0];
	int *nextCmdPipe = pipes[1];

	if(redirectionEntree(inNom, prevCmdPipe, deb, &fd_in)==1) return 1;
	if(redirectionSortie(outNom, nextCmdPipe, fin, deb, &fd_out)==1) return 1;

	if((pid=Fork()) == 0){
		//Fils

		if(execvp(cmd[0], cmd)==-1){
			//execvp(cmd[0], cmd) == -1 si commande pas executée
			fprintf(stderr,"%s: command not found\n",cmd[0]);
			exit(0);
		}

	}else{
		//Pere

		dup2(fd_term,1);
		dup2(fd_term,0);
		Close(fd_term);

		if(fin){

			char nomCommande[200];
			seqToChar(l,nomCommande);

			if(bg){
				addJob(jobs,nomCommande,pid,RUNNING,BACKGROUND);
				printf("[%d] %d\n",(*jobs)->num,(*jobs)->pid);
			}else{
				addJob(jobs,nomCommande,pid,RUNNING,FOREGROUND);
			}

		}
		

	}

	return 0;
}