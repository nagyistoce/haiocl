#ifndef DATA_ITEM_HPP
#define DATA_ITEM_HPP

#ifndef MAX_KERNEL_LEN
#define MAX_KERNEL_LEN 10240
#endif

namespace Hai {

  class DataItem {
  protected:
	char ksrc[MAX_KERNEL_LEN]_;
	uint32_t ksize_;
	uint32_t ikey_;
	deque<char> data_;
	Thread::mutex dmutex_;
  public:
	inline DataItem();
	inline size_t getSize() { return data.size(); };
	int getData(char* buf, uint32_t size) {
	}
	
  };


  class DataPool {
  public:
	DataPool();
	int createTask();
	const DataItem* getDataItem(uint32_t ikey);
  private:
	
  };
}

#endif
