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

void childHandler(int signum);
void ctrlCHandler(int sig);
void ctrlZHandler(int sig);

#endif