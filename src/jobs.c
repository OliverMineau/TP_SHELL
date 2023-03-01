#include "jobs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void addJob(Jobs **jobs, char **name, int pid, char *state){

    Jobs *newJob = malloc(sizeof(Jobs));

    char fullCmd[50];
    fullCmd[0]='\0';
    int i=0;
    while(name[i]){
        strcat(fullCmd,name[i]);
        strcat(fullCmd," ");
        i++;
    }
    newJob->name = malloc(strlen(fullCmd));
    newJob->state = malloc(strlen(state));
    strcpy(newJob->name,fullCmd);
    strcpy(newJob->state,state);
    newJob->pid=pid;

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
    
    if (*jobs == NULL) {
        return 0;
    }
    
    if (*jobs == del) {
        *jobs = del->next;
        free(del->name);
        free(del->state);
        free(del);
        return 1;
    }
    
    Jobs *head = *jobs;
    Jobs *tmpFils = head->next;
    
    while (tmpFils != NULL) {
        if (tmpFils == del) {
            head->next = tmpFils->next;
            free(tmpFils->name);
            free(tmpFils->state);
            free(tmpFils);
            return 1;
        }
        head = tmpFils;
        tmpFils = tmpFils->next;
    }
    
    return 0;
}


void printJobs(Jobs *jobs){
    if(jobs==NULL) return;

    Jobs *tmp=jobs;
    while (tmp!=NULL)
    {
        printf("[%d] %d %s %s\n",tmp->num,tmp->pid,tmp->state,tmp->name);
        tmp=tmp->next;
    }
}

void addFinJob(FinJobs **fj, int pid){
    
    FinJobs *newfj=malloc(sizeof(FinJobs));
    newfj->pid=pid;

    if((*fj)==NULL){
        newfj->next=NULL;
    }else{
        newfj->next=(*fj);
    }
    *fj=newfj;
}

void deleteFinJob(FinJobs **fj, int pid){
    
    FinJobs *head=(*fj);
    FinJobs *tmpFils=(*fj)->next;
    if(head->pid==pid){
        *fj=head->next;
        free(head);
        return;
    }
    
    while (tmpFils!=NULL)
    {
        if(tmpFils->pid==pid){
            head->next=tmpFils->next;
            free(tmpFils);
            return;
        }
        head=head->next;
        tmpFils=tmpFils->next;
    }
}

void printFinJobs(FinJobs *jobs){
    while (jobs!=NULL){
        printf("Job %d\n",jobs->pid);
        jobs=jobs->next;
    }
}

