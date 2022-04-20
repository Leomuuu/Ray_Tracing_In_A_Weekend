#pragma once

class Vector3 {
	
private:
	float a;
	float b;
	float c;


public:	
	
	Vector3() { a = b = c = 0; }
	Vector3(float first, float second, float third) 
		{ a = first; b = second; c = third;
	}




	inline float R() const { return a; }
	inline float G() const { return b; }
	inline float B() const { return c; }
	inline float X() const { return a; }
	inline float Y() const { return b; }
	inline float Z() const { return c; }

	Vector3 operator + (Vector3 v);
	Vector3 operator - (Vector3 v);
	Vector3 operator -();
	Vector3& operator = (const Vector3& v);
	Vector3 operator * (float d);
	Vector3 operator * (Vector3 v);
	Vector3 operator /(float d);
	float operator [](int index);
	bool operator ==(Vector3 v);
	bool operator !=(Vector3 v);

	//点乘
	float Dot(Vector3 v);
	//叉乘
	Vector3 Cross(Vector3 v);

	float Length();
	//自身变为单位向量
	Vector3 NormalNize();
	//返回单位向量
	Vector3 UnitVector();




};
