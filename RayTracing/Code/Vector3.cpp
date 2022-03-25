#include <cmath>
#include "Vector3.h"

Vector3 Vector3::operator+(Vector3 v)
{
	Vector3 ret(a+v.X(),b+v.Y(),c+v.Z());
	return ret;
}
Vector3 Vector3::operator-(Vector3 v)
{
	Vector3 ret(a - v.X(), b - v.Y(), c - v.Z());
	return ret;
}
Vector3 Vector3::operator=(Vector3 v)
{
	a = v.X();
	b = v.Y();
	c = v.Z();
	return *this;
}
bool Vector3::operator==(Vector3 v)
{
	return (a == v.X() && b == v.Y() && c == v.Z());
}
bool Vector3::operator!=(Vector3 v)
{
	return !(*this == v);
}

Vector3 Vector3::operator*(double d)
{
	Vector3 ret(a * d, b * d, c * d);
	return ret;
}

Vector3 Vector3::operator-()
{
	return Vector3(-a, -b, -c);
}

Vector3 Vector3::operator/(double d)
{
	return Vector3(a / d, b / d, c / d);
}

Vector3 Vector3::operator*(Vector3 v)
{
	return Vector3(a * v.a, b * v.b, c * v.c);
}

double Vector3::Dot(Vector3 v)
{
	return a * v.X() + b * v.Y() + c * v.Z();
}
Vector3 Vector3::Cross(Vector3 v)
{
	double newa = b * v.Z() - c * v.Y();
	double newb = c * v.X() - a * v.Z();
	double newc = a * v.Y() - b * v.X();
	Vector3 ret(newa, newb, newc);
	return ret;
}
double Vector3::Length()
{
	return sqrt(a * a + b * b + c * c);
}

Vector3 Vector3::NormalNize()
{
	double sum = Length();
	a = a / sum;
	b = b / sum;
	c = c / sum;
	return *this;
}
Vector3 Vector3::UnitVector()
{
	double len = Length();
	return Vector3(a / len,b/len,c/len);

}