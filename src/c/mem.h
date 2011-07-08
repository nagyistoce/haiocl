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
typedef uint32_t uid_t;

typedef struct {
  uid_t 	uid;
} map_key_t;

// ----------------------------------------------------------
// bin_node_t
// ----------------------------------------------------------
typedef char* binary_t;
typedef struct {
	struct raw_data_t* 	next;
	binary_t 			pdata;
	size_t				size;
} bin_node_t;

// ----------------------------------------------------------
// key_node_t
// ----------------------------------------------------------
typedef struct {
  uid_t			uid;
  raw_data_t*	phead;
  raw_data_t*	ptail;
  uint32_t     	size;
  mutex_t    	mutex;
} key_node_t;

// ----------------------------------------------------------
// key_table_t
// ----------------------------------------------------------
typedef struct {
  key_node_t*     nodes;
  uint32_t        capacity;
  uint32_t        size;
  mutex_t         mutex;
} key_table_t;

typedef key_table_t hai_key_table_t;


// ----------------------------------------------------------
// hai_keytable_init()
//
// Initialize the keytable by creating default empty key slots.
// 
// Return:
//   0 - initialize keytable failed
//   N - the number of keys created
// ----------------------------------------------------------
#define hai_keytable_init(x) hai_keytable_init_((x), DEFAULT_KEYTABLE_SIZE)

inline static
int hai_keytable_init_(key_table keytable, uint32_t size) {
  uint32_t i;
  keytable -> nodes = (key_node_t*)malloc(sizeof(key_node_t) * size);
  for (i = 0; i < size; i ++) {
    keytable -> nodes[i].uid = UINT32_MAX;
    keytable -> nodes[i].phead = NULL;
    keytable -> nodes[i].ptail = NULL;
    keytable -> nodes[i].size = NULL;
    hai_thread_init_mutex(keytable -> nodes[i].mutex);
  }
  keytable -> capacity = size;
  keytable -> size = 0u;
}

// ----------------------------------------------------------
// hai_keytable_init
// ----------------------------------------------------------
void* hai_keytable_search(uid_t uid)

// ----------------------------------------------------------
// hai_keytable_init
// ----------------------------------------------------------
uid_t hai_keytable_generate_key();

// ----------------------------------------------------------
// hai_keytable_init
// ----------------------------------------------------------
inline 
int	hai_keytable_insert_data(uid_t uid, binary_t data) ;


// ----------------------------------------------------------
// hai_keytable_insert_key()
//
// Insert a key into the key table. Since the key table is a
// dynamic array, there will be chance to extend it.
//
// Parameters:
//   uid - unique key generated based on the capacity.
//   keytable - the original key table.
//  
// Return:
//   0 - ok otherwise failed.
// ----------------------------------------------------------
#define hai_keytable_insert_key(x) hai_keytable_insert_key((x), g_state -> keytable)

int hai_keytable_insert_key_(uid_t uid, hai_key_table_t keytable) {
  // TODO: thread-safe?
  assert(keytable -> capacity >= keytable -> size);

  if (keytable -> capacity == keytable -> size) {
    // TODO: extend the key size
  }

  uint32_t last_i = keytable -> size - 1;
  keytable -> nodes[last_i + 1] = keytable -> nodes[last_i] + 1;
  return 0;
}
#endif
