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

#include "agent.h"
#include "common.h"
#include "mem.h"
#include "ocl.h"


inline int haiocl_init() {
}

inline int haiocl_exit() {
  exit(1);
}

// ------------------------------------------------------------
// global variables
// ------------------------------------------------------------
typedef struct g_state {
  hai_agent_t*       agents;
  key_table_t*     	 keytable;
  uint32_t           kt_size;
  hai_scheduler_t* 	 scheduler;
  hai_qsplit_t*      splits_queue;
} g_state_t;

inline int g_state_init(g_state_t* p) {
  p -> kt_size = DEFAULT_KEYTABLE_SIZE;
  keytable = (key_table_t*)malloc(sizeof(key_table_t) * p -> kt_size);
}

inline int g_state_release(g_state_t* p) {
}
#endif
