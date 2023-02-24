
#include <stdio.h>
#include "csapp.h"
#include "redirection.h"

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
