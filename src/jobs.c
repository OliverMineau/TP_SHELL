#include "jobs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void addJob(Jobs **jobs, char *name, int pid, enum state state, enum ground ground){

    Jobs *newJob = malloc(sizeof(Jobs));

    newJob->name = malloc(strlen(name));
    strcpy(newJob->name,name);
    newJob->state=state;
    newJob->pid=pid;
    newJob->ground=ground;

    /*Si c'est le premier job*/
    if((*jobs)==NULL){
        newJob->num=1;
        newJob->next=NULL;
    }
    else{
        newJob->num=(*jobs)->num+1;
        newJob->next=(*jobs);
    }

    *jobs=newJob;
}

Jobs *findJobByPID(Jobs *jobs, int pid){
    Jobs *tmp=jobs;
    /*Cherche dans les jobs le bon pid*/
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
    /*Cherche dans les jobs le bon nom*/
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
    
    if (*jobs == NULL) {
        return 0;
    }
    
    if (*jobs == del) {
        *jobs = del->next;
        free(del->name);
        free(del);
        return 1;
    }
    
    Jobs *tete = *jobs;
    Jobs *tmpFils = tete->next;
    
    while (tmpFils != NULL) {
        if (tmpFils == del) {
            tete->next = tmpFils->next;
            free(tmpFils->name);
            free(tmpFils);
            return 1;
        }
        tete = tmpFils;
        tmpFils = tmpFils->next;
    }
    
    return 0;
}


void printJobs(Jobs *jobs){
    if(jobs==NULL) return;

    Jobs *tmp=jobs;
    while (tmp!=NULL)
    {
        char *stateName="";
        switch (tmp->state)
        {
        case RUNNING:
            stateName="Running";
            break;
        case STOPPED:
            stateName="Stopped";
            break;
        default:
            break;
        }
        
        printf("[%d] %d %s %s\n",tmp->num,tmp->pid,stateName,tmp->name);
        tmp=tmp->next;
    }
}

int jobEnFG(Jobs *jobs){
    while (jobs!=NULL){
        if(jobs->ground==FOREGROUND) return 1;
        jobs=jobs->next;
    }
    return 0;
}

Jobs *findJobInFG(Jobs *jobs){
    while (jobs!=NULL){
        if(jobs->ground==FOREGROUND) return jobs;
        jobs=jobs->next;
    }
    return NULL;
}


Jobs *findJobNameNum(Jobs *jobs, char *id){
    
    if(!id) id="1";
    /*Cherche dans chaque job*/
    while (jobs!=NULL){
        char buffer[100];
        /*Convertir le job num en char* */
        sprintf(buffer, "%d", jobs->num);
        if(!strcmp(jobs->name,id) || !strcmp(buffer,id)) return jobs;
        jobs=jobs->next;
    }
    return NULL;
}
