#ifndef DATA_POOL_HPP
#define DATA_POOL_HPP

#include "DataItem.hpp"
#include "common.hpp"
#include <map>

namespace Hai {
  class DataPool {
  public:
    static DataPool* getInstance();
	static int freeInstance();
	
    DataItem* getDataItem(TKEY ikey);
	TRET createDataItem();
	
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
