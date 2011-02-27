#ifndef DATA_ITEM_HPP
#define DATA_ITEM_HPP

#ifndef MAX_KERNEL_LEN
#define MAX_KERNEL_LEN 10240
#endif

namespace Hai {
  class DataPool {
  public:
    static DataPool* getInstance();
    int createTask();
    const DataItem* getDataItem(uint32_t ikey);
  private:
    DataPool();
    static DataPool* pool;
  };
}

#endif
