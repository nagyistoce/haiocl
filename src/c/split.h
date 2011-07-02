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

typedef struct hai_kernel_prop {
  // -- kernel properties -------------
  cl_kernel* kernel;
  cl_uint work_dim;
  size_t* global_work_offset;
  size_t* global_work_size;
  size_t* local_work_size;
  cl_uint num_events_in_wait_list;
  const cl_event* event_wait_list;
  cl_event *event;
} hai_kernel_prop_t;

typedef struct hai_kernel_data {
  // --inputs and outputs memory objects -------------
  cl_mem in_binary;
  cl_mem in_schema;
  cl_mem in_size;
	
  cl_mem out_binary;
  cl_mem out_schema;
  cl_mem out_size;
} hai_kernel_data_t;

typedef struct hai_split {
  hai_kernel_prop* kernel_prop;
  hai_kernel_data_t* kernel_data;
  hai_workdag_t* dag;
} hai_split_t;

/**
 * Splitqueue item type by using linklist
 */
typedef struct hai_splitqueue_item {
  struct hai_splitqueu_item* next;
  hai_split* split;
} hai_splitqueue_item_t;

/**
 * Splitqueue type
 */
typedef struct hai_splitqueue {
  struct hai_splitqueue* head;
  struct hai_splitqueue* tail;
  uint32_t length;
} hai_splitqueue_t;

inline
int hai_splitqueue_push( hai_splitqueue_t* queue, 
                         hai_split_t*  split,
                         hai_thread_mutex* mutex) {
  if (length == 0) {
  }
}

inline
hai_split_t* hai_splitqueue_pop( hai_splitqueue_t* queue,
                                 hai_thread_mutex* mutex) {
}

#endif
