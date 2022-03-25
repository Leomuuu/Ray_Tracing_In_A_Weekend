#pragma once
#include "Material.h"
#include "Texture.h"


//漫反射材质
class Lambertian :public Material {
public:
	Texture* albedo;

	Lambertian(Texture* a):albedo(a){}

	virtual bool Scatter(Ray& ray_in, Hit_Record& rec, Vector3& attenuation, Ray& scattered) {
		Vector3 target = rec.HitPoint + rec.NormalDirection+Random_in_unit_sphere();
		scattered = Ray(rec.HitPoint, target - rec.HitPoint);
		attenuation = albedo->Value(0,0,rec.HitPoint);
		return true;
	}


};