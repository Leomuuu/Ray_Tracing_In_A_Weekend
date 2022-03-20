#pragma once
#include"Material.h"
#include "Lambertian.h"

class Metal:public Material {
public:
	Vector3 albedo;
	double fuzz;

	Metal(Vector3 a, double f) :albedo(a) {
		if (f < 1) fuzz = f;
		else fuzz = 0;
	}

	//在小球体内随机一个折射向量，并的到削减值
	virtual bool Scatter(Ray& ray_in, Hit_Record& rec, Vector3& attenuation, Ray& scattered) {
		Vector3 reflected = Reflect(ray_in.Direction().NormalNize(), rec.NormalDirection);
		scattered = Ray(rec.HitPoint, reflected+Random_in_unit_sphere()*fuzz);
		attenuation = albedo;
		return (scattered.Direction().Dot(rec.NormalDirection) > 0);
	}

	//返回折射向量
	Vector3 Reflect(Vector3 v, Vector3 n) {
		return v - n*v.Dot(n)*2;
	}

	Vector3 Random_in_unit_sphere() {
		Vector3 p;
		srand(time(0));
		//在半球体随机选一个位置
		do {

			p = (Vector3((double)rand() / RAND_MAX, (double)rand() / (double)RAND_MAX, rand() / RAND_MAX)
				- Vector3(0.5, 0.5, 0.5)) * 2;
		} while (p.Length() >= 1);

		return p;
	}

};