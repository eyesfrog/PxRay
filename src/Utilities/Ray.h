//
// Created by eyesfrog on 15/7/15.
//

#ifndef TINYRAY_RAY_H
#define TINYRAY_RAY_H

#include "Point3D.h"
#include "Vector3D.h"

class Ray {
public:

	Point3D o;
	Vector3D d;

	Ray(void);

	Ray(const Point3D& origin, const Vector3D& dir);

	Ray(const Ray& ray);

	~Ray();

	Ray& operator=(const Ray& rhs);
};

#endif //TINYRAY_RAY_H
