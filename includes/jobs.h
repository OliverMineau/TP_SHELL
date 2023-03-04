#ifndef  __JOBS_H__
#define __JOBS_H__

/**
 * @file jobs.h
 * @author @OliverMineau
 * @author @alexisthach
 * @brief 
 * @version 0.1
 * @date 2023-03-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/**
 * @brief Etat d'un job.
 * 
 */
enum state {RUNNING,STOPPED};

/**
 * @brief Plan d'un job.
 * 
 */
enum ground {BACKGROUND,FOREGROUND};

/**
 * @brief Structure comportant les informations sur un job.
 * @param name
 * Nom de la commande executée.
 * @param state
 * Etat du job : Running, Stopped.
 * @param pid
 * Pid du processus executant le job.
 * @param num
 * Numéro du job.
 * @param next
 * Job suivant dans la liste.
 * @param bg
 * 1 si la commande est en background, 0 sinon.
 */
typedef struct Jobs Jobs;
struct Jobs {
    char *name;
    enum state state;
    int pid;
    int num;
    enum ground ground;
    Jobs *next;
};


/**
 * @brief Ajout  d'un job dans la liste.
 * 
 * @param jobs 
 * Job à ajouter.
 * @param name 
 * Nom de la commande executée.
 * @param pid 
 * Pid de la commande executée.
 * @param state 
 * Etat de la commande executée.
 */
void addJob(Jobs **jobs, char *name, int pid, enum state state, enum ground ground);

/**
 * @brief Trouve si le job de nom name existe dans la liste.
 * 
 * @param jobs 
 * Liste des jobs.
 * @param name 
 * Nom du job à chercher.
 * @return Jobs*
 * Job trouvé.
 */
Jobs *findJobByName(Jobs *jobs, char *name);

/**
 * @brief Trouve si le job de pid pid existe dans la liste.
 * 
 * @param jobs 
 * Liste des jobs.
 * @param pid 
 * Pid du job à chercher.
 * @return Jobs*
 * Job trouvé.
 */
Jobs *findJobByPID(Jobs *jobs, int pid);

/**
 * @brief Supprimer un job par pid.
 * 
 * @param jobs 
 * Liste des jobs.
 * @param del 
 * Job a supprimer.
 * @return int 
 * 0 si job pas supprimé, 1 sinon.
 */
int deleteJob(Jobs **jobs, Jobs *del);

/**
 * @brief Affiche les jobs en executions.
 * 
 * @param jobs 
 * Liste des jobs.
 */
void printJobs(Jobs *jobs);

/**
 * @brief Indique si le job est en premier plan.
 * 
 * @param jobs 
 * Liste des jobs.
 * @return int 
 */
int jobEnFG(Jobs *jobs);

/**
 * @brief Recherche un job en premier plan.
 * 
 * @param jobs 
 * Liste des jobs.
 * @return Jobs* 
 */
Jobs *findJobInFG(Jobs *jobs);

/**
 * @brief Trouve un job par son nom ou numero.
 * 
 * @param jobs 
 * Liste des jobs.
 * @param id 
 * Numero ou nom du job.
 * @return Jobs* 
 */
Jobs *findJobNameNum(Jobs *jobs, char *id);

#endif