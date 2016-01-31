#ifndef _TEXTURE_REGION_HPP_
#define _TEXTURE_REGION_HPP_

#include "texture.hpp"

class TextureRegion{
public:
	TextureRegion();
	TextureRegion(Texture2D* texture, int x, int y, unsigned w, unsigned h);

	Texture2D* texture;

	/*bmp coords*/

	int x, y;
	unsigned int w, h;

	/*texture coords*/

	float u1, v1;
	float u2, v2;
};

#endif