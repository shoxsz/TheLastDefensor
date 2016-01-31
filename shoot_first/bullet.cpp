#include "bullet.hpp"
#include "fighter.hpp"

Bullet::Bullet(Fighter* shooter, int cooldown, unsigned int max, float damage) : GameThing(shooter->getGame()){
	this->shooter = shooter;
	this->cooldown = cooldown;
	this->max = max;
	this->damage = damage;
}