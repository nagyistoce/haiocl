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
#include <HAI/hai.h>


struct hai_scheduler_t {
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
  uint64_t         dev_status;
  uint32_t         nres;

  // -- General information ---------------------------
  uint32_t        status;
  sem_t			  sch_sem;
} ;

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
  CHK_RET(ret, scheduler);
  HAI_log("%d platforms fetched.", scheduler -> nPlatform);
  
  scheduler -> nResource = 0;
  for (i = 0; i < scheduler -> nPlatform; i ++) {
    clGetPlatformInfo(scheduler -> platform_id[i], 
                      CL_PLATFORM_NAME, 1024, buf, NULL);
    HAI_log("Platform %d : %s\n", i, buf);
    
    ret = clGetDeviceIDs(scheduler -> platform_id[i], 
                         CL_DEVICE_TYPE_ALL, 
                         HAI_MAX_DEVICE, 
                         scheduler -> device_id[i],
                         scheduler -> nDevice + i);
    CHK_RET(ret);

    HAI_log("Platform %d : %d devices is found.\n", i, scheduler -> nDevice[i]);
    nres += scheduler -> nDevice[i];

    // create context
    scheduler -> context[i] = clCreateContext(NULL, scheduler -> nDevice, 
                                              scheduler -> device_id[i], 
                                              context_notify, 
                                              i, 
                                              &ret);
    CHK_RET(ret);
    
    for (j = 0; j < scheduler -> nDevice[i]; j ++) {
      clGetDeviceInfo(scheduler -> device_id[i][j], 
                      CL_DEVICE_VENDOR, 
                      1024, 
                      buf, 
                      NULL);
      HAI_log("VENDOR: %s\n", buf);
      scheduler -> queue[i][j] = clCreateCommandQueue(scheduler -> context[i], 
                                                      scheduler -> device_id[i], 
                                                      OCL_PROFILE_PROPERTY, 
                                                      &ret);
      CHK_RET(ret);
    }
	
	// initialize the semaphores
	sem_init(&(scheduler -> sch_sem), 0, nres);
  }
  return 0;
}

// ----------------------------------------------------------
// ocl_scheduler_release()
// ----------------------------------------------------------
#define HAI_scheduler_release() HAI_scheduler_release_(g_state -> scheduler)
inline 
int HAI_scheduler_release_(ocl_sheduler_t* scheduler) {
	for (int i = 0; i < nPlatform; i ++) {
		for (int j = 0; j < nDevice[i]; j ++)
			clReleaseCommandQueue(queue[i][j]);
		clReleaseContext(context[i]);
		
	sem_destroy(&(scheduler -> sch_sem));
	return 0;
}

// ----------------------------------------------------------
// ocl_enqueue_split()
// ----------------------------------------------------------
#define HAI_enqueue_split(x) HAI_enqueue_split_(g_state -> scheduler, x)
inline 
int HAI_enqueue_split_(ocl_sheduler_t* scheduler, hai_split_t split) {
	
}

// ----------------------------------------------------------
// HAI_scheduler_wait()
// ----------------------------------------------------------
#define HAI_scheduler_wait() HAI_scheduler_wait(g_state -> scheduler)

inline
void HAI_scheduler_wait_(hai_scheduler_t* scheduler) {
	sem_wait(&(scheduler -> sch_sem))
}

// ----------------------------------------------------------
// HAI_next_resoure()
// ----------------------------------------------------------
#define HAI_next_resource() HAI_next_resource(g_state -> scheduler)

inline
int HAI_next_resource_(hai_scheduler_t* scheduler) {
	for (int i = 0; i < 64u; i ++) {
		if (scheduler -> dev_status & (1u << i))
			return i;
	return -1;
}

// ----------------------------------------------------------
// HAI_mask_resource()
// ----------------------------------------------------------
#define HAI_mask_resource(x) HAI_set_resource(g_state -> scheduler, x, 1)
#define HAI_unmask_resource(x) HAI_set_resource(g_state -> scheduler, x, 0)

static inline
void HAI_set_resource(hai_scheduler* scheduler, int p, bool v) {
	if (v)
		scheduler -> dev_status |= 1u << p;
	else
		scheduler -> dev_status ^= 1u << p;
}

// ----------------------------------------------------------
// HAI_mask_resource()
// ----------------------------------------------------------
inline
int HAI_next_resource_(hai_scheduler_t* scheduler) {
	for (int i = 0; i < 64u; i ++) {
		if (dev_status & (1u << i))
			return i;
	return -1;
}

static inline
bool is_scheduler_stopped(hai_scheduler_t* scheduler) {
	return scheduler -> status & SCHEDULER_STOPPED;
}

// ----------------------------------------------------------
// HAI_scheduler_run()
// ----------------------------------------------------------
inline
int HAI_scheduler_run() {
  uint32_t rid;
  hai_split_t* split;
  
  hai_scheduler_t* scheduler = g_state -> scheduler;

  while ( is_scheduler_stopped(scheduler) ) {
	HAI_queue_wait();
	if (is_scheduler_stopped(scheduler))
		break;
	
	split = hai_queue_pop();
	
	hai_scheduler_wait();
    if (is_scheduler_stopped())
		break;
		
    rid = HAI_next_resource();
	HAI_mask_resource(rid);
    HAI_enqueue_split(split, rid);
  }
  return 0;
}

#endif
