
#include <stdio.h>
#include "readcmd.h"
#include "csapp.h"
#include "redirection.h"
#include "externCmd.h"
#include "jobs.h"

void seqToChar(struct cmdline *l, char *nomCommande){
	nomCommande[0]='\0';
	int i = 0;
	/*Pour chaque commande*/
	while (l->seq[i])
	{
		int j=0;
		/*Pour chaque argument*/
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

	/*Cherche si on a des redirections d'entrées/sorties*/
	if(redirectionEntree(inNom, prevCmdPipe, deb, &fd_in)==1) return 1;
	if(redirectionSortie(outNom, nextCmdPipe, fin, deb, &fd_out)==1) return 1;

	if((pid=Fork()) == 0){
		/*Fils*/

		if(execvp(cmd[0], cmd)==-1){
			/*-1 si commande pas executée*/
			fprintf(stderr,"%s: command not found\n",cmd[0]);
			exit(0);
		}

	}else{
		/*Pere*/

		/*Replace les entrées/sorties standard*/
		dup2(fd_term,1);
		dup2(fd_term,0);
		Close(fd_term);

		/*Si c'est la derniere commande de la sequence*/
		if(fin){
			
			/*Prendre la sequence de commandes totale*/
			char nomCommande[200];
			seqToChar(l,nomCommande);

			/*Si elle est executée en arriere plan, ajout dans les jobs et affichage*/
			if(bg){
				addJob(jobs,nomCommande,pid,RUNNING,BACKGROUND);
				printf("[%d] %d\n",(*jobs)->num,(*jobs)->pid);
			}else{
				/*Sinon, ajout dans les jobs*/
				addJob(jobs,nomCommande,pid,RUNNING,FOREGROUND);
			}

		}
		

	}

	return 0;
}