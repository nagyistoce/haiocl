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

	TRet initOCL();
	TRet compileKernel(const char* ksrc, size_t ks, void* kbin);
	
  private:
    OCL() {}
    ~OCL() {}

	// -- OpenCL Context -------------------------------------
	struct CL_Context {
	};

	// -- OpenCL Devices -------------------------------------
	enum Device_Status {
	  FREE = 0, BUSY = 1
	}
	  
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

	//TO Improve: instead of using device, make it an abstract resource
	Device_Status status_[OCL_MAX_PLATFORM][OCL_MAX_DEVICE];
	
	inline Device_status getDeviceStatus(unsigned int pid, unsigned int did) {
	  return status[pid][did];
	}

	inline void setDeviceStatusBusy(unsigned int pid, unsigned int did) {
	  status[pid][did] = BUSY;
	}

	inline void setDeviceStatusFree(unsigned int pid, unsigned int did) {
	  status[pid][did] = FREE;
	}
	
	inline TRet getNextFreeDevice(cl_device_id* device_id) {
	}
	
	// -- CL_Platform -------------------------------------
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
	queue<OCLTask>  taskQueue;
	
	// -- Everything static  ---------------------------------------
    static OCL* oclInstance;

	/**
	 * taskCallBack() : callback function for OpenCL kernels
	 */
	static void taskCallBack();
  };
}
#endif
