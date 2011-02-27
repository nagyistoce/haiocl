#ifndef DATA_ITEM_HPP
#define DATA_ITEM_HPP

#ifndef MAX_KERNEL_LEN
#define MAX_KERNEL_LEN 10240
#endif

namespace Hai {
  class DataItem {
  protected:
    char ksrc[MAX_KERNEL_LEN]_;       // kernel src
    uint32_t ksize_;                  // kernel src length
    uint32_t ikey_;                   // map key
    deque<char> data_;                // map func. data
    Thread::mutex* dmutex_;            // mutex
  public:
    // constructor
    DataItem();

    // get the size of the data bunk
    size_t getDataSize();

    // fetch the data
    int getData(char* buf, uint32_t size);
  };
}

#endif
