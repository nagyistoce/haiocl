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
#ifdef HAI_DEBUG
#define MAKE_NAME(...) #__VA_ARGS__

#define HAI_log(format, ...) \
  fprintf(stdout, MAKE_NAME(%s, %d, format), __FILE__, __LINE__, ...)
#else
#define HAI_log(format, ...)
#endif

// ----------------------------------------------------------
// HAI_error
// ----------------------------------------------------------
inline
void HAI_error(int errorno) {
	
}

// ----------------------------------------------------------
// HAI_read_source_file
//
// Read kernel source from file on the disk.
// ----------------------------------------------------------
char* HAI_read_source_file(const char* filename, size_t* size) {
	FILE *fp;
	struct stat fp_stat;
	if ((fp = fopen(filename, "r")) == NULL) {
		HAI_log("Can't find the file.");
		return NULL;
	}
	
	if (fstat(fileno(fp), &fp_stat) < 0) {
		HAI_log("fstat failed.");
		return NULL;
	}
	
	size_t fp_size = fp_stat.st_size;
	char* buf = (char*)malloc(fp_size);
	*size = fread(buf, fp_size, 1, fp);
	fclose(fp);
	return buf;
}

#endif
