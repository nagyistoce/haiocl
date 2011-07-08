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
  hai_agent_t*       agents;                  // all the agents pointers
  hai_key_table_t  	 keytable;                // all the map keys
  hai_scheduler_t* 	 scheduler;               // scheduler pointer
  hai_qsplit_t*      splits_queue;            // splits queues

  uint32_t           kt_capacity;             // key table length
} g_state_t;

inline int g_state_init(g_state_t* p) {
  int ret;
  ret = hai_keytable_init(p -> keytables);
  CHK_RET(ret);

  ret = hai_scheduler_init(p -> scheduler);
  CHK_RET(ret);

  return 0;
}

inline int g_state_release(g_state_t* p) {
}
#endif
