/*
 * Copyright (C) 2002, Simon Nieuviarts
 */

#include <stdio.h>
#include <stdlib.h>
#include "readcmd.h"
#include "csapp.h"


void quitShell(char **cmd){
	if(!strcmp("exit",cmd[0]) || !strcmp("quit",cmd[0])){
		exit(0);
	}
}

void redirectionEntree(char *inNom, int *prevCmdPipe, int deb, int *fd_in){
	//Si on redirige l'entrée
	if(inNom && deb==1){

		*fd_in = open(inNom, O_RDONLY);

		if(*fd_in==-1){
			fprintf(stderr,"%s: No such file or directory\n",inNom);
			return;
		}
		if(dup2(*fd_in,0)==-1){
			fprintf(stderr,"Erreur de copie de l'entrée\n");
			return;
		}
	}else if (deb==0){

		//l'entree devient pipeP[0](sortie tube) car on a ecrit depuis pipeP[1](entree tube)
		if(dup2(prevCmdPipe[0],0)==-1){
			fprintf(stderr,"Erreur de copie de l'entrée\n");
			return;
		}
		Close(prevCmdPipe[0]);
	}
}


void redirectionSortie(char *outNom, int *nextCmdPipe, int fin, int *fd_out){
	//Si on redirige la sortie
	if(outNom && fin==1){

		//O_CREAT=Creer le fichier si inexistant
		//0666 permission RDWR pour tout le mondech 
		*fd_out = open(outNom, O_CREAT | O_RDWR, 0666);

		if(*fd_out==-1){
			fprintf(stderr,"%s: No such file or directory\n",outNom);
			return;
		}
		if(dup2(*fd_out,1)==-1){
			fprintf(stderr,"Erreur de copie de la sortie\n");
			return;
		}
	}else if (fin==0){

		if(pipe(nextCmdPipe)==-1){
			fprintf(stderr,"Erreur lors de l'ouverture du pipe\n");
			return;
		}

		//la sortie devient pipeActu[1](entree tube)
		if(dup2(nextCmdPipe[1],1)==-1){
			fprintf(stderr,"Erreur de copie de l'entrée\n");
			return;
		}
		Close(nextCmdPipe[1]);
	}
}

void commande(char **cmd, char *inNom, char *outNom, int pipes[2][2], int deb, int fin){
	int pid;
	int fd_out,fd_in;
	int fd_term = dup(1);

	int *prevCmdPipe = pipes[0];
	int *nextCmdPipe = pipes[1];
	
	int entreeOuverte = (inNom && deb==1);
	int sortieOuverte = (outNom && fin==1);

	redirectionEntree(inNom, prevCmdPipe, deb, &fd_in);
	redirectionSortie(outNom, nextCmdPipe, fin, &fd_out);

	if((pid=Fork()) == 0){

		if(entreeOuverte){
			Close(fd_in);
		}
		if(sortieOuverte){
			Close(fd_out);
		}
		if(deb==0){
			Close(prevCmdPipe[1]);
		}

		if(execvp(cmd[0], cmd)==-1){
			//execvp(cmd[0], cmd) == -1 si commande pas executée
			fprintf(stderr,"%s: command not found\n",cmd[0]);
			exit(0);
		}

	}else{

		Waitpid(pid,NULL,0);

		//On ferme fd_out si on l'a ouvert et ajoute le terminal en sortie
		if(sortieOuverte){
			Close(fd_out);
		}
		dup2(fd_term,1);

		//On ferme fd_in si on l'a ouvert et ajoute le terminal en entrée
		if(entreeOuverte){
			Close(fd_in);
		}
		dup2(fd_term,0);
		Close(fd_term);

		if(deb==0 && fin==0){
			Close(prevCmdPipe[1]);
		}
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
			//printf("seq[%d]: ", i);

			for (j=0; cmd[j]!=0; j++) {
				//printf("%s ", cmd[j]);
			}
			//printf("\n");
		}
		//printf("Nombre de commandes : %d\n",i);


		/**
		 * pipe[0] - On lit de là
		 * pipe[1] - On ecrit dessu
		 */

		/**pipes contient prevCmdPipe et nextCmdPipe respectivement :
		 * - le lien entre la commande precedente et la commande actuelle
		 * - le lien entre la commande actuelle et la commande suivante
		 */
		int pipes[2][2];
		int *prevCmdPipe = pipes[0];
		int *nextCmdPipe = pipes[1];

		if(i>1 && pipe(prevCmdPipe)==-1){
			fprintf(stderr,"Erreur lors de l'ouverture du pipe\n");
			return 1;
		}

		//Pour chaque commande
		for(int n = 0; n<i; n++){
			
			quitShell(l->seq[n]);
			commande(l->seq[n], l->in, l->out,pipes, (n==0?1:0),(n==(i-1)?1:0));

			//Si on a plus d'une commande, on créer un nouveau pipe et déplace l'ancien
			if(n < i-1){
				
				//Deplace l'ancien pipe
				prevCmdPipe[0]=nextCmdPipe[0];
				prevCmdPipe[1]=nextCmdPipe[1];

				if(pipe(nextCmdPipe)==-1){
					fprintf(stderr,"Erreur lors de l'ouverture du pipe\n");
					return 1;
				}
				
			}
		}


	}
}