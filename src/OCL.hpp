#ifndef OCL_HPP
#define OCL_HPP

#ifndef OCL_MAX_DEVICE
#define OCL_MAX_DEVICE 10
#endif

extern "C" {
#include <CL/opencl.h>
}


class OCL {
public:
  inline OCL() {}
  inline ~OCL() {}
private:
  cl_platform_id platform_id;
  cl_device_id device_id[OCL_MAX_DEVICE];
  cl_command_queue queue;
  cl_context context;
  
  
};

#endif
