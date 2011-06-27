/*==========================================================================
 *
 * mem.h
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

#ifndef HAI_MEM_H
#define HAI_MEM_H

#include "common.h"
#include "agent.h"

// ----------------------------------------------------------
// map_key_t defines the map key type
// ----------------------------------------------------------
typedef uint64_t uid_t;

typedef struct map_key_t {
  uid_t* 	uid;
  uint32_t  size;
} map_key_t;

// ----------------------------------------------------------
// hash_node_t
// ----------------------------------------------------------
typedef struct hai_hash_node {
  uid_t			uid;
  raw_data_t*	phead;
  raw_data_t*	ptail;
  uint32_t     	size;
  mutex_t    	mutex;
} hai_hash_t;

typedef hai_hash_node_t* key_table_t;
// ----------------------------------------------------------
// raw_data_t
// ----------------------------------------------------------
typedef char* binary_t;
typedef struct raw_data {
	struct raw_data_t* 	next;
	binary_t 			pdata;
	size_t				size;
} raw_data_t;

// ----------------------------------------------------------
// hai_keytable_init
// ----------------------------------------------------------
int   hai_keytable_init(void*);

// ----------------------------------------------------------
// hai_keytable_init
// ----------------------------------------------------------
void* hai_keytable_search(uid_t uid)

// ----------------------------------------------------------
// hai_keytable_init
// ----------------------------------------------------------
uid_t hai_keytable_generate();

// ----------------------------------------------------------
// hai_keytable_init
// ----------------------------------------------------------
int	  hai_keytable_insert(uid_t uid, binary_t data);

#endif
