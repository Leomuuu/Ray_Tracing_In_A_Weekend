#pragma once
#include <cstdlib>
#include <ctime>
#include "Ray.h"
#include "Hitable.h"
#include "Vector3.h"

#define RANDfloat01  ((float)rand() / (RAND_MAX+1.0))  // [0.1)
#define ZEROLIGHT 0
#define MPI 3.1415926535897932384626

struct  Hit_Record;
class HitableObject;
class PDF;

struct Scatter_Record {
	Ray specular_ray;
	bool is_specular;
	bool is_microfacet;
	Vector3 attenuation;

};

class Material {
public:
	virtual bool Scatter(Ray& ray_in, Hit_Record& rec,Scatter_Record& srec) { 
		return false; 
	}
	virtual float Scattering_pdf(Ray& ray_in, Hit_Record& rec,Ray& scattered) {
		return 0;
	}
	virtual Vector3 Diffuse_Scattering_pdf(Ray& ray_in, Hit_Record& rec, Ray& scattered) {
		return Vector3(0,0,0);
	}
	virtual Vector3 Emitted(Ray& ray,Hit_Record&rec,float u, float v, Vector3& p) {
		return Vector3(ZEROLIGHT, ZEROLIGHT, ZEROLIGHT);
	}
	
	//反射
	Vector3 Reflect(Vector3 v, Vector3 n) {
		return v - n *(v.Dot(n)) * 2;
	}
	//在球体内随机选一个位置
	Vector3 Random_in_unit_sphere() {
		Vector3 p;

		float a = RANDfloat01;
		float b = RANDfloat01;
		float c = RANDfloat01;

		p = (Vector3(a, b, c) * 2
			- Vector3(1, 1, 1));
		p.NormalNize();

		return p*RANDfloat01;
	}
	//折射
	bool Refract(Vector3 v, Vector3 n, float ni_over_nt, Vector3& refracted) {
		Vector3 uv = v.UnitVector();
		float dt = uv.Dot(n);
		float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);

		if (discriminant > 0) {
			refracted = (uv - n * dt) * ni_over_nt - n * sqrt(discriminant);
			return true;
		}
		else return false;
	}
	
	static Vector3 Random_Cosine_Direction() {
		float r1 = RANDfloat01;
		float r2 = RANDfloat01;
		float z = sqrt(1 - r2);
		float phi = 2 * MPI * r1;
		float x = cos(phi) * 2 * sqrt(r2);
		float y = sin(phi) * 2 * sqrt(r2);
		return Vector3(x, y, z);
	}


};