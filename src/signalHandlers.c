#include "signalHandlers.h"
#include <stdio.h>
#include "jobs.h"
#include "csapp.h"
#include "readcmd.h"



void childHandler(int signum){

	int pid;
	while((pid=waitpid(-1,NULL,WNOHANG|WUNTRACED))>0){
		Jobs *job;
		if((job=findJobByPID(jobs,pid))){

			if(job->state==STOPPED) return;

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
	if((job=findJobInFG(jobs))!=NULL){

		job->ground=BACKGROUND;
		job->state=STOPPED;
		printf("[%d]+  Stopped                 %s\n",job->num,job->name);
	}

}