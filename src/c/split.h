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

// ----------------------------------------------------------
// key_table_t
// ----------------------------------------------------------
typedef struct {
  hai_kernel_prop_t kernel_prop;
  cl_kernel*        kernel;
  char*             kernel_src;
  size_t            size;
  void*             fn_notify;
} hai_kernel_t;

// ----------------------------------------------------------
// kernel properties
// ----------------------------------------------------------
typedef struct {
  size_t          global_work_offset[3];
  size_t          global_work_size[3];
  size_t          local_work_size[3];
  cl_uint         num_events_in_wait_list;
  cl_event*       event_wait_list;
  cl_event        event;
  size_t          single_input_size;
  size_t          max_input_size;
  size_t          single_output_size;
  size_t          max_output_size;
} hai_kernel_prop_t;

// ----------------------------------------------------------
// key_table_t
// ----------------------------------------------------------
inline
uint32_t HAI_register_kernel(char* src, 
                             size_t size, 
                             HAI_kernel_prop_t prop, 
                             uint32_t* kid) {
}

// ----------------------------------------------------------
// key_table_t
// ----------------------------------------------------------
typedef struct {
  uint32_t   kid;
  char*      in_data;
  char*      out_data;
  size_t     in_size;
  size_t     out_size;
} hai_split_t;

// ----------------------------------------------------------
// key_table_t
// ----------------------------------------------------------
typedef struct {
  hai_queue_node_t* next;
  hai_split_t       split;
} hai_queue_node_t;

// ----------------------------------------------------------
// key_table_t
// ----------------------------------------------------------
typedef struct {
  hai_queue_node_t* head;
  hai_queue_node_t* tail;
  uint32_t          len;
  thread_mutex_t    qmutex;
} hai_queue_t;

// ----------------------------------------------------------
// key_table_t
// ----------------------------------------------------------
inline
int HAI_queue_init(HAI_queue_t* queue) {
  queue -> head = queue -> tail = NULL;
  queue -> len = 0;
  queue -> qmutex = thread_create_mutex();
  return 0;
}
// ----------------------------------------------------------
// key_table_t
// ----------------------------------------------------------

inline
int hai_queue_push( hai_queue_t* queue, 
                    hai_split_t* split) {
}

// ----------------------------------------------------------
// key_table_t
// ----------------------------------------------------------
inline
int hai_split_t* hai_queue_pop( hai_queue_t* queue,
                                hai_split_t** split) {
}

#endif
