#pragma once
#include <cmath>
#include "Material.h"

//折射介质
class Dielectric :public Material {
public:
	double ref_idx;

	Dielectric(double ri) :ref_idx(ri) {}

	virtual bool Scatter(Ray& ray_in, Hit_Record& rec, Vector3& attenuation, Ray& scattered) {
		Vector3 outward_normal;
		Vector3 reflected = Reflect(ray_in.Direction(), rec.NormalDirection);
		double ni_over_nt;
		attenuation = Vector3(1, 1, 1);
		Vector3 refracted;
		double reflect_prob;
		double cosine;
		if (ray_in.Direction().Dot(rec.NormalDirection) > 0) {
			outward_normal = -rec.NormalDirection;
			ni_over_nt = ref_idx;
			cosine = ref_idx * ray_in.Direction().Dot(rec.NormalDirection)
				/ ray_in.Direction().Length();
		}
		else {
			outward_normal = rec.NormalDirection;
			ni_over_nt = 1.0 / ref_idx;
			cosine=-ray_in.Direction().Dot(rec.NormalDirection)
				/ ray_in.Direction().Length();
		}
		if (Refract(ray_in.Direction(), outward_normal, ni_over_nt, refracted)) {
			reflect_prob = Schlick(cosine, ref_idx);
		}
		else {
			scattered = Ray(rec.HitPoint, reflected);
			reflect_prob = 1.0;
		}
		if (RANDDOUBLE01 < reflect_prob) {
			scattered = Ray(rec.HitPoint, reflected);
		}
		else {
			scattered = Ray(rec.HitPoint, refracted);
		}
		return true;
	}


	double Schlick(double cosine, double ref_idx) {
		double r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}

		

};