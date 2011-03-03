#include "OCL.hpp"

namespace Hai {
  static OCL* OCL::getInstance() {
	if (OCL::oclInstance == NULL) {
	  OCL::oclInstance = new OCL();
	}
	return OCL::oclInstance;
  }

  static int OCL::freeInstance() {
	return 0;
  }

  OCL::OCL() {
	cl_int ret;
	cl_uint i;
	// initialize platform_id
	log << "initialize platform\n";
	ret = clGetPlatformIDs(OCL_MAX_PLATFORM, platform_id, &nPlatform);
	if (ret != CL_SUCCESS) {
	}

	// initialize device_id
	for (i = 0; i < nPlatform; i ++) {
	  clGetDeviceIDs(platform_id[i], CL_DEVICE_TYPE_ALL, OCL_MAX_DEVICE,
					 device_id[i], nDevice[i]);
	}
	// initialize queue_id
  
	// initialize context
  }

  // -- OCL::CL_Platform --------------------------------
  inline cl_int OCL::CL_Platform::init() {
	cl_int ret;
	size_t retSize;
	ret = clGetPlatformInfo(id, CL_PLATFORM_PROFILE, 
							MAX_CL_INFO, profile, &retSize);
	if (ret != CL_SUCCESS) {
	}

	ret = clGetPlatformInfo(id, CL_PLATFORM_VERSION,
							MAX_CL_INFO, version, &retSize);
	if (ret != CL_SUCCESS) {}

	ret = clGetPlatformInfo(id, CL_PLATFORM_NAME,
							MAX_CL_INFO, name, &retSize);
	if (ret != CL_SUCCESS) {}

	ret = clGetPlatformInfo(id, CL_PLATFORM_NAME,
							MAX_CL_INFO, vendor, &retSize);
	if (ret != CL_SUCCESS) {}
		
	ret = clGetPlatformInfo(id, CL_PLATFORM_NAME,
							MAX_CL_INFO, extensions, &retSize);
	if (ret != CL_SUCCESS) {}
	return ret;
  }
};
}
