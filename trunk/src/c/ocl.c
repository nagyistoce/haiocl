/*================================================================================
 *
 * ocl.c
 *
 * Author:
 *   Si Yin <zyzyis@gmail.com>
 *
 * Copyright (C) 2011 Hai Computing
 *
 * This file is released under the terms of the GNU General Public License
 * versions 3.0. Please refers to the file COPYING for more information.
 *================================================================================
 */

#include "ocl.h"

// ------------------------------------------------------------
// ocl_splits_init
// : initialize the OCL split queue.
// ------------------------------------------------------------
int ocl_splits_init(ocl_split_t* ocl) {
  return 0;
}

// ------------------------------------------------------------
// ocl_scheduler_init
// : initialize OpenCL environment.
// ------------------------------------------------------------
int ocl_scheduler_init(ocl_scheduler_t* ocl) {
  // initialize the platform
  cl_int ret;
  cl_uint i, j, k;
  ret = clGetPlatformIDs(HAI_OCL_MAX_PLATFORM, 
                         ocl -> platform_id, 
                         &(ocl -> nPlatform));
  if (ret != CL_SUCCESS) {}

  // initialize device_id
  k = 0;
  for (i = 0; i < nPlatform; i ++ ){
    clGetDeviceIDs(ocl -> platform_id[i], 
                   CL_DEVICE_TYPE_ALL, 
                   HAI_OCL_MAX_DEVICE, 
                   ocl -> device_id[i], 
                   ocl -> nDevice[i]);
    if (ret != CL_SUCCESS) {}
  }

  // initialize context
  for (i = 0; i < nPlatform; i ++) {
    context[i] = clCreateContext(NULL, 
                                 ocl -> nDevice[i], 
                                 ocl -> device_id[i]
                                 NULL, // TODO: error handling
                                 NULL,
                                 &ret);
    check_ret(ret);
  }
  
  // initialize ocl queue
  ret = 
}
ret = clGetPlatformIDs(HAI_OCL_MAX_PLATFORM
                       return 0;
                       }
