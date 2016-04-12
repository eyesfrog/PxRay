//
// Created by eyesfrog on 15/7/16.
//

#include <math.h>
#include "Sphere.h"

const double Sphere::kEpsilon = 0.001;

Sphere::Sphere(void)
		:
		GeometricObject(),
		center(0.0),
		radius(1.0) { }

Sphere::Sphere(Point3D c, double r)
		:
		GeometricObject(),
		center(c),
		radius(r) { }

Sphere::Sphere(const Sphere& sphere)
		:
		GeometricObject(),
		center(sphere.center),
		radius(sphere.radius) { }

Sphere::~Sphere() { }

Sphere*
Sphere::clone(void) const
{
	return (new Sphere(*this));
}

Sphere& Sphere::operator=(const Sphere& sphere)
{
	if (this==&sphere)
		return (*this);

	center = sphere.center;
	radius = sphere.radius;

	return (*this);
}

bool
Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	double t;
	Vector3D temp = ray.o-center;
	double a = ray.d*ray.d;
	double b = 2.0*temp*ray.d;
	double c = temp*temp-radius*radius;
	double disc = b*b-4.0*a*c;

	if (disc<0.0)
		return (false);
	else {
		double e = sqrt(disc);
		double denom = 2.0*a;
		t = (-b-e)/denom;

		if (t>kEpsilon) {
			tmin = t;
			sr.normal = (temp+t*ray.d)/radius;
			sr.local_hit_point = ray.o+t*ray.d;
			return (true);
		}

		t = (-b+e)/denom;

		if (t>kEpsilon) {
			tmin = t;
			sr.normal = (temp+t*ray.d)/radius;
			sr.local_hit_point = ray.o+t*ray.d;
			return (true);
		}

	}
	return (false);
}

bool
Sphere::shadow_hit(const Ray& ray, double& tmin) const
{
	double t;
	Vector3D temp = ray.o-center;
	double a = ray.d*ray.d;
	double b = 2.0*temp*ray.d;
	double c = temp*temp-radius*radius;
	double disc = b*b-4.0*a*c;

	if (disc<0.0)
		return (false);
	else {
		double e = sqrt(disc);
		double denom = 2.0*a;
		t = (-b-e)/denom;

		if (t>kEpsilon) {
			tmin = t;
			return true;
		}

		t = (-b+e)/denom;

		if (t>kEpsilon) {
			tmin = t;
			return true;
		}

	}
	return false;
}