#ifndef OCL_HPP
#define OCL_HPP

#include "common.hpp"
#include <queue>

extern "C" {
#include <CL/opencl.h>
}

namespace Hai {
  class OCL {
  public:
    static OCL* getInstance();
    static int freeInstance();

	TRET initOCL();
	TRET compileKernel(const char* ksrc, size_t ks, void* kbin);

	
  private:
    OCL() {}
    ~OCL() {}
    cl_platform_id   platform_id;
    cl_device_id     device_id[OCL_MAX_DEVICE];
    cl_command_queue queue[OCL_MAX_QUEUE];
    cl_context       context[OCL_MAX_CONTEXT];
    static OCL* oclInstance;

  };
}
#endif
