#ifndef HAI_COMMON_HPP
#define HAI_COMMON_HPP

#include <cstdint>
#include <cstdio>
using namespace std;

#define TKey uint32_t
#define TRet int
#define TBinData char

#ifndef OCL_MAX_DEVICE
#define OCL_MAX_DEVICE 10
#endif

#ifndef OCL_MAX_CONTEXT
#define OCL_MAX_CONTEXT 10
#endif

#ifndef OCL_MAX_QUEUE
#define OCL_MAX_QUEUE 10
#endif

#ifndef MAX_KERNEL_LEN
#define MAX_KERNEL_LEN 10240
#endif

#define log cout

#endif
