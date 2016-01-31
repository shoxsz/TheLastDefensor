#ifndef _SIZE_
#define _SIZE_

template <class T>
class TSize{
public:

	TSize(){ w = h = T(0); }
	TSize(T w, T h){
		this->w = w;
		this->h = h;
	}

	void setWidth(T w){ this->w = w; }
	void setHeigth(T h){ this->h = h; }
	T getWidth()const{ return w; }
	T getHeight()const{ return h; }
	T area()const{ return w * h; }

	TSize<T>& operator=(const TSize<T>& other){
		w = other.w;
		h = other.h;
		return *this;
	}

	bool operator>(const TSize<T>& other)const{ return area() > other.area(); }

	bool operator<(const TSize<T>& other)const{ return area() < other.area(); }

	bool operator==(const TSize<T>& other)const{ return (w == other.w && h == other.h); }

	bool operator>=(const TSize<T>& other)const{ return (*this > other || *this == other); }

	bool operator<=(const TSize<T>& other)const{ return (*this < other || *this == other); }

	TSize<T> operator+(const TSize<T>& other){ return TSize<T>(w + other.w, h + other.h); }

	TSize<T> operator-(const TSize<T>& other){ return TSize<T>(w - other.w, h - other.h); }

	TSize<T> operator*(const TSize<T>& other){ return TSize<T>(w * other.w, h * other.h); }

	TSize<T> operator/(const TSize<T>& other){ return TSize<T>(w / other.w, h / other.h); }

	void operator+=(const TSize<T>& other){ *this = *this + other; }

	void operator-=(const TSize<T>& other){ *this = *this - other; }

	void operator*=(const TSize<T>& other){ *this = *this * other; }

	void operator/=(const TSize<T>& other){ *this = *this / other; }

private:
	T w, h;
};

typedef TSize<int> Size;
typedef TSize<float> SizeF;

#endif