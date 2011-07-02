/*==========================================================================
 *
 * scheduler.h
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
#ifndef HAI_SCHEDULER_H
#define HAI_SCHEDULER_H


#include <CL/opencl.h>


typedef struct hai_scheduler {
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
  uint32_t         nQueue[OCL_MAX_PLATFORM];
  uint32_t         nContext;
  
  // -- General information ---------------------------
  thread_id_t     thread_id;
  uint32_t        resource;
  int             stopflag;
} hai_scheduler_t;

/**
 * Initialize the scheduler thread including OpenCL initialization and device query.
 * There is only 1 scheduler during runtime execution. The main goal of scheduler
 * is to manage the splits allocated to different OpenCL devices.
 */
int hai_scheduler_init(ocl_scheduler_t*);

/**
 * Release all the resources for the scheduler.
 */
int hai_scheduler_release(ocl_sheduler_t*);


inline
int hai_scheduler_run(ocl_scheduler_t* sheduler) {
  split_queue_t* queue = scheduler -> split_queue;

  while ( scheduler -> stopflag ) {
    // the scheduler has no resource
    if ( scheduler -> resource == 0 || queue -> size == 0 ) {
      hai_scheduler_wait();
      continue;
    }

    hai_split_t* nsplit = hai_split_queue_pop(queue);
    hai_scheduler_schedule(scheduler, nsplit);
  }
  return 0;
}

inline
void hai_scheduler_wait() {
}

/**
 * Query available OpenCL platforms.
 */
static int hai_query_platform(cl_platform_id, ocl_platform_t*);

/**
 * Query available OpenCL devices from platform.
 */
static int hai_query_device(cl_platform_id, cl_device_id, ocl_device_t*);


#endif
