#ifndef _GAME_TEXTURES_HPP_
#define _GAME_TEXTURES_HPP_

#include "texture_region.hpp"

class GameTextures{
public:
	static Texture2D* textureAtlas;

	/*life bar*/
	static TextureRegion* life_bar;
	static TextureRegion* black_bar;
	static TextureRegion* gray_bar;

	/*bullets*/
	static TextureRegion* simple_bullet;

	/*boosts*/
	static TextureRegion* speed_boost;
	static TextureRegion* defense_boost;
	static TextureRegion* life_boost;

	/*character*/
	static TextureRegion* soldier;

	/*tanks*/
	static TextureRegion* tank;
private:
};

#endif