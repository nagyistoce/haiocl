/*================================================================================
 *
 * PThread.hpp
 *
 * Author:
 *   Si Yin <zyzyis@gmail.com>
 *
 * Copyright (C) 2010 Hai Computing
 *
 * This file is released under the terms of the GNU General Public License
 * versions 3.0. Please refers to the file COPYING for more information.
 *================================================================================
 */
#ifndef PTHREAD_HPP
#define PTHREAD_HPP

#include "Thread.hpp"

namespace Hai {
  class PThread : public Thread {
  public:
	typedef pthread_mutex_t TMutex;
	typedef pthread_cond_t  TCondVar;

    inline PThread() {
      int ret;
      ret = pthread_attr_init(&attr);
      if (ret) {
		// TODO:
      }
	  
      ret = pthread_create(&thread, &attr, PThread::entryPoint, this);
      if (ret) {
		// TODO: 
      }
    }

    virtual int run() = 0;

    inline int initMutex(void* mutex) {
	  return pthread_mutex_init(static_cast<TMutex*>mutex);
	}
	
    inline int lockMutex(void* mutex) {
	  return pthread_mutex_lock(static_cast<TMutex*>mutex);
	}
	
    inline int unlockMutex(void* mutex) {
	  return pthread_mutex_unlock(static_cast<TMutex*>mutex);
	}

	inline TThreadId getThreadId() {
	  return thread_id;
	}

  protected:
	typedef TThread     pthread_t;
	typedef TThreadAttr pthread_attr_t;
	
    static void *entryPoint(void *);

	
    TThread thread;
    TThreadAttr attr;
  };

  void* entryPoint(void *pt) {
    pt -> run();
    pthread_exit(NULL);
  }
}
#endif
