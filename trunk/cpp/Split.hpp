/*================================================================================
 *
 * Split.hpp
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

#ifndef SPLIT_T
#define SPLIT_T

#include "Common.hpp"
#include "io/io.hpp"

struct Split {
  void*     kernel;     // input kernel
  TKey      in_key;     // Map key
  TRawData* in_dat;     // input binary data
  ushort*   in_schema;  // input schema description 
  size_t    in_size;    // input data size
  size_t    out_size;   // output data size
};


#end
