/*================================================================================
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
 *================================================================================
 */


#ifndef HAI_H
#define HAI_H

#include <HAI/split.h>
#include <HAI/scheduler.h>
#include <HAI/common.h>

inline
int HAI_init() {
}

inline
int HAI_release() {
  exit(1);
}

// ------------------------------------------------------------
// global variables
// ------------------------------------------------------------
typedef struct {  
  hai_scheduler_t* 	 scheduler;               // scheduler pointer
  hai_queue_t*       splits_queue;            // splits queues
  hai_kernel_t       kernels[HAI_MAX_NKERNEL];
  uint32_t           klen;
} g_state_t;

inline 
int g_state_init(g_state_t* p) {
  int ret;
  ret = HAI_scheduler_init(p -> scheduler);
  p -> klen = 0;
  
}

inline int g_state_release(g_state_t* p) {
}


#endif
