#pragma once
#include <cmath>
#include "Vector3.h"

class Texture {
public:
	virtual Vector3 Value(double u, double v, const Vector3& p)=0;
};


class Constant_Texture :public Texture {
public:
	Vector3 Color;

	Constant_Texture();
	Constant_Texture(Vector3 c) :Color(c) {}

	virtual Vector3 Value(double u, double v, const Vector3& p) override{
		return Color;
	}

};


class Checker_Texture :public Texture {
public:
	Texture* odd=nullptr;
	Texture* even=nullptr;

	Checker_Texture() {}
	Checker_Texture(Texture* t0,Texture* t1):even(t0),odd(t1) {}

	virtual Vector3 Value(double u, double v, const Vector3& p)override {
		double sines = sin(10 * p.X()) * sin(10 * p.Y()) * sin(10 * p.Z());
		if (sines < 0)
			return odd->Value(u, v, p);
		else
			return even->Value(u, v, p);
	}

};