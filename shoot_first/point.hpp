#ifndef _POSITION_
#define _POSITION_

#include "size.hpp"
#include "area.hpp"

template<class T>
class TPoint{
public:

	TPoint(){ x = y = T(0); }
	TPoint(T x, T y){
		setLocal(x, y);
	}

	void moveX(T x){
		this->x += x;
	}

	void setX(T x){
		this->x = x;
	}

	void moveY(T y){
		this->y += y;
	}

	void setY(T y){
		this->y = y;
	}

	void move(T x, T y){
		this->x += x;
		this->y += y;
	}

	void move(const TPoint<T>& m){
		*this += m;
	}

	void setLocal(T x, T y){
		this->x = x;
		this->y = y;
	}

	T getX()const{
		return x;
	}

	T getY()const{
		return y;
	}

	bool isInside(const TArea<T>& area)const{
		if (x > area.getX() &&
			y > area.getY() &&
			x < area.getX() + area.getWidth() &&
			y < area.getY() + area.getHeight()){
			return true;
		}

		return false;
	}


	TPoint<T>& operator=(const TPoint<T>& other){
		x = other.x;
		y = other.y;
		return *this;
	}

	bool operator>(const TPoint<T>& other){ return (x > other.x && y > other.y); }

	bool operator<(const TPoint<T>& other){ return (x < other.x && y < other.y); }

	bool operator==(const TPoint<T>& other){ return (x == other.x && y == other.y); }

	bool operator>=(const TPoint<T>& other){ return (*this > other || *this == other); }

	bool operator<=(const TPoint<T>& other){ return (*this < other || *this == other); }

	TPoint<T> operator+(const TPoint<T>& other){ return TPoint<T>(x + other.x, y + other.y); }

	TPoint<T> operator-(const TPoint<T>& other){ return TPoint<T>(x - other.x, y - other.y); }

	TPoint<T> operator*(const TPoint<T>& other){ return TPoint<T>(x * other.x, y * other.y); }

	TPoint<T> operator/(const TPoint<T>& other){ return TPoint<T>(x / other.x, y / other.y); }

	void operator+=(const TPoint<T>& other){ *this = *this + other; }

	void operator-=(const TPoint<T>& other){ *this = *this - other; }

	void operator*=(const TPoint<T>& other){ *this = *this * other; }

	void operator/=(const TPoint<T>& other){ *this = *this / other; }

private:
	T x, y;
};

typedef TPoint<int> Point;
typedef TPoint<float> PointF;

#endif