#ifndef __INTERNCMD_H__
#define __INTERNCMD_H__

#include "readcmd.h"


/**
 * @brief Verifier si la commande correspond a quitter le shell
 * 
 * @param cmd 
 */

void printShellEnv();

void isQuitShell(struct cmdline *cmd, int n);

int isChangeDir(struct cmdline *cmd, int n);

int commandeInterne(struct cmdline *cmd, int n);

#endif