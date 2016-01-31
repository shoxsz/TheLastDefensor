#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <Box2D/Box2D.h>

#include <list>

#include "loop_handler.hpp"
#include "2d_camera.hpp"
#include "timer.hpp"
#include "timed_object.hpp"
#include "point.hpp"
#include "area.hpp"
#include "soldier.hpp"
#include "tank.hpp"
#include "painter.hpp"

class Game : public LoopHandler, public b2ContactListener, public b2ContactFilter{
public:
	friend class TimedBoostItem;
	void pre();
	void process(SDL_Event* event);
	void logics();
	void render();
	void pos();

	bool active();

	Camera2D getCamera()const;
	Soldier* getP1()const{ return p1; }
	Soldier* getP2()const{ return p2; }

	b2World* getWorld()const{ return world; }

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB);

private:
	Texture2D* loadTexture(const std::string& path){
		Image* image = Image::load(path);
		Texture2D* t = Texture2D::fromImage(image);
		return t;
	}

	void start();
	
	void preparePlayer(Soldier* soldier);
	void setToSleep(Soldier* soldier);
	
	/*Boosts items*/

	unsigned int to_next_boost;
	Timer boost_t;

	std::vector<TimedBoostItem*> boosts;
	Soldier *p1, *p2;
	Tank *tank1, *tank2;
	Camera2D camera;
	Timer p1t, p2t;

	Painter painter;

	b2World* world;
	b2Body* world_bounds;

	bool running;
};

#endif