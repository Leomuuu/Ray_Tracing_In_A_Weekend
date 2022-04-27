#pragma once
#include "Vector3.h"
#include "ONB.h"
#include "Material.h"

class PDF {
public:
	virtual float Value(Vector3 direction) = 0;
	virtual Vector3 Generate() = 0;

};

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

class Mixture_PDF :public PDF {
public:
	PDF* p[2];
	float p0ratio;
	Mixture_PDF(PDF* p0, PDF* p1,float ratio) {
		p[0] = p0;
		p[1] = p1;
		p0ratio = ratio;
	}
	virtual float Value(Vector3 direction) {
		return p0ratio * p[0]->Value(direction) +
			(1-p0ratio) * p[1]->Value(direction);
	}
	virtual Vector3 Generate() {
		if (RANDfloat01 < p0ratio)
			return p[0]->Generate();
		return p[1]->Generate();

	}
};