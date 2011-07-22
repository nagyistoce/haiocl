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


typedef struct {
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
  uint32_t         nQueue[OCL_MAX_RESOURCE];
  uint64_t         device_status;
  thread_mutex_t   device_status_mutex;
  uint32_t         nResource;

  // -- General information ---------------------------
  thread_id_t     thread_id;  
  uint32_t        scheduler_status;
  thread_mutex_t  scheduler_mutex;
  thread_cond_t   scheduler_cond;;
} hai_scheduler_t;

// ----------------------------------------------------------
// hai_scheduler_init()
//
// Initialize the scheduler thread including OpenCL initialization and device query.
// There is only 1 scheduler during runtime execution. The main goal of scheduler
//  is to manage the splits allocated to different OpenCL devices.
// ----------------------------------------------------------
inline
int HAI_scheduler_init(ocl_scheduler_t* scheduler) {
  cl_int ret;
  cl_int i, j;
  char buf[1024];

  ret = clGetPlatformIDs(HAI_MAX_PLATFORM, scheduler -> platform_id, 
                         scheduler -> &nPlatform);
  ASSERT_OCL_RET(ret, scheduler);
  logme("%d platforms fetched.", scheduler -> nPlatform);
  
  scheduler -> nResource = 0;
  for (i = 0; i < scheduler -> nPlatform; i ++) {
    clGetPlatformInfo(scheduler -> platform_id[i], 
                      CL_PLATFORM_NAME, 1024, buf, NULL);
    logme("Platform %d : %s\n", i, buf);
    
    ret = clGetDeviceIDs(scheduler -> platform_id[i], 
                         CL_DEVICE_TYPE_ALL, 
                         HAI_MAX_DEVICE, 
                         scheduler -> device_id[i],
                         scheduler -> nDevice + i);
    ASSERT_OCL_RET(ret, scheduler);

    logme("Platform %d : %d devices is found.\n", i, scheduler -> nDevice[i]);
    nResource += scheduler -> nDevice[i];

    // create context
    scheduler -> context[i] = clCreateContext(NULL, scheduler -> nDevice, 
                                              scheduler -> device_id[i], 
                                              context_notify, 
                                              i, 
                                              &ret);
    ASSERT_OCL_RET(ret, scheduler);
    
    for (j = 0; j < scheduler -> nDevice[i]; j ++) {
      clGetDeviceInfo(scheduler -> device_id[i][j], 
                      CL_DEVICE_VENDOR, 
                      1024, 
                      buf, 
                      NULL);
      logme("VENDOR: %s\n", buf);
      scheduler -> queue[i][j] = clCreateCommandQueue(scheduler -> context[i], 
                                                      scheduler -> device_id[i], 
                                                      OCL_PROFILE_PROPERTY, 
                                                      &ret);
      ASSERT_OCL_RET(ret, scheduler);
    }
  }
  return 0;
}

// ----------------------------------------------------------
// ocl_scheduler_release()
// ----------------------------------------------------------
inline 
int HAI_scheduler_release(ocl_sheduler_t* scheduler) {
}

inline
int HAI_scheduler_run() {
  uint32_t rid;
  hai_split_t* split;
  
  hai_scheduler_t* scheduler = g_state -> scheduler;

  pthread_mutex_lock( scheduler -> wmutex );
  
  while ( scheduler -> status & HAI_SCHEDULER_STOP ) {
    pthread_cond_wait( &(scheduler -> scheduler_cond), 
                       &(scheduler -> scheduler_mutex) );
    
    rid = NEXT_EMPTY_RESOURCE( scheduler -> resource );
    split = hai_queue_pop();
    enqueue(split, rid);
    mark_resource( scheduler -> resource, rid );
  }
  return 0;
}

#endif
