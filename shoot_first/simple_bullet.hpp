#ifndef _SIMPLE_BULLET_HPP_
#define _SIMPLE_BULLET_HPP_

#include "bullet.hpp"
#include "game_textures.hpp"

class SimpleBullet : public Bullet{
public:
	SimpleBullet(Fighter* soldier) : Bullet(soldier, 250, 20, 0.3f){
		my = GameTextures::simple_bullet;
	}

	~SimpleBullet(){ destroyBody(); }

	void load();
	void calculate();
	void render(Painter* painter);
	//void unload();

	void onCollide(GameData* g);

	Bullet* SimpleBullet::buildNew()const{return new SimpleBullet(shooter);}
	std::string getName()const{ return "sb"; }
private:
	float angle;
};

#endif