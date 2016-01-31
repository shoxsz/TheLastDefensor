#ifndef _TIMED_OBJECT_HPP_
#define _TIMED_OBJECT_HPP_

#include "game_thing.hpp"
#include "timer.hpp"
#include "enums.hpp"

class TimedObject : public GameThing{
public:
	/*!!PROBLEM!!*/
	TimedObject(Game* game) : GameThing(game){
		this->ttl = 0;
		t_state = SLEEPING;
	}

	virtual ~TimedObject(){}

	void calculate(){
		if (t_state == ENDED)
			return;

		if (timer.compare(ttl)){
			end();
		}
		else if(t_state == ALIVE){
			step();
		}
	}

	void start(){load(); t_state = TIMER_STATE::ALIVE; timer.start(); }
	void end(){ t_state = ENDED; onEnd(); }

	TIMER_STATE getTState()const{ return t_state; }
	unsigned int getTTL()const{ return ttl; }

protected:
	virtual void step(){}
	virtual void onEnd(){}

	TIMER_STATE t_state;
	Timer timer;
	unsigned int ttl;
};

#endif