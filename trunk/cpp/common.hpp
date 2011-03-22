/*================================================================================
 *
 * Common.hpp
 *
 * Author:
 *   Si Yin <zyzyis@gmail.com>
 *
 * Copyright (C) 2010 Hai Computing
 *
 * This file is released under the terms of the GNU General Public License
 * versions 3.0. Please refers to the file COPYING for more information.
 *================================================================================
 */

#ifndef HAI_COMMON_HPP
#define HAI_COMMON_HPP

#include <cstdint>
#include <iostream>
#include <cassert>


namespace Hai {
  class Common {
	
	typedef uint32_t TKey;
	typedef int TRet;
	typedef char TBinData;

	static const int OCL_MAX_DEVICE = 10;
	static const int OCL_MAX_CONTEXT = 10;
	static const int OCL_MAX_QUEUE = 10;
	static const int OCL_MAX_KERNEL_LEN = 10240;
  };
}

#endif
