#include "texture_region.hpp"

TextureRegion::TextureRegion(Texture2D* texture, int x, int y, unsigned w, unsigned h){
	this->texture = texture;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

	this->u1 = (float)x / texture->getWidth();
	this->v1 = (float)y / texture->getHeight();
	this->u2 = u1 + (float)w / texture->getWidth();
	this->v2 = v1 + (float)h / texture->getHeight();
}