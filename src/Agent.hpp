#ifndef AGENT_HPP
#define AGENT_HPP

namespace Hai {
  class Agent : Thread {
  public:
	enum AgentStatus {
	  AGENT_HAS_NO_DATA = 0,
	  AGENT_IS_BUSY = 1
	};
	
	inline Agent(DataPool* datapool, OCL* ocl, uint32_t bufsize)
	  : ikey_(0u), datapool(datapool_),
		ocl_(ocl), status_(0), bsize_(bufsize) {
	}
	
	
	int run() {
	  TRET ret;

	  void* kernel;
	  ret = ocl_ -> compileKernel(dataitem_ -> getKSrc(),
								  dataitem_ -> getKSize(),
								  kernel);
	  
	  while( 1 ) {
		ret = dataitem_ -> getData(data_buf_, bsize);
		if (ret != HAI_SUCCESS) {
		}

		ret = ocl_ -> setTask(kernel. databuf_, bsize_);
	  }
	}

	inline int setBufferSize(size_t bufsize) {
	  bsize_ = bufsize;
	}

  protected:
	DataItem* dataitem_;
	OCL* ocl_;

	// agent status
	AgentStatus status_;

	// associated map key
	TKEY ikey_;

	// data to be processed
	TRawData* databuf_;

	// data size
	size_t bsize_;
  };
}
#endif
