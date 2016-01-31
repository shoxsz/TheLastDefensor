#include "texture.hpp"

#include <iostream>

Texture2D* Texture2D::fromImage(const Image* image, GLint min_filter, GLint mag_filter, GLint wrapping){
	GLint format;
	Texture2D* t2d = new Texture2D();

	glGenTextures(1, &t2d->tid);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, t2d->tid);
	t2d->size.setWidth(image->getWidth());
	t2d->size.setHeigth(image->getHeight());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	switch (image->getBPP()){
	case 24:
		format = GL_RGB;
		break;
	case 32:
		format = GL_RGBA;
		break;
	default:
		throw std::runtime_error("Unsurpoted pixel format!");
		break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, format, image->getWidth(), image->getHeight(), 0, format, GL_UNSIGNED_BYTE, image->getPixels());
	glDisable(GL_TEXTURE_2D);

	std::cout << glGetError() << std::endl;

	return t2d;
}

Texture2D::~Texture2D(){
	glDeleteTextures(1, &tid);
}

void Texture2D::bind(){
	glBindTexture(GL_TEXTURE_2D, tid);
}

void Texture2D::setMinFilter(GLint min_filter){
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
}

void Texture2D::setMaxFilter(GLint max_filter){
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, max_filter);
}

void Texture2D::setWrapping(GLint wrapping){
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
}