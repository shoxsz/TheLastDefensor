#ifndef _SHOOT_HPP_
#define _SHOOT_HPP_

#include <vector>

#include <SDL.h>

#include "point.hpp"
#include "enums.hpp"
#include "area.hpp"
#include "2d_camera.hpp"
#include "timer.hpp"
#include "game_thing.hpp"
#include "bullet.hpp"

class Fighter;

class MachineGun : public GameThing{
public:
	MachineGun(Fighter* soldier);
	~MachineGun(){ unload(); }

	bool startShooting();
	void stopShooting();

	void charge(Bullet* bullet);
	void freeBullets();
	void calculate();
	void render(Painter* painter);
	void unload();

	Bullet* getBullet()const{ return reference; }
	bool isShooting()const{ return shoting; }

	Fighter* getShooter()const{return shooter;}

	std::vector<Bullet*>& getBullets(){ return bullets; }
	void removeBullet(unsigned int index){
		bullets.erase(bullets.begin() + index);
	}

private:
	bool push_bullet();

	Fighter* shooter;
	Timer cooldown;
	bool shoting;

	Bullet* reference;
	std::vector<Bullet*> bullets;
};

#endif