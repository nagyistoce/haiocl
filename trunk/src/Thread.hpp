#ifndef THREAD_HPP
#define THREAD_HPP

namespace Hai {

  class Thread {
  public:
	inline Thread() {
	  int ret;
	  ret = pthread_attr_init(&attr);
	  if (ret) {
		// TODO:
	  }
	  
	  ret = pthread_create(&thread, &attr, Thread::entryPoint, this);
	  if (ret) {
		// TODO: 
	  }
	}

	virtual int run() = 0;
	
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
