#ifndef _AREA_
#define _AREA_

template<class T>
class TArea{
public:
	TArea(){ x = y = w = h = T(0); }
	TArea(T x, T y, T w, T h){
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}

	void setX(T x){ this->x = x; }
	void setY(T y){ this->y = y; }
	void setWidth(T w){ this->w = w; }
	void setHeight(T h){this->h = h; }

	T getX()const{ return x; }
	T getY()const{ return y; }
	T getWidth()const{ return w; }
	T getHeight()const{ return h; }

	T getRight()const{ return x + w; }
	T getBottom()const{ return y + h; }

	T area()const{ return w * h; }

	bool testCollision(const TArea<T>& area)const{
		if (x + w < area.x || x > area.x + area.w)
			return false;

		if (y + h < area.y || y > area.y + area.h)
			return false;

		return true;
	}

	bool isInside(const TArea<T>& area)const{
		if (x > area.x && x + w < area.x + area.w &&
			y > area.y && y + h < area.y + area.h){
			return true;
		}

		return false;
	}

	void scale(float scale){
		w *= scale;
		h *= scale;
	}

	TArea<T>& operator=(const TArea<T>& other){
		x = other.x;
		y = other.y;
		w = other.w;
		h = other.h;
		return *this;
	}

	bool operator>(const TArea<T>& other){ return (area() > other.area()); }
	bool operator<(const TArea<T>& other){ return (area() < other.area()); }
	bool operator==(const TArea<T>& other){ return (x == other.x && y == other.y && w == other.w && h == other.h); }
	bool operator>=(const TArea<T>& other){ return (*this > other || *this == other); }
	bool operator<=(const TArea<T>& other){ return (*this < other || *this == other); }
private:
	T x;
	T y;
	T w;
	T h;
};

typedef TArea<int> Area;
typedef TArea<float> AreaF;

#endif