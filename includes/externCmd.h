#ifndef __EXTERNCMD_H__
#define __EXTERNCMD_H__
/**
 * @file externCmd.h
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
 * @brief Gestionnaire des commandes externes.
 * 
 * @param cmd 
 * Contient une commande et ses parametres.
 * @param inNom 
 * Nom du fichier donné en entrée si fournit, sinon null.
 * @param outNom 
 * Nom du fichier donné en sortie si fournit, sinon null.
 * @param pipes 
 * Tableau de deux pipes contenant prevCmdPipe et nextCmdPipe.
 * @param deb 
 * Indique si la commande lue est la premiere.
 * @param fin 
 * Indique si la commande lue est la derniere.
 * @return int
 * 1 si erreur, 0 sinon.
 */
int commandeExterne(char **cmd, char *inNom, char *outNom, int pipes[2][2], int deb, int fin);

#endif