#pragma once
#include "Vector3.h"
#include "Ray.h"

class Camera {



public:
	Vector3 origin; 
	Vector3 lower_left_corner;
	Vector3 horizontal;
	Vector3 vertical;


	Camera(Vector3 _origin,Vector3 _lower_left_corner,Vector3 _horizontal, Vector3 _vertical):
		origin(_origin),lower_left_corner(_lower_left_corner),horizontal(_horizontal),vertical(_vertical)
	{
	
	}


	Ray GetRay(double u, double v) {
		return Ray(origin, lower_left_corner + horizontal * u + vertical * v - origin);
	}

};