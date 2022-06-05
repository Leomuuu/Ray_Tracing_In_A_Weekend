#pragma once
#include "Vector3.h"
#include "ONB.h"
#include "Material.h"
#include <cmath>

class PDF {
public:
	virtual float Value(Vector3 direction){
		return 0;
	};
	virtual Vector3 Generate(){
		return Vector3(0, 0, 0);
	};

};

//对cos theta 采样
class Cosine_PDF :public PDF {
public:
	ONB uvw;

	Cosine_PDF(Vector3& w) { uvw.Build_From(w); }
	virtual float Value(Vector3 direction) {
		float cosine = direction.UnitVector().Dot(uvw.w());
		if (cosine < 0)
			return 0;
		return cosine/MPI;
	}
	virtual Vector3 Generate() {
		return uvw.Local(Material::Random_Cosine_Direction());
	}
};

//对目标物体采样
class Hitable_PDF :public PDF {
public:
	Vector3 o;
	HitableObject* ptr;
	Hitable_PDF(HitableObject* p,Vector3& origin):
		ptr(p), o(origin) {}
	virtual float Value(Vector3 direction) {
		return ptr->pdf_value(o, direction);
	}
	virtual Vector3 Generate() {
		return ptr->random(o);
	}
};

//对GGX 法线分布函数采样
class GGX_PDF :public PDF {
public:
	float roughness;
	ONB uvw;

	GGX_PDF(float alpha,Vector3& w) :roughness(alpha){ uvw.Build_From(w); }

	virtual float Value(Vector3 direction) {
		float z = direction.Dot(uvw.w().UnitVector());

		float d = (z * roughness - z) * z + 1;
		float D = roughness / (MPI * d * d);
		return D * z;
	}

	virtual Vector3 Generate() {
		float e1 = RANDfloat01;
		float e2 = RANDfloat01;
		
		float theta = acos(sqrt((1 - e2) / (e2 * (roughness * roughness-1) + 1)));
		float phi = 2 * MPI * e1;

		Vector3 ret(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));

		return uvw.Local(ret);
	}

};

class Mixture_PDF :public PDF {
public:
	PDF* p[2];
	float p0ratio;
	Mixture_PDF(PDF* p0, PDF* p1,float ratio) {
		p[0] = p0;
		p[1] = p1;
		p0ratio = ratio;
	}
	virtual float MixValue(Vector3 direction,int index) {
		return p[index]->Value(direction);

		//return p0ratio * p[0]->Value(direction) +
		//	(1-p0ratio) * p[1]->Value(direction);
	}
	virtual Vector3 MixGenerate(int & index) {
		/*return (p[0]->Generate()) * (p[1]->Generate()) * p0ratio;*/

		if (RANDfloat01 < p0ratio) {
			index = 0;
			return p[0]->Generate();
		}
		index = 1;
		return p[1]->Generate();
	}
};