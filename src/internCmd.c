
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "internCmd.h"
#include "readcmd.h"


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

int commandeInterne(struct cmdline *cmd, int n){

    isQuitShell(cmd, n);
	
	if(isChangeDir(cmd, n)) return -1; //Aucune commande ne peut suivre cd

	return 0;
}