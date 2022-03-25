#pragma once

class Vector3 {
	
private:
	double a;
	double b;
	double c;


public:	
	Vector3():a(0),b(0),c(0) {}
	Vector3(double first, double second, double third) 
		: a(first), b(second), c(third) {
	}
	Vector3(const Vector3& vec) {
		a = vec.X();
		b = vec.Y();
		c = vec.Z();
	}

	inline double R() const { return a; }
	inline double G() const { return b; }
	inline double B() const { return c; }
	inline double X() const { return a; }
	inline double Y() const { return b; }
	inline double Z() const { return c; }

	Vector3 operator + (Vector3 v);
	Vector3 operator - (Vector3 v);
	Vector3 operator -();
	Vector3 operator = (Vector3 v);
	Vector3 operator * (double d);
	Vector3 operator * (Vector3 v);
	Vector3 operator /(double d);
	bool operator ==(Vector3 v);
	bool operator !=(Vector3 v);

	//点乘
	double Dot(Vector3 v);
	//叉乘
	Vector3 Cross(Vector3 v);

	double Length();
	//自身变为单位向量
	Vector3 NormalNize();
	//返回单位向量
	Vector3 UnitVector();




};
