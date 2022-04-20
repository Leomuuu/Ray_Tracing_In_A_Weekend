#include <cmath>
#include "Vector3.h"

Vector3 Vector3::operator+(Vector3 v)
{
	
	return Vector3 (a + v.a, b + v.b, c + v.c);
}
Vector3 Vector3::operator-(Vector3 v)
{
	
	return Vector3 (a - v.a, b - v.b, c - v.c);
}
Vector3& Vector3::operator=(const Vector3& v)
{
	a = v.X();
	b = v.Y();
	c = v.Z();
	return *this;
}
bool Vector3::operator==(Vector3 v)
{
	return ((a- v.a)< 1e-20 && (b - v.b)<1e-20 && (c - v.c)<1e-20);
}
bool Vector3::operator!=(Vector3 v)
{
	return !(*this == v);
}

Vector3 Vector3::operator*(float d)
{
	
	return Vector3 (a * d, b * d, c * d);
}

Vector3 Vector3::operator-()
{
	return Vector3(-a, -b, -c);
}

Vector3 Vector3::operator/(float d)
{
	return Vector3(a / d, b / d, c / d);
}

Vector3 Vector3::operator*(Vector3 v)
{
	return Vector3(a * v.a, b * v.b, c * v.c);
}

float Vector3::operator[](int index)
{
	switch (index)
	{
		case 0: return a;
		case 1:return b;
		default:
		return c;
	}
}

float Vector3::Dot(Vector3 v)
{
	return a * v.a + b * v.b + c * v.c;
}
Vector3 Vector3::Cross(Vector3 v)
{
	float newa = b * v.Z() - c * v.Y();
	float newb = c * v.X() - a * v.Z();
	float newc = a * v.Y() - b * v.X();	
	return Vector3 (newa, newb, newc);
}
float Vector3::Length()
{
	return sqrt(a * a + b * b + c * c);
}

Vector3 Vector3::NormalNize()
{
	float sum = Length();
	a = a / sum;
	b = b / sum;
	c = c / sum;
	return *this;
}
Vector3 Vector3::UnitVector()
{
	float len = Length();
	return Vector3(a / len,b/len,c/len);

}