#ifndef _BULLET_
#define _BULLET_

#include "game_thing.hpp"

class Fighter;

class Bullet : public GameThing{
public:
	Bullet(Fighter* shooter, int cooldown, unsigned int max, float damage);

	virtual ~Bullet(){}

	/*return a new instance of a bullet*/
	virtual Bullet* buildNew()const{ return nullptr; }
	virtual std::string getName()const{ return "ni"; /*ni for not identified*/ }

	unsigned int getCooldown()const{ return cooldown; }
	unsigned int getMax()const{ return max; }

	Fighter* getShooter()const{ return shooter; }
	STATE getState()const{ return state; }

	float getDamage()const{ return damage; }

protected:
	Fighter* shooter;
	unsigned int cooldown;
	unsigned int max;
	float damage;
	STATE state;
	PointF walk;
};
#endif