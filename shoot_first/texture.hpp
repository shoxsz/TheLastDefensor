#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <SDL_opengl.h>

#include "image.hpp"
#include "area.hpp"
#include "size.hpp"

typedef unsigned int TextureId;

/*Hold an opengl 2d Texture*/
class Texture2D{
public:
	static Texture2D* fromImage(const Image* image, GLint min_filter = 0, GLint mag_filter = 0, GLint wrapping = 0);
	static AreaF getTextureArea(const Area& area){ return AreaF(1.0f / area.getX(), 1.0f / area.getY(), 1.0f / area.getWidth(), 1.0f / area.getHeight()); }

	~Texture2D();

	void bind();
	void setMinFilter(GLint min_filter);
	void setMaxFilter(GLint max_filter);
	void setWrapping(GLint wrapping);
	unsigned int getWidth()const{ return size.getWidth(); }
	unsigned int getHeight()const{ return size.getHeight(); }

private:
	TextureId tid;
	Size size;
};

#endif