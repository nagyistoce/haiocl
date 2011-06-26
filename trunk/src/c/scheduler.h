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
  uint32_t         nQueue[OCL_MAX_PLATFORM];
  uint32_t         nContext;
  
  // -- Thread information ---------------------------
  thread_id_t     ocl_id;
  mutex_t         res_mutex;
  cond_t          res_cond;
  uint32_t        nres;
} ocl_scheduler_t;

int ocl_scheduler_init(ocl_scheduler_t*);
int ocl_scheduler_shutdown(ocl_sheduler_t*);

int ocl_splits_init();
int ocl_splits_shutdown();


static int ocl_profile_platform(cl_platform_id, ocl_platform_t*);
static int ocl_profile_device(cl_platform_id, cl_device_id, ocl_device_t*);

#endif
