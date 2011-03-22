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
#define HAI_MAX_KEY_LEN    100
#define HAI_MAX_KERNEL_LEN 10240
#define HAI_MAX_AGENTS     20

// ------- mem.h -------------------
#define HAI_DATA_TRUNK_LEN 41960


// ------- ocl.h -------------------
#define HAI_OCL_MAX_DEVICE     10
#define HAI_OCL_MAX_QUEUE      10
#define HAI_OCL_MAX_CONTEXT    10
#define HAI_OCL_SPLITS_SIZE    30

// ------- log & error -------------
#ifdef _DEBUG
#define log(format, content) printf(format, content)
#else
#define log(format, content)
#endif


#endif
