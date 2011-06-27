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
hai_agent_t*         agents;
key_table_t*     	 keytable;
hai_scheduler_t* 	 scheduler;
hai_qsplit_t*     	 splits_queue;
#endif
