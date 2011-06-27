/*==========================================================================
 *
 * hai.h
 *
 * Author:
 *   Si Yin <zyzyis@gmail.com>
 *
 * Copyright (C) 2011 Hai Computing
 *
 * This file is released under the terms of the GNU General Public License
 * versions 3.0. Please refers to the file COPYING for more information.
 *==========================================================================
 */


#ifndef HAI_AGENT_H
#define HAI_AGENT_H

#include "common.h"
#include <pthread.h>

#define thread_id_t     int
#define mutex_t         pthread_mutex_t
#define cond_t          pthread_cond_t  


typedef struct hai_agent_t {
  // --- agent basic information --------
  void*       map_kernel;
  char*       map_kernel_src;
  map_key_t   in_key;
  map_key_t   out_key;
  
  // --- runtime information --------
  int         weight;
  
  // --- thread spec. --------------
  thread_id_t tid;
  mutex_t     tmutex;
};


int agent_compile(agent_t* agent);
int agent_init();
int agent_start();
int agent_stop();
#endif

