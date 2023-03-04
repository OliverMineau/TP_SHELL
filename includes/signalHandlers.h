#ifndef __SIGHANDLER_H__
#define __SIGHANDLER_H__

#include "shell.h"
/**
 * @file signalHandlers.h
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
 * @brief Tue et supprime les processus terminés.
 * 
 * @param signum 
 */
void childHandler(int signum);

/**
 * @brief Intercepte le signal SIGINT
 * 
 * @param sig 
 */
void ctrlCHandler(int sig);

/**
 * @brief Intercepte le signal SIGTSTP
 * 
 * @param sig 
 */
void ctrlZHandler(int sig);

#endif