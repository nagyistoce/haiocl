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
typedef char binary_t;
typedef struct {
  bin_node_t* 	next;       // next pointer
  binary_t*		pdata;      // data pointer
  uint32_t		ihead;      // first index of data object
  uint32_t      itail;      // last index of data object
  uint32_t      size;       // total number of data object
} bin_node_t;

// ----------------------------------------------------------
// key_node_t
// ----------------------------------------------------------
typedef struct {
  uid_t			uid;        // unique id for the key
  bin_node_t*	phead;      // head of the link list
  bin_node_t*	ptail;      // tail of the link list
  uint32_t      nobj;       // number of object in the node
  size_t        ssize;      // size of the object in bytes
  mutex_t    	mutex;
} key_node_t;

// ----------------------------------------------------------
// key_table_t
// ----------------------------------------------------------
typedef struct {
  key_node_t*     nodes;    // key node array
  uint32_t        maxkey;   // maximum number of keys in the table
  uint32_t        nkey;     // number of keys in the table
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
#define hai_keytable_search(x) hai_keytable_search_(x, g_state -> keytable)
inline
key_node_t* hai_keytable_search_(uid_t uid, key_table_t keytable) {
  return keytable -> nodes[uid];
}

// ----------------------------------------------------------
// hai_keytable_init
// ----------------------------------------------------------
inline static
bin_node_t* init_bin_node(size_t ssize, uint32_t len) {
  bin_node_t* p = (bin_node_t*)malloc(sizeof(bin_node_t));
  p -> next  = NULL;
  p -> pdata = (binar_t)malloc(sizeof(len * ssize));
  p -> ihead = 0;
  p -> itail = 0;
  p -> size  = len;
  return p;
}
// ----------------------------------------------------------
// hai_keytable_push()
//
// Insert binary data into the linked list in the key table.
// By design there is only 1 thread which can access the node
// so that no multithreading is possible.
//
// Parameter:
//   uid      - unique key value
//   binary_t - serialized binary data
//   bsize    - data size in bytes
// Return:
//   0 - good otherwise failed
// ----------------------------------------------------------
#define	hai_keytable_push(uid, data) \
  hai_keytable_push_(uid, data, g_state -> keytable)


inline
int hai_keytable_push_(uid_t uid, binary_t* data, uint32_t n, 
                              key_table_t* keytable) {
  uid_t index = hai_keytable_search_(uid, keytable);
  key_node_t* pnode = keytable -> nodes[index];
  bin_node_t* ptail = pnode -> ptail;
  binary_t *src, *des;
  
  for (int i = 0; i < n; i ++) {
    if (ptail -> remain == 0) {
      ptail -> next = init_bin_node(pnode -> ssize, pnode -> capacity);
      pnode -> ptail = ptail -> next;
      ptail = ptail -> next;
    }

    src = data + (i * pnode -> ssize);
    des = ptail -> pdata[ pnode -> capacity - ptail -> remain ];

    memcpy(des, src, pnode -> ssize);
    ptail -> remain --;
  }
  return 0;
}

// ----------------------------------------------------------
// hai_keytable_pop_data()
//
// Insert binary data into the linked list in the key table.
// By design there is only 1 thread which can access the node
// so that no multithreading is possible.
//
// Parameter:
//   uid      - unique key value
//   des      - data copy to
//
// Return:
//   0 - good otherwise failed
// ----------------------------------------------------------
#define hai_keytable_pop(uid, des) hai_keytable_pop_(uid, des, g_state -> keytable)

int hai_keytable_pop_(uid_t uid, binary_t* des, 
                      keytable_t* keytable) {
  uid_t index = hai_keytable_search_(uid, keytable);
  key_node_t* pk = keytable -> nodes[index];
  bin_node_t* pb = pnode -> phead;
  
  memcpy(des, pb -> ihead, pk -> ssize);
  pb -> ihead = p -> ihead + pb -> ssize;
  if (pb -> ihead > pb -> itail) {
    // currently node is running out, move to the next node
    pnode -> phead = pb -> next;
    free(pb -> pdata);
    pb -> pdata = NULL;
    free(pb);
  }
  return 0;
}

// ----------------------------------------------------------
// hai_keytable_add_key()
//
// Add a new key in the key table.
//
// Parameters:
//   ssize       - size of the new data object size
//   default_len - the inital length of the new key node
//  
// Return:
//   uid - the unique key id
// ----------------------------------------------------------
#define hai_keytable_add_key(x, y) hai_keytable_assign_((x), (y), &(g_state -> keytable))

uid_t hai_keytable_assign_(size_t ssize, uint32_t default_len, 
                           hai_key_table_t* pt) {
  key_node_t* nnp = NULL;
  if (pt -> maxkey == pt -> nkey) {
    // the key table is full,  extend the key size
    nnp = (key_node_t*) malloc(sizeof(pt -> maxkey) + HAI_INIT_KEY_LEN);
    memcpy(nt, pt -> nodes, sizeof(key_node_t) * pt -> maxkey);
    free(pt -> nodes);
    pt -> nodes = nnp;
    pt -> maxkey += HAI_INIT_KEY_LEN;
  }

  // create the new key node
  uint32_t last_i = keytable -> nkey ++;
  key_node_t* pk = pt -> nodes[last_i];

  pk -> uid   = last_i;
  pk -> phead = init_bin_node(size, default_len);
  pk -> ptail = phead;
  pk -> nobj  = 0;
  pk -> ssize = ssize;

  return last_i;
}
#endif
