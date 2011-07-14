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
  cl_platform_id   platform_id[HAI_MAX_PLATFORM];
  cl_platform      platforms[HAI_MAX_PLATFORM];

  cl_device        devices[HAI_MAX_PLATFORM][HAI_MAX_DEVICE];
  cl_device_id     device_id[HAI_MAX_PLATFORM][HAI_MAX_DEVICE];

  cl_command_queue queue[HAI_MAX_PLATFORM][HAI_MAX_QUEUE];
  cl_context       context[HAI_MAX_PLATFORM];
	
  // -- Number of OpenCL env. ------------------------
  uint32_t         nPlatform;
  uint32_t         nDevice[OCL_MAX_PLATFORM];
  uint32_t         nQueue[OCL_MAX_PLATFORM];
  uint32_t         nContext;
  
  // -- General information ---------------------------
  thread_id_t     thread_id;
  uint32_t        resource;
  uint32_t        status;
  thread_mutex_t  wmutex;
  thread_cond_t   wcond;
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
int is_scheduler_stopped(hai_scheduler_t* scheduler) {
  return scheduler -> status == 1;
}

inline
int chk_condition() {
}

inline
int hai_scheduler_run(ocl_scheduler_t* sheduler) {
  uint32_t rid;
  bin_node_t* bnode;
  pthread_mutex_lock( scheduler -> wmutex );
  
  while ( should_i_stop(scheduler) ) {
    pthread_cond_wait( &(scheduler -> wcond), &(scheduler -> wmutex) );
        
    rid = hai_scheduler_get_empty_resource( scheduler );
    bnode = hai_keytable_pop(uid);
    hai_scheduler_go(rid, bnode);
    hai_scheduler_disable(rid);
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
