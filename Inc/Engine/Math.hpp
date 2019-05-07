#pragma once

#include "Common.hpp"

namespace Verge3D {

template<typename T>
struct Range {
	T minValue, maxValue;
	Range(const T&  minValue_, const T&  maxValue_) : minValue(minValue_), maxValue(maxValue_) {}
};


template<typename T>
struct Square {
	T width, height;
	Square() : width(0), height(0) {}
	Square(const T&  width_, const T&  height_) : width(width_), height(height_) {}
	T calcValue() const { return width * height; }
};

template<typename T>
struct Volume : public Square<T> {
	T depth;
	Volume(const T&  width_, const T&  height_, const T& depth_) : Square(width_, height_), depth(depth_) {}
	T calcValue() const { return Square::getValue() * depth; }
};

template<typename T>
struct Rect {
	T top, left, right, bottom;
	//Rect(const T&  left_, const T&  top_, const T&  right_, const T&  bottom_) : minValue(minValue_), maxValue(maxValue_) {}
};


template  <typename P>
struct TVector2
{
	P x, y;

	TVector2() {}
	TVector2(const P& x_, const P& y_) : x(x_), y(y_) {}

	TVector2& operator=(const TVector2& other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	TVector2 operator-() { return TVector2(-x, -y); }

	TVector2& operator+=(const TVector2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	TVector2 operator + (const TVector2& a) {
		return TVector2(x + a.x, y + a.y);
	}

};




template  <typename P>
struct TVector3
{
	P x, y, z;

	TVector3() {}
	TVector3(const P& x_, const P& y_, const P& z_ = 0) : x(x_), y(y_), z(z_) {}
	//TVector3(const TVector2<P> & v) : TVector2(v.x_, v,y_), z(0.0) {}

	TVector3& operator=(const TVector3& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	TVector3 operator-() { return TVector3(-x, -y, -z); }

	TVector3& operator+=(const TVector3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	TVector3 operator + (const TVector3& a) {
		return TVector3(x + a.x, y + a.y, z + a.z);
	}

	TVector3 operator * (const P& s) {
		return TVector3(x * s, y * s, z * s);
	}

};


typedef TVector3<float> Vector;


/*
template  <typename P>
struct TVector4 {
	P x, y, z, w;
	TVector4() {}
	TVector4(const P& x_, const P& y_, const P& z_) :(x_), (y_), z(z_), w(1) {}
	//TVector4(const TVector3<P>& v) : TVector3(v), w(1) {}
};
*/


template  <typename P>
class TMatrix4x4 {

	P array[4][4];

public:


};

enum class MatrixType : uint32_t {
	View,
	Projection,
	World,
	InvView,
	Max
};

//static constexpr uint32_t MaxSize = sizeof();

template  <typename T>
class MatrixSet {

	//T matrices[MatrixType::Max];
	T matrices[10];
	void update();

public:

	void setViewMatrix(const T&) {}
	void setProjectionMatrix(const T&) {}

	void commit() {}
};


struct IntPosition {
	int x, y;

	bool operator==(const IntPosition& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	IntPosition(int x_, int y_) : x(x_), y(y_) {}
	IntPosition() : x(0), y(0) {}
};




typedef Square<unsigned> WindowSize;
typedef Square<unsigned> ClientWindowSize;
typedef IntPosition WindowPosition;

struct Quaternion {
	Quaternion(float, float, float, float) {}
};
struct Scale {

};

struct Transform {
	Vector translate;

public:

	Transform() {}
	Transform(const Vector& translate_, const Quaternion& rotate_, const Scale& scale_) {}

};

/*
struct Color {
	float r, g, b, a;
};
*/



template  <typename T>
//inline T Random(const T& minValue = 0.0f, const T maxValue = 1.0f, uint32_t denom = 1024) {
inline T Random(const T& minValue, const T maxValue, uint32_t denom = 1024) {

	const T r = static_cast<T>(rand() % denom) / denom;
	return minValue + (maxValue - minValue) * r;
}


inline Vector Random(const Vector& minValue, const Vector& maxValue, uint32_t denom = 1024) {

	return Vector(Random(-1.0f,1.0f,denom), Random(-1.0f, 1.0f, denom), Random(-1.0f, 1.0f, denom));
	//const T r = static_cast<T>(rand() % denom) / denom;
	//return minValue + (maxValue - minValue) * r;
}




template  <typename T>
T Lerp(const T& minValue, const T& maxValue, float a) {
	return minValue + (maxValue - minValue) * a;
}



}
