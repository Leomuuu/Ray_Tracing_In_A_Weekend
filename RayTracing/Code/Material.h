#pragma once
#include <cstdlib>
#include <ctime>
#include "Ray.h"
#include "Hitable.h"
#include "Vector3.h"

#define RANDDOUBLE01  ((double)rand() / (RAND_MAX+1.0))  // [0.1)

struct  Hit_Record;

class Material {
public:
	virtual bool Scatter(Ray& ray_in, Hit_Record& rec, Vector3& attenuation, Ray& scattered) { return false; };
	//反射
	Vector3 Reflect(Vector3 v, Vector3 n) {
		return v - n *(v.Dot(n)) * 2;
	}
	//在半球体随机选一个位置
	Vector3 Random_in_unit_sphere() {
		Vector3 p;
		
		
		/*do {
			p = (Vector3(RANDDOUBLE01, RANDDOUBLE01, RANDDOUBLE01)*2
				- Vector3(1, 1, 1));
		} while (p.Length() >= 1);*/

		double a = RANDDOUBLE01;
		double b = RANDDOUBLE01;
		double c = RANDDOUBLE01;

		p = (Vector3(a, b, c) * 2
			- Vector3(1, 1, 1));
		p.NormalNize();

		return p*RANDDOUBLE01;
	}
	//折射
	bool Refract(Vector3 v, Vector3 n, double ni_over_nt, Vector3& refracted) {
		Vector3 uv = v.UnitVector();
		double dt = uv.Dot(n);
		double discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);

		if (discriminant > 0) {
			refracted = (uv - n * dt) * ni_over_nt - n * sqrt(discriminant);
			return true;
		}
		else return false;
	}
	//发射光线
	virtual Vector3 Emitted(double u, double v, Vector3& p) {
		return Vector3(0, 0, 0);
	}



};