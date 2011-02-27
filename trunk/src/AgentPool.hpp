#ifndef AGENT_POOL_HPP
#define AGENT_POOL_HPP

#include <map>

namespace Hai {
  class AgentPool {
  public:
	static AgentPool* getInstance();
	static int freeInstance();

	int createNewAgent();
	
  private:
	AgentPool();
	~AgentPool();
	static AgentPool* ap_;
	map<TKEY, Agent*> agmap_;
  };
}

#endif
