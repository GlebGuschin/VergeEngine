#pragma once

#include "Common.hpp"

//#include "Archive.hpp"
//#include "MathCommon.hpp"

namespace Verge3D {


class Color {

	float r, g, b, a;

public:


	inline float getRed() const { return(r); }
	inline float getBlue() const { return(b); }
	inline float getGreen() const { return(g); }
	inline float getAlpha() const { return(a); }

	void setValue(float r_, float g_, float b_, float a_) {

		r = (float)r_;
		g = (float)g_;
		b = (float)b_;
		a = (float)a_;

	}

	Color() { setValue(0.0, 0.0, 0.0, 1.0); }
	Color(double r_, double g_, double b_, double a_ = 1.0) {
		setValue((float)r_, (float)g_, (float)b_, (float)a_);
	}

	Color(float r_, float g_, float b_, float a_ = 1.0) {
		setValue((float)r_, (float)g_, (float)b_, (float)a_);
	}


	Color& operator*=(const float scale) { r *= scale; g *= scale; b *= scale; a *= scale; return(*this); }
	Color& operator*=(const double scale) { r *= (float)scale; g *= (float)scale; b *= (float)scale; a *= (float)scale; return(*this); }


	Color& operator*=(const Color&color) { r *= color.r; g *= color.g; b *= color.b; a *= color.a; return(*this); }

	bool operator==(const Color&other) const {
		const float esp = 0.001f;
		return fabs(a - other.a) < esp && fabs(r - other.r) < esp && fabs(g - other.g) < esp && fabs(b - other.b) < esp;
	}

	/*
	inline operator dword() const {

		//saturate();

		byte _r = byte(r * 255.0f);
		byte _g = byte(g * 255.0f);
		byte _b = byte(b * 255.0f);
		byte _a = byte(a * 255.0f);

		return( (_r << 24) | (_g << 16) | (_b << 8 ) | _a );

	}
	*/

	//Color bgra() const { return(Color(b, g, r, a)); }
	//Color argb() const { return(Color(a, r, g, b)); }
	//Color gamma() const { return(Color(a, r, g, b)); }



	const static Color BLACK;
	const static Color RED;
	const static Color GREEN;
	const static Color BLUE;
	const static Color WHITE;
	const static Color GRAY;


	friend Color operator * (const Color &color, double scale) { return(Color(color.r * scale, color.g * scale, color.b * scale)); }
	friend Color operator + (const Color &color1, const Color &color2) { return(Color(color1.r + color2.r, color1.g + color2.g, color1.b + color2.b, color1.a + color2.a)); }
	friend Color operator - (const Color &color1, const Color &color2) { return(Color(color1.r - color2.r, color1.g - color2.g, color1.b - color2.b, color1.a - color2.a)); }

};


/*

class GammaColor {

	float r, g, b, a;

public:

	void setValue(float r_, float g_, float b_, float a_ = 1.0) {

		static const float scale = 1.0f / 2.2f;

		r = powf(r_, scale);
		g = powf(g_, scale);
		b = powf(b_, scale);
		a = powf(a_, scale);

	}

	GammaColor(const Color& color) { setValue(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha()); }
	GammaColor(float r_, float g_, float b_, float a_ = 1.0) {
		setValue(r_, g_, b_, a_);
	}
	GammaColor(double r_, double g_, double b_, double a_ = 1.0) {
		setValue((float)r_, (float)g_, (float)b_, (float)a_);
	}

	operator Color() const {

		const float scale = 2.2f;
		return Color(powf(r, scale), powf(g, scale), powf(b, scale), powf(a, scale));

	}


};


class PackedColor {

	//uint32 color;
	uint8 r, g, b, a;

	void setValue(float r_, float g_, float b_, float a_ = 1.0f) {

		r = byte(r_ * 255.0f);
		g = byte(g_ * 255.0f);
		b = byte(b_ * 255.0f);
		a = byte(a_ * 255.0f);

	}

public:

	PackedColor() {
		setValue(0.0f, 0.0f, 0.0f, 1.0f);
	}

	PackedColor(float r_, float g_, float b_, float a_ = 1.0f) {
		setValue(r_, g_, b_, a_);
	}


	PackedColor(const Color& color) {
		setValue(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
	}

	operator Color() const {

		const float scale = 1.0f / 255.0f;
		return Color(r * scale, g * scale, b * scale, a * scale);

	}

};

*/

}






