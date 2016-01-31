#ifndef _MAP_
#define _MAP_

#include <string>

#include <Box2D\Box2D.h>

class Map{
public:
	Map();
	~Map();

	void load(const std::string& str, b2World* world);
private:
	void addBody(float x, float y);
};

#endif