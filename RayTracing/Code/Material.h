#pragma once
#include "Ray.h"
#include "Hitable.h"
#include "Vector3.h"

class Material {
public:
	virtual bool Scatter(Ray& ray_in, Hit_Record& rec, Vector3& attenuation, Ray& scattered) = 0;

};