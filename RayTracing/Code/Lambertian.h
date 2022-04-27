#pragma once
#include "Material.h"
#include "Texture.h"
#include "ONB.h"

//漫反射材质
class Lambertian :public Material {
public:
	Texture* albedo;

	Lambertian(Texture* a) :albedo(a) {}

	virtual bool Scatter(Ray& ray_in, Hit_Record& rec, Vector3& attenuation, Ray& scattered,float &pdf) {
		/*ONB uvw;
		uvw.Build_From(rec.NormalDirection);
		Vector3 direction = uvw.Local(Material::Random_Cosine_Direction());
		scattered = Ray(rec.HitPoint, direction.UnitVector());*/
		Vector3 target = rec.HitPoint + rec.NormalDirection + Random_in_unit_sphere();
		scattered = Ray(rec.HitPoint, target - rec.HitPoint);
		attenuation = albedo->Value(rec.u, rec.v, rec.HitPoint);
		//pdf = rec.NormalDirection.Dot(scattered.Direction()) / MPI;
		/*pdf = uvw.w().Dot(scattered.Direction()) / MPI;*/
		return true;
	}

	virtual float Scattering_pdf(Ray& ray_in, Hit_Record& rec,  Ray& scattered) {
		float cosine = rec.NormalDirection.Dot(scattered.Direction().UnitVector());
		if (cosine < 0)  cosine = 0;
		return cosine / MPI;
	}

	


};