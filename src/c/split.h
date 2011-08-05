/*==========================================================================
 *
 * split.h
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
#ifndef HAI_SPLIT_H
#define HAI_SPLIT_H

#include <HAI/hai.h>

// ----------------------------------------------------------
// hai_split_t
// ----------------------------------------------------------
typedef struct hai_split_t {
  kid_t      kid;
  void*      in_data;
  void*      out_data;
  size_t     in_size;
  size_t     out_size;
} hai_split_t;

// ----------------------------------------------------------
// hai_queue_node_t
// ----------------------------------------------------------
typedef struct hai_queue_node_t {
  struct hai_queue_node_t* next;
  hai_split_t       	   split;
} hai_queue_node_t;

// ----------------------------------------------------------
// hai_queue_t
// ----------------------------------------------------------
typedef struct hai_queue_t {
  hai_queue_node_t* head;
  hai_queue_node_t* tail;
  uint32_t          len;
  thread_mutex_t    qmutex
  sem_t				qsem;
} hai_queue_t;

// ----------------------------------------------------------
// HAI_queue_init
// ----------------------------------------------------------
inline
void HAI_queue_init(hai_queue_t* queue) {
  queue -> head = queue -> tail = NULL;
  queue -> len = 0;
  queue -> qmutex = thread_create_mutex();
  sem_init(&(queue -> qsem), 0, 0);
}

// ----------------------------------------------------------
// HAI_queue_wait
// ----------------------------------------------------------
#define HAI_queue_wait() HAI_queue_wait_(g_state -> split_queue)
inline
void HAI_queue_wait_(hai_queue_t* queue) {
  return sem_wait(&(queue -> qsem));
}

// ----------------------------------------------------------
// hai_queue_push
// ----------------------------------------------------------
#define HAI_queue_push(x) HAI_queue_push_(g_state -> split_queue, x)
inline
int hai_queue_push_(hai_queue_t* queue, 
                    hai_split_t  split) {
	pthread_mutex_lock(&(queue -> qmutex));
	hai_queue_node_t *p = (hai_queue_node_t *) malloc(sizeof(hai_queue_node_t));
	p -> split = split;
	p -> next = NULL;
	
	if (queue -> len == 0) { // insert on the head
		queue -> head = p;
		queue -> tail = queue -> head;
	} else { // insert on the tail
		queue -> tail -> next = p;
		queue -> tail = p;		
	}
	
	queue -> len ++;
	pthread_mutex_unlock(&(queue -> qmutex));
	sem_post(&(queue -> qsem));
	return 0;
}

// ----------------------------------------------------------
// hai_queue_pop
// ----------------------------------------------------------
#define HAI_queue_pop(x) HAI_queue_pop_(g_state -> split_queue, x)

inline
hai_split_t hai_queue_pop_(hai_queue_t* queue, int* ret) {
}

#endif
