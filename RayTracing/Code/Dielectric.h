#pragma once
#include <cmath>
#include "Material.h"

//折射介质
class Dielectric :public Material {
public:
	float ref_idx;

	Dielectric(float ri) :ref_idx(ri) {}

	virtual bool Scatter(Ray& ray_in, Hit_Record& rec, Scatter_Record&srec) {
		Vector3 outward_normal;
		Vector3 reflected = Reflect(ray_in.Direction(), rec.NormalDirection);
		float ni_over_nt;
		srec.attenuation = Vector3(1, 1, 1);
		srec.is_specular = true;
		srec.is_microfacet = false;
		Vector3 refracted;
		float reflect_prob;
		float cosine;
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
			srec.specular_ray = Ray(rec.HitPoint, reflected);
			reflect_prob = 1.0;
		}
		if (RANDfloat01 < reflect_prob) {
			srec.specular_ray = Ray(rec.HitPoint, reflected);
		}
		else {
			srec.specular_ray = Ray(rec.HitPoint, refracted);
		}
		return true;
	}


	float Schlick(float cosine, float ref_idx) {
		float r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}

		

};