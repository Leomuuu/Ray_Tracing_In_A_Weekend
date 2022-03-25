#pragma once
#include "Vector3.h"
#include "Ray.h"

class NormalCamera {
public:
	Vector3 origin;
	Vector3 lower_left_corner;
	Vector3 horizontal;
	Vector3 vertical;
	Vector3 u, v, w;


	NormalCamera(Vector3 lookfrom, Vector3 lookat, Vector3 vup,
		double vfov, double aspect);


	virtual Ray GetRay(double s, double t);


};


class DefocusBlurCamera {
public:
	Vector3 origin;
	Vector3 lower_left_corner;
	Vector3 horizontal;
	Vector3 vertical;
	Vector3 u, v, w;
	double lens_radius;


	DefocusBlurCamera(Vector3 lookfrom,Vector3 lookat,Vector3 vup,
		double vfov,double aspect,double aperture,double focus_dist);


	virtual Ray GetRay(double s, double t) ;

};

