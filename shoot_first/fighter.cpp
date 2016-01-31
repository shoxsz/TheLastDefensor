#include "fighter.hpp"

#include "game.hpp"

Fighter::Fighter(Game* game, unsigned short category) : GameThing(game){
	mgun = nullptr;
	this->category = category;
}

Fighter::~Fighter(){
	delete mgun;
}

void Fighter::setLife(float life){
	this->clife = this->life = life;

	if (this->life <= 0){
		state = DEAD;
		onDie();
	}
}

void Fighter::addLife(float life){
	this->clife += life;
	
	if (this->clife <= 0){
		state = DEAD;
		onDie();
	}
}

float Fighter::setDamage(float damage){
	if (state == DEAD)
		return 0.0f;

	float defense = 1 / cdefense;
	clife -= damage * defense;

	if (clife <= 0.0)
		kill();

	return defense * damage;
}

void Fighter::setDefense(float defense){
	this->cdefense = this->defense = defense;
}

void Fighter::addDefense(float defense){
	this->cdefense += defense;
}

void Fighter::kill(){
	addLife(-clife);
}