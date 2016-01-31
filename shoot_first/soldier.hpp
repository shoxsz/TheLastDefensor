#ifndef _SOLDIER_HPP_
#define _SOLDIER_HPP_

#include <vector>

#include <SDL.h>
#include <SDL_opengl.h>

#include "image.hpp"
#include "texture.hpp"
#include "2d_camera.hpp"
#include "fighter.hpp"
#include "point.hpp"
#include "size.hpp"
#include "enums.hpp"
#include "shoot.hpp"
#include "game_thing.hpp"
#include "timed_object.hpp"
#include "tank.hpp"
#include "effect.hpp"

#include "simple_bullet.hpp"

struct ControlKeys{
	SDL_Keycode up;
	SDL_Keycode down;
	SDL_Keycode left;
	SDL_Keycode right;
	SDL_Keycode shoot;
	SDL_Keycode granade;
};

class Soldier : public Fighter{
public:
	Soldier(Game* game, unsigned short category, ControlKeys controls);
	~Soldier(){ unload(); }

	void load();
	void calculate();
	void render(Painter* painter);
	void unload();

	void setTank(Tank* tank){ this->tank = tank; }
	Tank* getTank()const{ return tank; }

	void addSpeed(float speed){ c_speed += speed; }
	float getSpeed()const{ return speed; }
	float getCurrentSpeed()const{ return c_speed; }

	void setBullet(Bullet* bullet){ mgun->charge(bullet); }
	Bullet* getBullet()const{ return mgun->getBullet(); }

	void keyDown(SDL_KeyboardEvent* event);
	void keyUp(SDL_KeyboardEvent* event);

	ControlKeys getControls()const{ return control_keys; }

	void addEffect(Effect* effect){ this->effects.push_back(effect); }
	void removeEffect(unsigned int index){ effects.erase(effects.begin() + index); }
	std::vector<Effect*>& getEffects(){ return effects; }

private:
	void calculateFaceDirection();
	void renderSelf();

	ControlKeys control_keys;

	PointF walk;
	std::vector<Effect*> effects;

	Tank* tank;
	Tank* enemy_tank;

	float speed, c_speed;
	unsigned int points;
};

#endif