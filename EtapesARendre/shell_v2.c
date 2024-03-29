/*
 * Copyright (C) 2002, Simon Nieuviarts
 */

#include <stdio.h>
#include <stdlib.h>
#include "readcmd.h"
#include "csapp.h"

#define BUFSIZE 1000

void quitShell(char **cmd){
	if(!strcmp("exit",cmd[0]) || !strcmp("quit",cmd[0])){
		exit(0);
	}
}


void commande(char **cmd, char *inNom, char *outNom, int *tube, int debut,int fin){
	int pid;
	int fd_out,fd_in;
	int fd_term = dup(1);

	//Si on redirige la sortie
	if(outNom && fin == 1){

		//O_CREAT=Creer le fichier si inexistant
		//0666 permission RDWR pour tout le mondech 
		fd_out = open(outNom, O_CREAT | O_RDWR, 0666);

		if(fd_out==-1){
			if(errno == EACCES){
				fprintf(stderr,"%s: Permission denied.\n", outNom);
			} else {
				fprintf(stderr,"%s: No such file or directory\n",outNom);	
			}
			return;
		}
		if(dup2(fd_out,1)==-1){
			fprintf(stderr,"Erreur de copie de la sortie\n");
			return;
		}
	}else if (fin == 0){

		if(dup2(tube[1],1)==-1){
			fprintf(stderr,"Erreur de copie de la sortie\n");
			return;
		}
		Close(tube[1]);
	}

	//Si on redirige l'entrée
	if(inNom && debut == 1){

		fd_in = open(inNom, O_RDONLY);

		if(fd_in==-1){
			fprintf(stderr,"%s: No such file or directory\n",inNom);
			return;
		}
		if(dup2(fd_in,0)==-1){
			fprintf(stderr,"Erreur de copie de l'entrée\n");
			return;
		}
	}else if (debut == 0){
		if(dup2(tube[0],0)==-1){
			fprintf(stderr,"Erreur de copie de l'entrée\n");
			return;
		}
		Close(tube[0]);
	}

	if((pid=Fork()) == 0){

		if(inNom && debut==1){
			Close(fd_in);
		}
		if(outNom && fin==1){
			Close(fd_out);
		}

		if(debut == 1){
			Close(tube[0]);
		}
		if(fin == 1){
			Close(tube[1]);
		}

		execvp(cmd[0], cmd);

		//execvp(cmd[0], cmd) == -1 si commande pas executée
		fprintf(stderr,"%s: command not found\n",cmd[0]);
		exit(0);

	}else{

		Waitpid(pid,NULL,0);

		//On ferme fd_out et ajoute le terminal en sortie
		if(outNom && fin==1){
			Close(fd_out);
		}
		dup2(fd_term,1);

		//On ferme fd_in et ajoute le terminal en entrée
		if(inNom && debut==1){
			Close(fd_in);
		}
		dup2(fd_term,0);
		Close(fd_term);

	}
}

int main()
{
	while (1) {
		struct cmdline *l;
		int i, j;

		printf("shell> ");
		l = readcmd();

		/* If input stream closed, normal termination */
		if (!l) {
			printf("exit\n");
			exit(0);
		}

		if (l->err) {
			/* Syntax error, read another command */
			printf("error: %s\n", l->err);
			continue;
		}

		if (l->in) printf("in: %s\n", l->in);
		if (l->out) printf("out: %s\n", l->out);

		/* Display each command of the pipe */
		for (i=0; l->seq[i]!=0; i++) {
			char **cmd = l->seq[i];
			printf("seq[%d]: ", i);

			for (j=0; cmd[j]!=0; j++) {
				printf("%s ", cmd[j]);
			}
			printf("\n");

		}

		printf("Nombre de commandes : %d\n",i);

		int tube[2];
		if(pipe(tube)==-1){
			fprintf(stderr,"Erreur lors de l'ouverture du pipe\n");
			return 1;
		}

		//Pour chaque commande
		for(int n = 0; n<(i>2?2:i); n++){
			
			quitShell(l->seq[n]);
			commande(l->seq[n], l->in, l->out,tube,(n==0?1:0),(n==i-1?1:0));

		}


	}
}