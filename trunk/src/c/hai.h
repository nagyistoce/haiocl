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


int haiocl_init();
int haiocl_exit();

// ------------------------------------------------------------
// global variables
// ------------------------------------------------------------
agent_t*         hai_agents;
key_table_t*     hai_table;
ocl_scheduler_t* ocl_scheduler;
ocl_split_t*     ocl_splits;
#endif
