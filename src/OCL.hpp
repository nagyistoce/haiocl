#ifndef OCL_HPP
#define OCL_HPP

#ifndef OCL_MAX_DEVICE
#define OCL_MAX_DEVICE 10
#endif

#ifndef OCL_MAX_CONTEXT
#define OCL_MAX_CONTEXT 10
#endif

#ifndef OCL_MAX_QUEUE
#define OCL_MAX_QUEUE 10
#endif

#ifndef OCL_MAX_PLATFORM
#define OCL_MAX_PLATFORM 10
#endif

extern "C" {
#include <CL/opencl.h>
}


class OCL {
public:
  inline OCL() {}
  inline uint32_t oclInit() {
	cl_int ret;
	cl_uint np, nd;
	uint32_t i, j;
	char buf[1024];
	ret = clGetPlatformIDs(1, platform_id_, &nPlatform_);
	if (ret != CL_SUCCESS) 
	  return OCL::oclErrLookup(ret);

	logger << np << " platforms fetched." << std::endl;
	for (i = 0; i < nPlatform_; i ++) {
	  // create all the platforms
	  clGetPlatformInfo(platform_id[i], CL_PLATFORM_NAME, 1024, buf, NULL);
	  logger << i << ": " << buf << std::endl;

	  // create all the devices for each platform
	  ret = clGetDeviceIDs(platform_id_[i], DEVICE_TYPE, 1, device_id[i], &nDevice_);
	  if (ret != CL_SUCCESS) 
		return oclErrLookup(ret);
	  
	  logger << nd << " devices is found in platform " << i << std::endl;
	  
	  for (j = 0; j < nDevice_; j ++) {
		clGetDeviceInfo(device_id_[i][j], CL_DEVICE_VENDOR, 1024, buf, NULL);
		logger << i << ": " << buf << std::endl;

		// create the context and queue for each device in each platform
		context_[i][j] = clCreateContext(NULL, 1, device_id_[i] + j, NULL, NULL, &ret);
		if (ret != CL_SUCCESS) return oclErrLookup(ret);


		queue = clCreateCommandQueue(context_[i] + j, device_id_[i][j], PROFILE_PROPERTY, &ret);
		if (ret != CL_SUCCESS) return oclErrLookup(ret)
	  }
	}
	
	return 0u;
  }

  inline ~OCL() {}
private:
  cl_platform_id   platform_id_[OCL_MAX_PLATFORM];
  cl_device_id     device_id_[OCL_MAX_PLATFORM][OCL_MAX_DEVICE];
  cl_command_queue queue_[OCL_MAX_PLATFORM][OCL_MAX_QUEUE];
  cl_context       context_[OCL_MAX_PLATFORM][OCL_MAX_CONTEXT];
  uint32_t         nPlatform_;
  uint32_t         nDevice_;
};

#endif
