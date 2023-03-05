
#include <stdio.h>
#include "csapp.h"
#include "redirection.h"

#define BUFSIZE 200

int redirectionEntree(char *inNom, int *prevCmdPipe, int deb, int *fd_in){
	/*Si on redirige l'entrée*/
	if(inNom && deb==1){

		*fd_in = open(inNom, O_RDONLY);

		if(*fd_in==-1){
			printf("%s: %s\n",inNom,strerror(errno));
			return 1;
		}

		/*On redirige l'entree standard vers le descripteur de fichier du fichier*/
		if(dup2(*fd_in,0)==-1){
			fprintf(stderr,"Erreur de copie de l'entrée\n");
			return 1;
		}

	}else if (deb==0){
		/*On redirige l'entree standard vers la sortie de la commande precedente*/
		if(dup2(prevCmdPipe[0],0)==-1){
			fprintf(stderr,"Erreur de copie de l'entrée\n");
			return 1;
		}
		Close(prevCmdPipe[0]);
	}

	return 0;
}


int redirectionSortie(char *outNom, int *nextCmdPipe, int fin, int deb, int *fd_out){
	/*Si on redirige la sortie*/
	
	if(outNom && fin==1){

		/*O_CREAT=Creer le fichier si inexistant
		0666 permission RDWR pour tout le mondech */
		*fd_out = open(outNom, O_CREAT | O_RDWR, 0666);

		if(*fd_out==-1){
			if(errno == EACCES){
				fprintf(stderr,"%s: Permission denied.\n", outNom);
				exit(1);
			}
			printf("%s: %s\n",outNom,strerror(errno));
			return 1;
		}

		/*Redirige la sortie standard vers le descripteur de fichier du fichier*/
		if(dup2(*fd_out,1)==-1){
			fprintf(stderr,"Erreur de copie de la sortie\n");
			return 1;
		}

	}else if (fin==0){

		/*Si c'est la premiere commande et pas la derniere*/
		if(deb==1 && pipe(nextCmdPipe)==-1){
			fprintf(stderr,"Erreur lors de l'ouverture du pipe\n");
			return 1;
		}

		/*la sortie devient nextCmdPipe[1](entree tube)*/
		if(dup2(nextCmdPipe[1],1)==-1){
			fprintf(stderr,"Erreur de copie de l'sortie\n");
			return 1;
		}
		Close(nextCmdPipe[1]);
	}

	return 0;
}
