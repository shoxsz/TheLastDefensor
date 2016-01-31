#ifndef _BOOST_
#define _BOOST_

#include "game.hpp"

class Game;

class Boost : public Effect{
public:
	enum BOOST_TYPE{
		SPEED = 0,
		DEFENSE,
		LIFE,
		GUN
	};

	Boost(Soldier* target, BOOST_TYPE btype) : Effect(target){
		this->btype = btype;
	}

	void load();
	void onEnd();

	BOOST_TYPE getType()const{ return btype; }

private:
	void speed();	/*increase speed in 50%(of the current speed) for 10 seconds*/
	void defense();	/*increase defense in 30%(of the current defense) for 30 sconds*/
	void life();	/*increase life in 20%(of the max life)*/

	float added;
	BOOST_TYPE btype;
};

#define TIMED_BOOST_SIZE 2.0f

/*process the boost item on the ground*/
class TimedBoostItem : public TimedObject{
public:
	TimedBoostItem(Game* game) : TimedObject(game){
		this->boost = nullptr;
		my = nullptr;
		this->game = game;
	}

	~TimedBoostItem(){ destroyBody(); }

	void load();
	void step();
	void render(Painter* painter);
	void onCollide(GameData* g);

private:
	Boost* boost;
};

#endif