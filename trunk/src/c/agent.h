/*==========================================================================
 *
 * agent.h
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


#ifndef HAI_KERNEL_H
#define HAI_KERNEL_H

#include "common.h"

typedef struct hai_kernel_t {
  // --- agent basic information --------
  void*       kernel_bin;
  char*       kernel_src;
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

