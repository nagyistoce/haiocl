/*================================================================================
 *
 * DataItem.hpp
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

#ifndef DATA_ITEM_HPP
#define DATA_ITEM_HPP

#include "common.hpp"


namespace Hai {
  class DataItemAbstract : public GeneralSerializer {
  protected:
	// kernel source
    char ksrc_[OCL::Common::MAX_KERNEL_LEN];
	
	// kernel size
    size_t ksize_;
	
	// map key
    TKey mkey_;
	
    // map function data
	deque<TRawData> data_;

	// thread mutex
	PThread::TMutex mutex_;

	// thread conditional variable
	PThread::TCondVar cond_var_;
	
  public:
    // constructor
    inline DataItemAbstract(TKey mkey)
	  :mkey_(mkey) {
	  int ret;
	  
	  ret = PThread::initMutex(&mutex);
	  if (ret) {
	  }

	  ret = PThread::initCondVar(&cond_var_);
	  if (ret) {}
	}
	
	inline ~DataItemAbstract() {
	  PThread::destoryMutex(mutex_);
	  PThread::destoryCondVar(cond_var_);
	}
	
    // get the total size of the data bunk
    size_t getDataSize();

    // fetch the data
    inline size_t getData(char* buf, size_t size) {
	  assert(buf != NULL);
	  
	}

	// get the kernel source
	inline const char* getKernelSrc(size_t* ksize) {
	  *kize = ksize_;
	  return static_cast<const char*>ksrc_;
	};

	// push data into the container
	inline TRet pushData(TBinData* data, size_t size) {
	  data_.push(data);
	};

	// get the map key
	inline TKey getMKey() {
	  return mkey_;
	}

	inline bool hasEnoughData(size_t size) {
	  return data_.size() >= size;
	}
  };
}

#endif
