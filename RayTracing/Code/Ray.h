#pragma once
#include "Vector3.h"

class Ray {

private:
	Vector3 startpoint;
	Vector3 direction;

public:
	Ray() {}
	Ray(Vector3 start, Vector3 direc) :startpoint(start), direction(direc) {
	}

	inline Vector3 Start() { return startpoint; }
	inline Vector3 Direction()  { return direction; }
	inline Vector3 Point(double t) { return startpoint + direction * t; }


};