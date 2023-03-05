#include "signalHandlers.h"
#include <stdio.h>
#include "jobs.h"
#include "csapp.h"
#include "readcmd.h"



void childHandler(int signum){

	int pid;
	/*Tant qu'un processus fils est mort*/
	while((pid=waitpid(-1,NULL,WNOHANG|WUNTRACED))>0){
		Jobs *job;
		/*Chercher s'il fait parti des jobs*/
		if((job=findJobByPID(jobs,pid))){
			
			/*Si le processus est stoppé on ne fait rien*/
			if(job->state==STOPPED) return;

			/*Si le processus est en arriere plan*/
			if(job->ground==BACKGROUND){
				printf("[%d]+ Done                    %s\n",job->num,job->name);
			}

			deleteJob(&jobs,job);
		}
	}
}

void ctrlCHandler(int sig){
	printf("\n");
}

void ctrlZHandler(int sig){
	printf("\n");

	Jobs *job;
	/*Si un job est en premier plan*/
	if((job=findJobInFG(jobs))!=NULL){
		/*Passage en arriere plan stoppé*/
		job->ground=BACKGROUND;
		job->state=STOPPED;
		printf("[%d]+  Stopped                 %s\n",job->num,job->name);
	}

}