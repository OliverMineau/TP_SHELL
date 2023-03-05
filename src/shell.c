/*
 * Copyright (C) 2002, Simon Nieuviarts
 */

#include "shell.h"

Jobs *jobs=NULL;


int gestionCommande(struct cmdline *l, Jobs **jobs){
	int i;

	#if DEBUG
	if (l->in) printf("in: %s\n", l->in);
	if (l->out) printf("out: %s\n", l->out);
	printf("background: %d\n",l->bg);
	#endif

	/* Display each command of the pipe */
	//Calcule le nombre de commandes
	for (i=0; l->seq[i]!=0; i++) {

		#if DEBUG 
		char **cmd = l->seq[i];
		printf("seq[%d]: ", i);
		for (int j=0; cmd[j]!=0; j++) {
			printf("%s ", cmd[j]);
			
		}
		printf("\n");
		#endif
	}
	#if DEBUG
	printf("Nombre de commandes : %d\n",i);
	#endif

	/**pipes contient prevCmdPipe et nextCmdPipe respectivement :
	 * - le lien entre la commande precedente et la commande actuelle
	 * - le lien entre la commande actuelle et la commande suivante
	 * 
	 * pipe[0] - On lit de là
	 * pipe[1] - On ecrit dessu
	 */
	int pipes[2][2];
	int *prevCmdPipe = pipes[0];
	int *nextCmdPipe = pipes[1];

	//Pour chaque commande
	for(int n = 0; n<i; n++){
		
		int resCmdInt = commandeInterne(l,n, jobs, l->out,pipes,(n==0?1:0),(n==(i-1)?1:0)==1);
		if(resCmdInt==0){
			//Pas une commande interne
			if(commandeExterne(l,n,pipes, (n==0?1:0),(n==(i-1)?1:0),jobs)==1) break;
		}
		//Commande interne qui ne peut pas etre suivie
		else if(resCmdInt==-1) break;
		
		
		//Si on a plus d'une commande, on créer un nouveau pipe et déplace l'ancien
		if(n+1 < i){
			
			//Deplace l'ancien pipe
			prevCmdPipe[0]=nextCmdPipe[0];
			prevCmdPipe[1]=nextCmdPipe[1];

			//On cree un pipe seulement si ce n'est pas la derniere commande
			if(n+1!=i && pipe(nextCmdPipe)==-1){
				fprintf(stderr,"Erreur lors de l'ouverture du pipe\n");
				return 1;
			}
			
		}

	}

	return 0;
}

int main()
{

	Signal(SIGCHLD,childHandler);
	Signal(SIGINT,ctrlCHandler);
	Signal(SIGTSTP,ctrlZHandler);

	while (1) {
		struct cmdline *l;

		//Affiche ~Documents/GitHub/TP_SHELL$ (selon la machine)
		printShellEnv();
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
		
		gestionCommande(l,&jobs);

		while(jobEnFG(jobs)){
			sleep(1);
		}

		#if DEBUG
		printJobs(jobs);
		#endif
	}
	exit(0);
}