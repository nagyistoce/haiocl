/*==========================================================================
 *
 * ocl.h
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
#ifndef HAI_OCL_H
#define HAI_OCL_H


#include <CL/opencl.h>

typedef struct ocl_split {
  // -- kernel properties -------------
  cl_kernel* kernel;
  cl_uint work_dim;
  size_t* global_work_offset;
  size_t* global_work_size;
  size_t* local_work_size;
  cl_uint num_events_in_wait_list;
  const cl_event* event_wait_list;
  cl_event *event;
	
  // --inputs and outputs memory objects -------------
  cl_mem in_binary;
  cl_mem in_schema;
  cl_mem in_size;
	
  cl_mem out_binary;
  cl_mem out_schema;
  cl_mem out_size;
  
} ocl_split_t;


typedef struct ocl_scheduler {
  // -- OpenCL Env. IDs -------------------------------
  cl_platform_id   platform_id[HAI_OCL_MAX_PLATFORM];
  cl_platform      platforms[HAI_OCl_MAX_PLATFORM];

  cl_device        devices[HAI_OCl_MAX_PLATFORM][HAI_OCL_MAX_DEVICE];
  cl_device_id     device_id[HAI_OCl_MAX_PLATFORM][HAI_OCL_MAX_DEVICE];

  cl_command_queue queue[HAI_OCL_MAX_PLATFORM][HAI_OCL_OCL_MAX_QUEUE];
  cl_context       context[HAI_OCL_MAX_PLATFORM];
	
  // -- Number of OpenCL env. ------------------------
  uint32_t         nPlatform;
  uint32_t         nDevice[OCL_MAX_PLATFORM];
  uint32_t         nQueue;
  uint32_t         nContext;
  
  // -- Thread information ---------------------------
  thread_id_t     tid;
  mutex_t         tmutex;
  cond_t          tcond;
} ocl_scheduler_t;

int ocl_scheduler_init(ocl_scheduler_t*);
int ocl_scheduler_shutdown(ocl_sheduler_t*);

int ocl_splits_init();
int ocl_splits_shutdown();


static int ocl_profile_platform(cl_platform_id, ocl_platform_t*);
static int ocl_profile_device(cl_platform_id, cl_device_id, ocl_device_t*);

#endif
