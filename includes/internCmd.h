#ifndef __INTERNCMD_H__
#define __INTERNCMD_H__

/**
 * @file internCmd.h
 * @author @OliverMineau
 * @author @alexisthach
 * @brief 
 * @version 0.1
 * @date 2023-03-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "readcmd.h"
#include "jobs.h"


/**
 * @brief Affiche l'environnement courant du shell.
 * 
 */
void printShellEnv();

/**
 * @brief Vérifie si la commande donnée doit fermer le shell.
 * 
 * @param cmd 
 * Structure cmdline contenant les commandes.
 * @param n
 * Position/Numéro de la commande à vérifier.
 */
void isQuitShell(struct cmdline *cmd, int n);

/**
 * @brief Vérifie si la commande donnée doit changer l'environnement du shell.
 * 
 * @param cmd 
 * Structure cmdline contenant les commandes.
 * @param n 
 * Position/Numéro de la commande à vérifier.
 * @return int 
 * 1 si commande ne peut etre suivie par d'autres commandes, 0 sinon.
 * 
 */
int isChangeDir(struct cmdline *cmd, int n);

/**
 * @brief Vérifie si la commande donnée doit afficher les jobs en cours.
 * 
 * @param cmd 
 * Structure cmdline contenant les commandes.
 * @param n 
 * Position/Numéro de la commande à vérifier.
 * @param jobs
 * Liste des jobs en cours.
 * @return int 
 * 1 si commande ne peut etre suivie par d'autres commandes, 0 sinon.
 */
int isJobs(struct cmdline *cmd, int n, Jobs *jobs);

/**
 * @brief Gestionnaire des commandes internes
 * 
 * @param cmd 
 * Structure cmdline contenant les commandes.
 * @param n 
 * Position/Numéro de la commande à vérifier.
 * @param jobs 
 * Liste des jobs en cours.
 * @return int 
 * 1 si c'est une commande interne,
 * -1 si c'est une commande interne qui ne peut pas etre suivie d'une autre commande,
 * 0 sinon.
 */
int commandeInterne(struct cmdline *cmd, int n, Jobs **jobs, char *outNom, int pipes[2][2], int deb, int fin);

/**
 * @brief Vérifie si la commande donnée doit mettre en premier plan un job.
 * 
 * @param cmd 
 * Structure cmdline contenant les commandes.
 * @param n 
 * Position/Numéro de la commande à vérifier.
 * @param jobs 
 * Liste des jobs en cours.
 * @return int 
 */
int isFg(struct cmdline *cmd, int n, Jobs *jobs);

/**
 * @brief  Vérifie si la commande donnée doit mettre en arriere plan un job.
 * 
 * @param cmd 
 * Structure cmdline contenant les commandes.
 * @param n 
 * Position/Numéro de la commande à vérifier.
 * @param jobs 
 * Liste des jobs en cours.
 * @return int 
 */
int isBg(struct cmdline *cmd, int n, Jobs *jobs);

#endif