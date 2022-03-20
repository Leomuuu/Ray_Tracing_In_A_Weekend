#pragma once
#include "Material.h"
#include <cstdlib>
#include <ctime>


class Lambertian :public Material {
public:
	Vector3 albedo;

	Lambertian(Vector3 a):albedo(a){}

	virtual bool Scatter(Ray& ray_in, Hit_Record& rec, Vector3& attenuation, Ray& scattered) {
		Vector3 target = rec.HitPoint + rec.NormalDirection + Random_in_unit_sphere();
		scattered = Ray(rec.HitPoint, target - rec.HitPoint);
		attenuation = albedo;
		return true;
	}

	Vector3 Random_in_unit_sphere() {
		Vector3 p;
		srand(time(0));
		//在半球体随机选一个位置
		do {
			
			p = (Vector3((double)rand() / RAND_MAX, (double)rand() / (double)RAND_MAX, rand ()/ RAND_MAX)
				 - Vector3(0.5,0.5,0.5))*2;
		} while (p.Length() >= 1);

		return p;
	}

};