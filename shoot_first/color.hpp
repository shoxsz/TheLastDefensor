#ifndef _COLOR_
#define _COLOR_

class Color{
public:
	Color(){
		r = g = b = a = 0.0f;
	}

	Color(float r, float g, float b){ setRGB(r, g, b); }
	Color(float r, float g, float b, float a){ setRGBA(r, g, b, a); }

	void setRGB(unsigned int r, unsigned int g, unsigned int b){
		this->r = r / 255.0f;
		this->g = g / 255.0f;
		this->b = b / 255.0f;
	}

	void setRGBA(unsigned int r, unsigned int g, unsigned int b, unsigned int a){
		this->r = r / 255.0f;
		this->g = g / 255.0f;
		this->b = b / 255.0f;
		this->a = a / 255.0f;
	}

	void setRGB(float r, float g, float b){
		this->r = r;
		this->g = g;
		this->b = b;
	}

	void setRGBA(float r, float g, float b, float a){
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	float getR()const{ return r; }
	float getG()const{ return g; }
	float getB()const{ return b; }
	float getA()const{ return a; }

private:
	float r, g, b, a;
};

#endif