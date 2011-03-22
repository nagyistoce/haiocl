/*================================================================================
 *
 * Common.hpp
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

#ifndef THREAD_HPP
#define THREAD_HPP


namespace Hai {
  class Thread {
  public:
	// --- Mutex functions -------------------------------
    virtual int createMutex(void*) = 0;
    virtual int lockMutex(void*) = 0;
    virtual int unlockMutex(void*) = 0;
	virtual int destoryMutex(void*) = 0;
	
	// --- Conditon Variables functions -------------------------------
	virtual int wait_for_cond(void*) = 0;
    virtual int init_cond(void*) = 0;

	inline Thread(TThread id)
	  : thread_id_(id) {
	}
	
	inline TThreadId getThreadId() {
	  return thread_id;
	}
	
  protected:
	typedef int TThreadId;

	TThreadId thread_id_;
  };
}
#endif
