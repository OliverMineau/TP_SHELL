#ifndef __REDIRECTION_H__
#define __REDIRECTION_H__

/**
 * @file redirection.h
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
 * @brief Redirige l'entrée si un fichier d'entrée est fournit.
 * 
 * @param inNom 
 * Nom du fichier donnée en entrée.
 * @param prevCmdPipe 
 * Pipe venant de la commande précédente.
 * @param deb 
 * Indique si la commande est la première d'une sequence de commandes.
 * @param fd_in
 * Descripteur de fichier correspondant au fichier de nom inNom.
 * @return int 
 * 1 si erreur, 0 sinon.
 */
int redirectionEntree(char *inNom, int *prevCmdPipe, int deb, int *fd_in);

/**
 * @brief Redirige la sortie si un fichier de sortie est fournit.
 * 
 * @param outNom 
 * Nom du fichier donnée en sortie.
 * @param nextCmdPipe 
 * Pipe allant vers la prochaine commande.
 * @param fin
 * Indique si la commande est la dernière d'une sequence de commandes.
 * @param deb 
 * Indique si la commande est la première d'une sequence de commandes.
 * @param fd_out
 * Descripteur de fichier correspondant au fichier de nom outNom.
 * @return int 
 * 1 si erreur, 0 sinon.
 */
int redirectionSortie(char *outNom, int *nextCmdPipe, int fin, int deb, int *fd_out);


#endif