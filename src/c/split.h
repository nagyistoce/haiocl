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

typedef uint32_t kid_t;		// kernel id type

// ----------------------------------------------------------
// Thread-safe Buffer type
// ----------------------------------------------------------
typedef struct {
  char*		data;
  size_t	offset;
  mutex_t	mutex;
  size_t	size;
  bool		shared;
} hai_buffer_t;

int hai_read_buffer(hai_buffer_t* p, size_t size);
int hai_write_buffer(hai_buffer_t* p, char* np, size_t size);

// ----------------------------------------------------------
// Notifier type
// ----------------------------------------------------------
typedef struct {
  uint32_t	kid;
  void*		output;
  uint32_t	offset;
} hai_notify_t;

hai_notify_t hai_register_to_kernel(kid_t kid, void* p, size_t size);
hai_notify_t hai_register_to_buffer();

// ----------------------------------------------------------
// kernel type
// ----------------------------------------------------------
typedef struct {
  hai_kernel_prop_t kernel_prop;	// kernel property
  cl_kernel*        kernel;			// kernel object
  char*             kernel_src;		// kernel source
  size_t            size;			// source size
  hai_notify_t      fn_notify;		// notifier
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
// HAI_register_kernel
// ----------------------------------------------------------
inline
uint32_t HAI_register_kernel(char* src, 
							 size_t size, 
							hai_kernel_prop_t prop, 
							hai_notify_t notifier, 
							kid_t* kid) {
}


#endif
