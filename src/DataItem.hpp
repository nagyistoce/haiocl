#ifndef DATA_ITEM_HPP
#define DATA_ITEM_HPP

#ifndef MAX_KERNEL_LEN
#define MAX_KERNEL_LEN 10240
#endif

#include "common.hpp"


namespace Hai {
  class DataItem {
  protected:
	// kernel source
    char ksrc_[MAX_KERNEL_LEN];
	
	// kernel size
    size_t ksize_;
	
	// map key
    TKey ikey_;
	
    // map function data
	deque<TRawData> data_;

	// map mutex
    Thread::mutex* dmutex_;
  public:
    // constructor
    DataItem();
	~DataItem();
    // get the size of the data bunk
    size_t getDataSize();

    // fetch the data
    int getData(char* buf, uint32_t size);

	// get the kernel source
	TRET getKernelSrc(const char* kernel);

	// push data into the container
	
	
  };
}

#endif
