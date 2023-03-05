
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
	 * getcwd donne le chemin complet, on enleve le chemin de home avec
	 * strlen(getenv("HOME")) : on trouve la taille de l'env et affiche a partir de là*/
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	int lenHome=strlen(getenv("HOME"));
	if(strlen(cwd)>=lenHome)
		printf("~%s$ ",cwd+lenHome);
	else
		printf("%s$ ",cwd);
}

void isQuitShell(struct cmdline *cmd, int n){
	/*exit/quit*/
	if(!strcmp("exit",cmd->seq[n][0]) || !strcmp("quit",cmd->seq[n][0])){
		exit(0);
	}
}

int isChangeDir(struct cmdline *cmd, int n){
	/*cd*/
	if(!strcmp("cd",cmd->seq[n][0])){
		char path[1024];

		/*~*/
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
	/*jobs*/
	if(!strcmp("jobs",cmd->seq[n][0])){
		printJobs(jobs);
		return 1;
	}
	return 0;
}

int isFg(struct cmdline *cmd, int n, Jobs *jobs){
	/*fg*/
	if(!strcmp("fg",cmd->seq[n][0])){
		Jobs *job;

		/*On cherche le job*/
		if((job=findJobNameNum(jobs,cmd->seq[n][1]))){
			job->ground=FOREGROUND;
			job->state=RUNNING;
			printf("%s\n",job->name);
			/*Redemarre le processus*/
			Kill(job->pid,SIGCONT);

		}else if(cmd->seq[n][1]!=NULL){
			printf("fg: %s: no such job\n",cmd->seq[n][1]);

		}else{
			printf("fg: current: no such job\n");
		}
		return 1;
	}
	return 0;
}

int isBg(struct cmdline *cmd, int n, Jobs *jobs){
	/*bg*/
	if(!strcmp("bg",cmd->seq[n][0])){
		Jobs *job;
		/*On cherche le job*/
		if((job=findJobNameNum(jobs,cmd->seq[n][1]))){
			job->ground=BACKGROUND;
			job->state=RUNNING;
			printf("[%d]+ %s &\n",job->num,job->name);
			/*Redemarre le processus*/
			Kill(job->pid,SIGCONT);

		}else if(cmd->seq[n][1]!=NULL){
			printf("bg: %s: no such job\n",cmd->seq[n][1]);
			
		}else{
			printf("bg: current: no such job\n");
		}
		return 1;
	}
	return 0;
}

int commandeInterne(struct cmdline *cmd, int n, Jobs **jobs, char *outNom, int pipes[2][2], int deb, int fin){

    isQuitShell(cmd, n);

	if(isChangeDir(cmd, n)) return -1; //Aucune commande ne peut suivre cd
	if(isJobs(cmd, n, *jobs)) return 1; //Commande peut etre suivie
	if(isFg(cmd, n, *jobs)) return -1; //Aucune commande ne peut suivre fg
	if(isBg(cmd, n, *jobs)) return -1; //Aucune commande ne peut suivre bg


	return 0;
}