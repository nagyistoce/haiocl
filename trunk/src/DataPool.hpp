#ifndef DATA_ITEM_HPP
#define DATA_ITEM_HPP

#ifndef MAX_KERNEL_LEN
#define MAX_KERNEL_LEN 10240
#endif

namespace Hai {

  struct DataItem {
	char ksrc[MAX_KERNEL_LEN];
	uint32_t ksize;
	uint32_t ikey;
	deque<char> data;
  
	inline size_t getSize() { return data.size(); };
  };


  class DataPool {
  public:
	DataPool();
	int createTask();
	int pushData(uint32_t ikey);
	int createDataItem();
  private:
	
  };
}

#endif
