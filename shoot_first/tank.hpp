#ifndef _TANK_
#define _TANK_

#include "2d_camera.hpp"
#include "fighter.hpp"
#include "shoot.hpp"
#include "area.hpp"
#include "enums.hpp"

class Tank : public Fighter{
public:
	Tank(Game* game, Fighter* defensor);
	~Tank(){ destroyBody(); }

	void load();
	void calculate();
	void render(Painter* painter);
	void erase();

	void setTankState(TANK_STATE tstate);
	TANK_STATE getTankState()const{ return tstate; }

	Fighter* getDefensor()const{ return defensor; }

private:
	TANK_STATE tstate;
	
	Fighter* defensor;
};

#endif