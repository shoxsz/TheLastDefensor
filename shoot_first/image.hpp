#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <string>

#include <image\SDL_image.h>
#include <SDL_opengl.h>

#include "color.hpp"

class Image{
public:
	static Image* load(const std::string& path);

	Image();
	Image(const Image& image);
	Image(Image&& image);
	~Image();

	void erase();

	/*return the pixel in the specified position as a 32 bit pixel*/
	unsigned int getPixel(unsigned int x, unsigned int y)const;
	/*insert the pixel in the specified position using the image pixel format*/
	void setPixel(unsigned int x, unsigned int y, unsigned int pixel);

	void setColorKey(unsigned int r, unsigned g, unsigned b);

	unsigned int getWidth()const{
		return image->w;
	}

	unsigned int getHeight()const{
		return image->h;
	}

	unsigned int getBPP()const{
		return image->format->BitsPerPixel;
	}

	unsigned char* getPixels()const;

	Image& operator=(Image image){
		std::swap(this->image, image.image);
	}

private:
	SDL_Surface* image;
};

#endif