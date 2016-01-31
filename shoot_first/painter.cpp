#include "painter.hpp"

#include <cmath>

Painter::Painter(){}
Painter::~Painter(){}

void Painter::rotate(float angle){
	/*rotate from z-axis, thats all needed for this game*/
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
}

void Painter::translate(float tx, float tz, float ty){
	glTranslatef(tx, ty, tz);
}

void Painter::scale(float sx, float, float sy, float sz){
	glScalef(sx, sy, sz);
}

void Painter::drawTexture(TextureRegion* texture, const AreaF& area, float angle){
	float halfw = area.getWidth() / 2;
	float halfh = area.getHeight() / 2;
	float cx = area.getX() + halfw;
	float cy = area.getY() + halfh;

	float rad = angle * 3.14159265 / 180.0f;
	float _cos = cos(rad);
	float _sin = sin(rad);
		
	float x1 = (-halfw * _cos - (-halfh) * _sin) + cx;
	float y1 = (-halfw * _sin + (-halfh) * _cos) + cy;
	float x2 = (halfw * _cos - (-halfh) * _sin) + cx;
	float y2 = (halfw * _sin + (-halfh) * _cos) + cy;
	float x3 = (halfw * _cos - halfh * _sin) + cx;
	float y3 = (halfw * _sin + halfh * _cos) + cy;
	float x4 = (-halfw * _cos - halfh * _sin) + cx;
	float y4 = (-halfw * _sin + halfh * _cos) + cy;

	glTexCoord2f(texture->u1, texture->v2);
	glVertex2f(x1, y1);
	glTexCoord2f(texture->u2, texture->v2);
	glVertex2f(x2, y2);
	glTexCoord2f(texture->u2, texture->v1);
	glVertex2f(x3, y3);
	glTexCoord2f(texture->u1, texture->v1);
	glVertex2f(x4, y4);
}