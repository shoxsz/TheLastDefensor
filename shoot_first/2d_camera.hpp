#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <SDL_opengl.h>

/*Simple class that uses glOrtho to manipulate the camera*/
class Camera2D{
public:
	Camera2D(){
		x_offset = 0;
		y_offset = 0;
		width = 0;
		height = 0;
	}

	Camera2D(float width, float height){
		x_offset = 0;
		y_offset = 0;
		set(width, height);
	}

	Camera2D(float x_offset, float y_offset, float width, float height) : Camera2D(width, height){
		translate(x_offset, y_offset);
	}

	void translate(float x_offset, float y_offset){
		this->x_offset = x_offset;
		this->y_offset = y_offset;
		set(width, height);
	}

	void set(float width, float height){
		this->width = width;
		this->height = height;
		glOrtho(-(width / 2) + x_offset, width / 2 + x_offset, -(height / 2) + y_offset, height / 2 + y_offset, -1, 1);
	}

	float getLeft()const{
		return -getRight();
	}

	float getRight()const{
		return width / 2;
	}

	float getBottom()const{
		return -getTop();
	}

	float getTop()const{
		return height / 2;
	}

	float getXOffset()const{
		return x_offset;
	}

	float getYOffset()const{
		return y_offset;
	}

	float getWidth()const{
		return width;
	}

	float getHeight()const{
		return height;
	}

private:
	float x_offset, y_offset;
	float width;
	float height;
};

#endif