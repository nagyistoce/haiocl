#ifndef AGENT_HPP
#define AGENT_HPP

namespace Hai {
  class Agent : Thread {
  public:
	enum AgentStatus {
	  AGENT_HAS_NO_TASK = 0,
	};
	
	inline Agent(DataPool* datapool, OCL* ocl, uint32_t bufsize)
	  : ikey_(0u), datapool(datapool_),
		ocl_(ocl), status_(0), bufsize_(bufsize) {
	}
	
	int run() {
	  int ret;
	  // create agent
	  if (status_ == STATUS_NO_AGENT_RUNNING) {
		ret = datapool_ -> createTask(&ikey_);
		if (ret) {
		  // TODO:
		}

		ocl -> registerAgent();
	  }

	  // fetch data
	  const DataItem* di = datapool_ -> getDataItem(ikey_);
	  ret = di -> getData(databuf_, bufsize_);
	  if (ret != 0) {
		// TODO:
	  }

	  // push for data
	  
	  
	}

	inline int setBufferSize(uint32_t bufsize) {
	  bufsize_ = bufsize;
	}

  protected:
	DataPool* datapool_;
	OCL* ocl_;
	AgentStatus status_;
	uint32_t ikey_;
	char* databuf_;
	uint32_t bufsize_;
  };
}
#endif
