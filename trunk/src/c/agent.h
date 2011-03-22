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


#ifndef AGENT_H
#define AGENT_H

#include "common.h"
#include <pthread.h>

#define thread_id_t     int
#define mutex_t         pthread_mutex_t
#define cond_t          pthread_cond_t  


typedef struct agent_t {
  // --- agent basic information --------
  void*       map_kernel;
  char*       map_kernel_src;
  map_key_t   in_key;
  map_key_t*  out_key;
  int         out_len;
  
  // --- runtime information --------
  int         weight;
  
  // --- thread spec. --------------
  thread_id_t tid;
  mutex_t     tmutex;
};


int agent_compile_kernel(agent_t* agent);
int agent_init_thread();
int agent_start();
int agent_stop();

#endif

