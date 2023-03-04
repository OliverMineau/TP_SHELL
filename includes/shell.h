#ifndef __SHELL_H__
#define __SHELL_H__

#include <stdio.h>
#include <stdlib.h>
#include "readcmd.h"
#include "csapp.h"
#include "internCmd.h"
#include "externCmd.h"
#include "jobs.h"
#include "signalHandlers.h"

/**
 * @file shell.h
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
 * @brief Liste de tous les jobs en cours.
 * 
 */
extern Jobs *jobs;

#endif