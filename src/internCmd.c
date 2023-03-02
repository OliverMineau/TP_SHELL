
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "readcmd.h"
#include "csapp.h"
#include "internCmd.h"
#include "readcmd.h"
#include "jobs.h"
#include "redirection.h"


void printShellEnv(){
	/**Trouver le Current Working Directory
	 * strlen(getenv("HOME")) : on trouve la taille de l'env et affiche apres
	 */
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	int lenHome=strlen(getenv("HOME"));
	if(strlen(cwd)>=lenHome)
		printf("~%s$ ",cwd+lenHome);
	else
		printf("%s$ ",cwd);
}

void isQuitShell(struct cmdline *cmd, int n){
	if(!strcmp("exit",cmd->seq[n][0]) || !strcmp("quit",cmd->seq[n][0])){
		exit(0);
	}
}

int isChangeDir(struct cmdline *cmd, int n){
	if(!strcmp("cd",cmd->seq[n][0])){
		char path[1024];

		if(cmd->seq[n][1]==NULL || !strcmp(cmd->seq[n][1],"~")){
			strcpy(path,getenv("HOME"));
		}else{
			strcpy(path,cmd->seq[n][1]);
		}

		if(chdir(path)==-1){
			fprintf(stderr,"cd: %s: No such file or directory\n",cmd->seq[n][1]);
		}
		return 1;
	}
	return 0;
}

int isJobs(struct cmdline *cmd, int n, Jobs *jobs){
	if(!strcmp("jobs",cmd->seq[n][0])){
		printJobs(jobs);
		return 1;
	}
	return 0;
}

int isFg(struct cmdline *cmd, int n, Jobs *jobs){

	if(!strcmp("fg",cmd->seq[n][0])){
		Jobs *job;
		if((job=findJobNameNum(jobs,cmd->seq[n][1]))){

			job->ground=FOREGROUND;
			job->state=RUNNING;
			printf("%s\n",job->name);
			Kill(job->pid,SIGCONT);
		}else{
			printf("fg: current: no such job\n");
		}
		return 1;
	}
	return 0;
}

int commandeInterne(struct cmdline *cmd, int n, Jobs *jobs, char *outNom, int pipes[2][2], int deb, int fin){

    isQuitShell(cmd, n);

	/*int fd_out;
	int fd_term = dup(1);

	int *nextCmdPipe = pipes[1];
	
	int sortieOuverte = (outNom && fin==1);

	if(redirectionSortie(outNom, nextCmdPipe, fin, deb, &fd_out)==1) return -1;*/


	int isCd = isChangeDir(cmd, n);
	int isJ = isJobs(cmd, n, jobs);
	int isF = isFg(cmd, n, jobs);


/*
	//On ferme fd_out si on l'a ouvert et ajoute le terminal en sortie
	if(sortieOuverte){
		Close(fd_out);
	}
	dup2(fd_term,1);
	Close(fd_term);*/

	if(isCd) return -1; //Aucune commande ne peut suivre cd
	if(isJ) return 1; //Commande peut etre suivie
	if(isF) return -1; //Aucune commande ne peut suivre fg

	return 0;
}