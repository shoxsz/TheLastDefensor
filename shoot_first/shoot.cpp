#include "shoot.hpp"

#include "area.hpp"
#include "fighter.hpp"

MachineGun::MachineGun(Fighter* shooter) : GameThing(shooter->getGame()){
	this->shooter = shooter;
	shoting = false;
	cooldown.start();
}

bool MachineGun::startShooting(){
	if (!shoting){
		shoting = true;
		return true;
	}

	return false;
}

void MachineGun::stopShooting(){
	shoting = false;
}

void MachineGun::charge(Bullet*bullet){
	delete reference;

	this->reference = bullet->buildNew();
	cooldown.start();
}

void MachineGun::freeBullets(){
	for (Bullet* b : bullets){
		delete b;
	}

	bullets.clear();
}

void MachineGun::calculate(){
	if (shoting && cooldown.compare(reference->getCooldown())){
		push_bullet();
	}

	for (unsigned int i = 0; i < bullets.size(); i++){
		Bullet* b = bullets[i];
		b->calculate();

		if (b->getState() == STATE::DEAD){
			delete b;
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}
}

void MachineGun::render(Painter* painter){
	for (Bullet* b : bullets){
		b->render(painter);
	}
}

void MachineGun::unload(){
	cooldown.stop();

	for (Bullet* b : bullets){
		delete b;
	}

	bullets.clear();

	delete reference;
}

bool MachineGun::push_bullet(){
	if (bullets.size() < reference->getMax()){
		Bullet* bullet = reference->buildNew();
		bullet->load();
		bullets.push_back(bullet);
		return true;
	}

	return false;
}