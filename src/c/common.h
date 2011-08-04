/*================================================================================
 * common.h
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
#ifndef HAI_COMMON_H
#define HAI_COMMON_H

#include <stdint.h>
#include <stdio.h>

// ------- ocl.h -------------------
#define HAI_MAX_PLATFORM	   10
#define HAI_MAX_DEVICE     	   10
#define HAI_MAX_QUEUE          10

// ------- general ----------------
#ifndef HAI_DEFAULT_DEVICE_TYPE
#define HAI_DEFAULT_DEVICE_TYPE    CL_DEVICE_TYPE_GPU
#endif

// ------- log & error -------------
#ifdef _DEBUG
#define HAI_LOG(format, msg) \
  log_("Log", format, msg)

#define log_(type, format, msg)                   \
  printf("#type %s, %4d: ", __FILE__, __LINE__);  \
  printf(format, msg);                            \
  puts("");

#else
#define HAI_LOG(format, msg)
#endif

#define CHK_RET(ret) \
	if (ret != CL_SUCCESS) \
		HAI_error(ret)

// ----------------------------------------------------------
// HAI_error
// ----------------------------------------------------------
void HAI_error(int errorno) {
}

// ----------------------------------------------------------
// HAI_register_kernel
// ----------------------------------------------------------
char* HAI_read_source_from_file(const char* filename, size_t* size) {
}
#endif
