/*================================================================================
 *
 * Agent.hpp
 *
 * Author:
 *   Si Yin <zyzyis@gmail.com>
 *
 * Copyright (C) 2011 Hai Computing
 *
 * This file is released under the terms of the GNU General Public License
 * versions 3.0. Please refers to the file COPYING for more information.
 *================================================================================
 */
#ifndef AGENT_HPP
#define AGENT_HPP

namespace Hai {
  class Agent : Thread {
  public:
	enum AgentStatus {
	  AGENT_HAS_NO_DATA = 0,
	  AGENT_IS_BUSY = 1
	};
	
	inline Agent()
	  : thread_run_flag(true) {
	}

	TRet init() {
	  TRet ret;
	  OCL* ocl = OCL::getInstance();

	  // initialize the kernel
	  if (kernel_ == null) {
		ret = ocl -> compileKernel(dataitem -> getKSrc(),
								   dataitem -> getKSize(),
								   kernel_);
	  }

	}
	
	int run() {
	  TRET ret;
	  OCLSon* oclson;
	  OCL* ocl = OCL::getInstance();
	  OCLTask* ocltask;

	  while( thread_end_flag ) {
		if (dataitem -> hasEnoughData(dsize)) {
		  wait();
		}
		
		ret = dataitem_ -> getData(databuf_, dsize);
		if (ret) {
		}
		
		oclson = dataitem_ -> serializeToOCLSON(databuf_, dsize, &ret);
		if (ret) {
		}

		ocltask = ocl -> createOCLTask(oclson, ret);
		if (ret) {
		}

		tret = ocltask -> setOutputKey(okey);
		if (ret) {
		}
		
		ret = ocl -> pushOCLTask(oclson);
		if (ret) {
		}
	  }
	}

	inline int setBufferSize(size_t bufsize) {
	  bsize_ = bufsize;
	}


  protected:
	PThread::TCondVar cond_var;
	PThread::TMutex   mutex;

	DataItem* dataitem_;

	// agent status
	AgentStatus status_;

	// associated map input key
	TKey mkey_;

	// associated map output keys
	TKey okey[1];
	
	// data to be processed
	TRawData databuf_[MAX_DATA_SIZE];

	// data size
	size_t dsize_;

	// check if thread is still running
	bool thread_run_flag;
  };
}
#endif
