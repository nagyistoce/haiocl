#ifndef DATA_POOL_HPP
#define DATA_POOL_HPP

#ifndef MAX_KERNEL_LEN
#define MAX_KERNEL_LEN 10240
#endif

#include "DataItem.hpp"
#include "common.hpp"
#include <map>

namespace Hai {
  class DataPool {
  public:
    static DataPool* getInstance();
	static int freeInstance();
	
    const DataItem* getDataItem(TKEY ikey);
	TRET createDataItem();
	TRET pushData();
	
  private:
    DataPool(const AgentPool*);
	~DataPool();
	TKEY generateKey();
	
    static DataPool* pool_;
	const AgentPool* ap_;
	map<TKEY, DataItem> dimap_;
  };
}

#endif
