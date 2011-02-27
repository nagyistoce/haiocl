#include "DataItem.hpp"


inline DataItem::DataItem() {
}

inline size_t DataItem::getDataSize() {
  return data.size();
}

inline size_t DataItem::getData(char* buf, uint32_t size) {
  thread_proxy -> lockMutex(mutex);
  // fetch the data in a fast way
  thread_proxy -> releaseMutex(mutex);
}
