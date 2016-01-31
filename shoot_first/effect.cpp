#include "effect.hpp"

#include "soldier.hpp"

Effect::Effect(Soldier* target) : TimedObject(target->getGame()){
	setTarget(target);
}

void Effect::setTarget(Soldier* target){
	this->target = target;
}