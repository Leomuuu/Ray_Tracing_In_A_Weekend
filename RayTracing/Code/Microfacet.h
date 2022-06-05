#pragma once
#include "Material.h"
#include "Texture.h"
#include "ONB.h"
#include "PDF.h"

//微表面模型材质
class Microfacet :public Material {

public:

	float roughness;//粗糙度
	float ref_idx;//折射率
	Texture *texture; //颜色

	Microfacet(float rough, float refidx,Texture* color) {
		roughness = rough;
		ref_idx = refidx;
		texture = color;
	}


	virtual bool Scatter(Ray& ray_in, Hit_Record& rec, Scatter_Record& srec) {
		srec.is_specular = false;
		srec.is_microfacet = true;
		srec.attenuation =Vector3(1,1,1);
		return true;
	}

	virtual Vector3 Diffuse_Scattering_pdf(Ray& ray_in, Hit_Record& rec, Ray& scattered) {
		float cosine = rec.NormalDirection.Dot(scattered.Direction().UnitVector());
		if (cosine < 0)  cosine = 0;
		Vector3 brdf = texture->Value(rec.u, rec.v, rec.HitPoint)/MPI;

		return brdf * cosine;
	}

	// brdf * cos theta
	virtual float Scattering_pdf(Ray& ray_in, Hit_Record& rec, Ray& scattered) {
		Vector3 normal = rec.NormalDirection.UnitVector();
		Vector3 rayin = -ray_in.Direction().UnitVector();
		Vector3 rayout = scattered.Direction().UnitVector();

		if (normal.Dot(rayin) <= 0 || normal.Dot(rayout) <= 0) return 0;

		float brdf = (GGX(normal, rayin, rayout) * Fernel(normal, rayin, rayout) * Geometry(normal, rayin, rayout)) /
			(4 * std::max(0.0f,normal.Dot(rayin)) * std::max(0.0f,normal.Dot(rayout)));
		
		float cosine = rec.NormalDirection.Dot(scattered.Direction().UnitVector());
		return brdf * cosine;
	}

	// 法线分布函数
	float GGX(Vector3& normal,Vector3& rayin, Vector3& rayout) {

		Vector3 halfvector = (rayin.UnitVector() + rayout.UnitVector()).UnitVector();

		float ret = (roughness * roughness) /
			(MPI * pow((pow(normal.Dot(halfvector),2)*(roughness*roughness-1)+1), 2));

		return ret;
	}

	// 菲涅尔项  Schlick 近似
	float Fernel(Vector3& normal, Vector3& rayin, Vector3& rayout) {

		float r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;

		return r0 + (1 - r0) * pow((1 - rayin.Dot(normal)), 5);
	}

	// 几何项
	float Geometry(Vector3& normal, Vector3& rayin, Vector3& rayout) {

		float alpha = pow((roughness+1)/2, 2);
		float k = alpha / 2;

		auto G = [k](Vector3& normal,Vector3& raydirection) {
			float nr = normal.Dot(raydirection);
			return (nr) / ((nr) * (1 - k) + k);
		};

		return G(normal, rayin)*G(normal, rayout);

	}
};