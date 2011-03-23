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

  nPlatform = nQueue = nContext = 0;
  
  ret = clGetPlatformIDs(HAI_OCL_MAX_PLATFORM, 
                         ocl -> platform_id, 
                         &(ocl -> nPlatform));
  if (ret != CL_SUCCESS) {}
  HAI_LOG("%d platform found.", ocl -> nPlatform);

  // initialize device_id
  for (i = 0; i < nPlatform; i ++ ){
    clGetDeviceIDs(ocl -> platform_id[i], 
                   DEFAULT_DEVICE_TYPE, 
                   HAI_OCL_MAX_DEVICE, 
                   ocl -> device_id[i], 
                   ocl -> nDevice[i]);
    if (ret != CL_SUCCESS) {}
    ocl -> nres += nDevice[i];
    ocl -> nQueue[i] = ocl -> nDevice[i];
  }
  HAI_LOG("%d GPU found as devices.", ocl -> nres);

  //
  // TODO: to create context for each device
  //
  nContext = 1;
  context[0] = clCreateContextFromType(NULL,
                                       DEFAULT_DEVICE_TYPE,
                                       NULL,
                                       NULL,
                                       0,
                                       NULL,
                                       &ret);
  CHK_RET(ret);
  //
  // initialize ocl queue
  //
  for (i = 0; i < ocl -> nPlatform; i ++)
    for (j = 0; j < ocl -> nDevice; j ++) {
      queue[i][j] = clCreateCommandQueue(context[i],
                                         ocl -> device_id[i][j],
                                         0,
                                         &ret);
      CHK_RET(ret);
    }
     
  return 0;
}
