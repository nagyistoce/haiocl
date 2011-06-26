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

#endif