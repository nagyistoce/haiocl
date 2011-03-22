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
typedef struct map_key_t {
  char  key[HAI_MAX_KEY_LEN];
  int   size;
} map_key_t;

// ----------------------------------------------------------
// hash_node_t
// ----------------------------------------------------------
typedef char binary_t
typedef struct hai_hash_node_t {
  map_key_t  key;
  binary_t*  values;
  size_t     size;
  mutex_t    mutex;
} hai_hash_t;

// ----------------------------------------------------------
// key_table_t
// ----------------------------------------------------------
typedef hai_hash_node_t* key_table_t;

int mem_emit_data(map_key_t*, void*, size_t);
int mem_get_data(map_key_t*, void*, size_t);

#endif
