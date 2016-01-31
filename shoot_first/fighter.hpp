#ifndef _FIGHTER_
#define _FIGHTER_

#include "2d_camera.hpp"
#include "game_thing.hpp"
#include "shoot.hpp"
#include "enums.hpp"

class Fighter : public GameThing{
public:
	Fighter(Game* game, unsigned short category);
	virtual ~Fighter();

	void setLife(float life);
	void addLife(float life);
	float getLife()const{ return life; }
	float getCurrentLife()const{ return clife; }

	float setDamage(float damage);
	void setDefense(float defense);
	void addDefense(float defense);
	float getDefense()const{ return defense; }
	float getCurrentDefense()const{ return cdefense; }

	void kill();

	MachineGun* getMachineGun()const{ return mgun; }

	void setState(STATE state){ this->state = state; }
	STATE getState()const{ return state; }

	void setDirection(DIRECTION direction){ this->direction = direction; }
	DIRECTION getDirection()const{ return direction; }
	DIRECTION getFaceDirection()const{ return face_direction; }

	void setEnemy(Fighter* enemy){ this->enemy = enemy; }
	Fighter* getEnemy()const{ return enemy; }

	unsigned short getCategory()const{ return category; }
	unsigned short getEnemyCategory()const{ return (category == FIGHTER1 ? FIGHTER2 : FIGHTER1); }

protected:
	virtual void onDie(){}

	float life;
	float clife;
	float defense;
	float cdefense;

	STATE state;
	DIRECTION direction;
	DIRECTION face_direction;

	MachineGun* mgun;
	Fighter* enemy;

	unsigned short category;
};

#endif