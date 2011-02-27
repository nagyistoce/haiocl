#ifndef THREAD_HPP
#define THREAD_HPP


namespace Hai {
  class Thread {
  public:
    virtual int createMutex(void*) = 0;
    virtual int lockMutex(void*) = 0;
    virtual int releaseMutex(void*) = 0;
    
  };
}
#endif
