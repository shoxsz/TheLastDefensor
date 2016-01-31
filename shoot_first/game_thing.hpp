#ifndef _GAME_THING_HPP_
#define _GAME_THING_HPP_

#include <Box2D\Box2D.h>

#include <vector>
#include <string>

#include "image.hpp"
#include "texture_region.hpp"
#include "2d_camera.hpp"
#include "point.hpp"
#include "painter.hpp"
#include "size.hpp"
#include "area.hpp"
#include "enums.hpp"

class Game;

#define BULLET 0x1
#define FIGHTER1 0x2
#define TANK 0x4
#define TIMED_BOOST_ITEM 0x8
#define SCENARIO 0xF
#define FIGHTER2 0x20

class GameThing;

struct GameData{
	GameThing* thing;
	unsigned short bits;
};

class GameThing{
public:
	/*!!PROBLEM!!*/
	GameThing(Game* game);
	
	virtual ~GameThing(){}

	virtual void load(){}
	virtual void calculate(){}
	virtual void render(Painter* painter){}
	virtual void unload(){}

	virtual void onCollide(GameData* g){}

	void setPosition(const PointF& position){ body->SetTransform(b2Vec2(position.getX(), position.getY()), 0.0f); }

	AreaF getArea()const{ return area; }
	PointF getPosition()const{ return PointF(area.getX(), area.getY()); }

	Camera2D getCamera()const;

	Game* getGame()const{ return game; }

protected:
	void createBody(const SizeF& size, b2BodyType btype, unsigned short bits, unsigned short colliders, bool is_sensor);
	void destroyBody();

	TextureRegion* my;
	AreaF area;
	b2Body* body;
	Game* game;
	GameData data;
};

#endif