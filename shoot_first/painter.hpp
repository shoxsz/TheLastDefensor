#ifndef _PAINTER_
#define _PAINTER_

#include <SDL.h>

#include "texture_region.hpp"
#include "2d_camera.hpp"
#include "point.hpp"
#include "area.hpp"
#include "size.hpp"
#include "color.hpp"

/*Represents a draw batcher*/
class Painter{
public:
	Painter();
	~Painter();

	void begin(Texture2D* texture){
		drawning_now = texture;
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		drawning_now->bind();
		glBegin(GL_QUADS);
	}

	void end(){
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}

	void setCamera(Camera2D camera){ this->camera = camera; }
	void rotate(float angle);
	void translate(float tx, float tz, float ty);
	void scale(float sx, float, float sy, float sz);
	
	/*Os métodos acima devem ser chamados antes dos métodos abaixo:*/

	/*Desenha a texture region com o tamanho e posição indicados, e ainda rotaciona no angulo especificado*/
	void drawTexture(TextureRegion* texture, const AreaF& area, float angle = 0.0f);
private:
	Camera2D camera;
	Texture2D* drawning_now;
};

#endif