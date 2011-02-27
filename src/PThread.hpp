#ifndef PTHREAD_HPP
#define PTHREAD_HPP

#include "Thread.hpp"

namespace Hai {
  class PThread : Thread {
  public:
    inline PThread() {
      int ret;
      ret = pthread_attr_init(&attr);
      if (ret) {
	// TODO:
      }
	  
      ret = pthread_create(&thread, &attr, 
			   Thread::entryPoint, this);
      if (ret) {
	// TODO: 
      }
    }

    virtual int run() = 0;
    int createMutex(void* mutex);
    int lockMutex(void* mutex);
    int releaseMutex(void* mutex);
    
  protected:
    static void *entryPoint(void *);
    pthread_t thread;
    pthread_attr_t attr;
  };

  void* entryPoint(void *pt) {
    pt -> run();
    pthread_exit(NULL);
  }
}
#endif
