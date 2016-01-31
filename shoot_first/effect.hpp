#ifndef _EFFECT_
#define _EFFECT_

#include "timed_object.hpp"

class Soldier;

class Effect : public TimedObject{
public:
	Effect(Soldier* target);

	virtual ~Effect(){ destroyBody(); }

	void setTarget(Soldier* target);
	Soldier* getTarget()const{ return target; }

protected:
	Soldier* target;
};

#endif