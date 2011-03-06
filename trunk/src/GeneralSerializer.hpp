#ifndef GENERAL_SERIALIZER_HPP
#define GENERAL_SERIALIZER_HPP


#include "Common.hpp"

namespace Hai {
  namespace IO {
	class GeneralSerializer {
	public:
	  GeneralSerializer();
	  virtual TRet serializeToBinary(void* pBin, size_t size) = 0;
	}
  }
}

#endif
