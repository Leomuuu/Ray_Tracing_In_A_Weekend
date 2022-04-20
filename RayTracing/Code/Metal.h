#pragma once
#include"Material.h"
#include "Lambertian.h"

class Metal:public Material {
public:
	Vector3 albedo;
	float fuzz;

	Metal(Vector3 a, float f) :albedo(a) {
		if (f < 1) fuzz = f;
		else fuzz = 1;
	}

	//在小球体内随机一个折射向量，并的到削减值
	virtual bool Scatter(Ray& ray_in, Hit_Record& rec, Vector3& attenuation, Ray& scattered) {
		Vector3 reflected = Reflect(ray_in.Direction().UnitVector(), rec.NormalDirection);
		scattered = Ray(rec.HitPoint, reflected+Random_in_unit_sphere()*fuzz);
		attenuation = albedo;
		return (scattered.Direction().Dot(rec.NormalDirection) > 0);
	}





};