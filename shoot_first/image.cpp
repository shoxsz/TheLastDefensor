#include "image.hpp"

Image* Image::load(const std::string& path){
	Image* image = new Image();

	image->image = IMG_Load(path.c_str());

	if (!image->image)
		throw std::runtime_error(SDL_GetError());

	return image;
}

/*TextureId Image::createTexture2D(const Image* image, GLint min_filter, GLint mag_filter, GLint wrapping){
	TextureId id;
	GLint format;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	if (min_filter != 0)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);

	if (mag_filter != 0)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

	if (wrapping != 0)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);

	switch (image->image->format->BytesPerPixel){
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	default:
		throw std::runtime_error("Unsuported pixel format!");
		break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, format, image->image->w, image->image->h, 0, format, GL_UNSIGNED_BYTE, image->image->pixels);

	return id;
}*/

Image::Image(){
	image = nullptr;
}

Image::Image(const Image& image){
	this->image = SDL_CreateRGBSurfaceFrom(
		image.image->pixels,
		image.image->w,
		image.image->h,
		0,
		image.image->pitch,
		image.image->format->Rmask,
		image.image->format->Gmask,
		image.image->format->Bmask,
		image.image->format->Amask);

	if (this->image == nullptr)
		throw std::runtime_error(SDL_GetError());
}

Image::Image(Image&& image){
	this->image = image.image;
	image.image = nullptr;
}

Image::~Image(){
	erase();
}

void Image::erase(){
	SDL_FreeSurface(image);
}

unsigned int Image::getPixel(unsigned int x, unsigned int y)const{
	int bpp = image->format->BytesPerPixel;
	unsigned char* p = (unsigned char*)image->pixels + y * image->pitch + x * bpp;

	switch (bpp) {
	case 1:
		return *p;
	case 2:
		return *(unsigned int*)p;
	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
	case 4:
		return *(unsigned int*)p;
	default:
		return 0;
	}
}

void Image::setPixel(unsigned int x, unsigned int y, unsigned int pixel){
	int bpp = image->format->BytesPerPixel;
	unsigned char* p = (unsigned char*)image->pixels + y * image->pitch + x * bpp;

	switch (bpp) {
	case 1:
		*p = pixel;
		break;
	case 2:
		*(unsigned short*)p = pixel;
		break;
	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else {
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;
	case 4:
		*(unsigned int*)p = pixel;
		break;
	}
}

void Image::setColorKey(unsigned int r, unsigned g, unsigned b){
	SDL_SetColorKey(image, 1, SDL_MapRGB(image->format, r, g, b));
}

unsigned char* Image::getPixels()const{
	return (unsigned char*)image->pixels;
}