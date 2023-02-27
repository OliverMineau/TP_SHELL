#include "jobs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void addJob(Jobs **jobs, char *name, int pid){

    Jobs *newJob = malloc(sizeof(newJob));
    newJob->name = malloc(sizeof(name));
    strcpy(newJob->name,name);
    newJob->pid=pid;

    if((*jobs)==NULL){
        newJob->num=1;
    }
    else{
        newJob->num=(*jobs)->num+1;
        newJob->next=(*jobs);
    }

    *jobs=newJob;
}

Jobs *findJobByPID(Jobs *jobs, int pid){
    Jobs *tmp=jobs;
    while (tmp!=NULL)
    {
        if(tmp->pid == pid){
            return tmp;
        }
        tmp=tmp->next;
    }
    return NULL;
}

Jobs *findJobByName(Jobs *jobs, char *name){
    Jobs *tmp=jobs;
    while (tmp!=NULL)
    {
        if(!strcmp(tmp->name,name)){
            return tmp;
        }
        tmp=tmp->next;
    }
    return NULL;
}

int deleteJob(Jobs **jobs, Jobs *del){
    
    Jobs *tmpFils=(*jobs)->next;
    if(tmpFils==NULL){
        free((*jobs)->name);
        free((*jobs));
        *jobs=NULL;
        return 1;
    }

    while (tmpFils!=NULL)
    {
        if(tmpFils==del){

            (*jobs)->next=tmpFils->next;
            free(tmpFils->name);
            free(tmpFils);
            return 1;
        }

        (*jobs)=(*jobs)->next;
        tmpFils=tmpFils->next;
    }
    return 0;

}

void printJobs(Jobs *jobs){
    Jobs *tmp=jobs;
    printf("All jobs:\n");
    while (tmp!=NULL)
    {
        printf("    [%d] %s %d\n",tmp->num,tmp->name,tmp->pid);
        tmp=tmp->next;
    }
}