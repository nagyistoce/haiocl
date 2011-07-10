/*================================================================================
 *
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

// ------- agent.h -------------------
#define HAI_MAX_INIT_LEN    100
#define HAI_MAX_KERNEL_LEN 10240
#define HAI_MAX_AGENTS     20

// ------- mem.h -------------------
#ifndef DEFAULT_KEYTABLE_SIZE
#define DEFAULT_KEYTABLE_SIZE 1024           // 1K initial key size length
#endif

#define HAI_DATA_TRUNK_LEN 41960
#ifndef HAI_DEFAULT_NODE_SIZE 10240          // 10K for each node size
#endif

// ------- ocl.h -------------------
#define HAI_OCL_MAX_DEVICE     10
#define HAI_OCL_MAX_QUEUE      10
#define HAI_OCL_MAX_CONTEXT    10
#define HAI_OCL_SPLITS_SIZE    30

// ------- general ----------------
#ifndef DEFAULT_DEVICE_TYPE
#define DEFAULT_DEVICE_TYPE    CL_DEVICE_TYPE_GPU
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

#define CHK_RET(ret)

#endif
