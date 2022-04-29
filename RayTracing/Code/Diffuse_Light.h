#pragma once
#include "Material.h"
#include "Texture.h"

//指定发射光线的颜色
class Diffuse_Light :public Material {
public:
	Texture* emit;

	Diffuse_Light(Texture* a) :emit(a) {}

	virtual bool Scatter(Ray& ray_in, Hit_Record& rec, Vector3& attenuation, Ray& scattered) 
	{
		return false;
	}
	virtual Vector3 Emitted(Ray& ray, Hit_Record& rec,float u, float v, Vector3& p) {
		if(rec.NormalDirection.Dot(ray.Direction())<0)
			return emit->Value(u, v, p);
		return Vector3(0, 0, 0);
	}



};