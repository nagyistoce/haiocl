/*================================================================================
 *
 * GeneralSerializer.hpp
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

#ifndef GENERAL_SERIALIZER_HPP
#define GENERAL_SERIALIZER_HPP


#include "Common.hpp"

namespace Hai {
  namespace IO {
	template<Split_T>
	class GeneralSerializer {
	public:
	  virtual TRet serializeToBinary(Split_T* pBin, size_t size) = 0;
	}
  }
}

#endif
