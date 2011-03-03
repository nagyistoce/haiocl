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
	// -- instance -------------------------------------
    static OCL* getInstance();
    static int freeInstance();

	struct OCLMap {
	  // -- NDRange parameters ----------------------------
	  cl_kernel* kernel;
	  cl_uint work_dim;
	  size_t* global_work_offset;
	  size_t* global_work_size;
	  size_t* local_work_size;
	  cl_uint num_events_in_wait_list;
	  const cl_event* event_wait_list;
	  cl_event *event;

	  // --inputs and outputs ------------------------------
	  cl_mem in_binary;
	  cl_mem in_schema;
	  cl_mem in_size;

	  cl_mem out_binary;
	  cl_mem out_schema;
	  cl_mem out_size;
	  
	  // -- callback func ----------------------------------
	  OCLKernelCallBack kcb;
	  OCLMemoryDescBack mdb;

	  OCLMap();
	};

	TRet initOCL();
	TRet compileKernel(const char* ksrc, size_t ks, void* kbin);

	
  private:
    OCL() {}
    ~OCL() {}
	struct CL_Context {
	};
	
	struct CL_Device {
	  cl_uint address_bits;
	  cl_bool device_available;
	  cl_bool compiler_available;
	  cl_bool endian_little;
	  cl_bool correction_support;
	  char extensions[MAX_CL_INFO];
	  cl_ulong global_mem_cache_size;
	  cl_ulong global_mem_cache_type;
	  cl_uint global_mem_cacheline_size;
	  cl_ulong global_mem_size;
	  // TODO: to fill the complete fields


	  cl_device_id id;
	  inline CL_Device(cl_device_id _id) : id(_id) {}
	  inline cl_int init() {}
	};
	
	struct CL_Platform {
	  char profile[MAX_CL_INFO];
	  char version[MAX_CL_INFO];
	  char name[MAX_CL_INFO];
	  char vendor[MAX_CL_INFO];
	  char extension[MAX_CL_INFO];
	  cl_platform_id id;

	  inline CL_Platform(cl_platform_id _id) : id(_id) {}
	  cl_int init();
	};

	// -- OpenCL Env. IDs ---------------------------------------
    cl_platform_id   platform_id[OCL_MAX_PLATFORM];
    cl_device_id     device_id[OCl_MAX_PLATFORM][OCL_MAX_DEVICE];
    cl_command_queue queue[OCL_MAX_QUEUE];
    cl_context       context[OCL_MAX_CONTEXT];

	// -- OpenCL Env. Info ---------------------------------------
    CL_Platform      platforms[OCl_MAX_PLATFORM];
    cl_Device        devices[OCl_MAX_PLATFORM][OCL_MAX_DEVICE];
    cl_command_queue queue[OCL_MAX_QUEUE];
    cl_context       context[OCL_MAX_CONTEXT];
	
	// -- Number of OpenCL env. ---------------------------------------
	cl_uint          nPlatform;
	cl_uint          nDevice[OCL_MAX_PLATFORM];
	cl_uint          nQueue;
	cl_uint          nContext;
	
	// -- Map class definition -------------------------------------
	// -- Number of Instance ---------------------------------------
    static OCL* oclInstance;
  };
}
#endif
