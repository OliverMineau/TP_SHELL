
#include <stdio.h>
#include "readcmd.h"
#include "csapp.h"
#include "redirection.h"
#include "externCmd.h"

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
		//Fils

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
		//Pere

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

		//Si c'est une commande du milieu on ferme l'entree du pipe de la commande precedente
		if(deb==0 && fin==0){
			Close(prevCmdPipe[1]);
		}
	}
}