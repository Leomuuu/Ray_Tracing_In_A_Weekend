#pragma once
#include<cmath>
#include "Vector3.h"

class ONB {
public:
	Vector3 axis[3];

	ONB() {}
	inline Vector3 operator [](int i) {
		return axis[i];
	}
	Vector3 u() { return axis[0]; }
	Vector3 v() { return axis[1]; }
	Vector3 w() { return axis[2]; }

	Vector3 Local(float a, float b, float c) {
		return u()*a + v()*b + w()*c;
	}
	Vector3 Local(Vector3 a) {
		return u() * a.X() + v() * a.Y() + w() * a.Z();
	}
	void Build_From(Vector3&);
};

void ONB::Build_From(Vector3& n)
{
	axis[2] = n.UnitVector();
	Vector3 a;
	if (fabs(w().X()) > 0.9)
		a = Vector3(0, 1, 0);
	else
		a = Vector3(1, 0, 0);
	axis[1] = w().Cross(a).UnitVector();
	axis[0] = w().Cross(v());

}