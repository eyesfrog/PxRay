//
// Created by eyesfrog on 15/7/15.
//

#include "Plane.h"

const double Plane::kEpsilon = 0.001;

Plane::Plane(void)
		:
		GeometricObject(),
		point(0.0),
		normal(0, 1, 0) { }

Plane::Plane(const Point3D& p, const Normal& n)
		:
		GeometricObject(),
		point(p),
		normal(n) { }

Plane::Plane(const Plane& plane)
		:
		GeometricObject(),
		point(plane.point),
		normal(plane.normal) { }

Plane*
Plane::clone(void) const
{
	return (new Plane(*this));
}

Plane::~Plane() { }

Plane&
Plane::operator=(const Plane& rhs)
{

	if (this==&rhs)
		return (*this);

	GeometricObject::operator=(rhs);

	point = rhs.point;
	normal = rhs.normal;

	return (*this);
}

bool
Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	double t = (point-ray.o)*normal/(ray.d*normal);

	if (t>kEpsilon) {
		tmin = t;
		sr.normal = normal;
		sr.local_hit_point = ray.o+t*ray.d;

		return (true);
	}
	else
		return (false);

}

bool
Plane::shadow_hit(const Ray& ray, double& tmin) const
{
	double t = (point-ray.o)*normal/(ray.d*normal);

	if (t>kEpsilon) {
		tmin = t;
		return true;
	}
	else return false;
}
