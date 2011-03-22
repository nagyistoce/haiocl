#ifndef AGENT_POOL_HPP
#define AGENT_POOL_HPP

#include <map>
#include "common.hpp"

namespace Hai {
  class AgentPool {
  public:
	// -- instance mgt -------------------------
	static AgentPool* getInstance();
	static int freeInstance();

	// -- method -------------------------
	/*
	 * create a new agent
	 */
	int createNewAgent(TKEY);
	
  private:
	AgentPool();
	~AgentPool();
	static AgentPool* ap_;
	map<TKEY, Agent*> agmap_;
  };
}

#endif
