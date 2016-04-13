//
// Created by eyesfrog on 15/7/16.
//

#ifndef TINYRAY_SPHERE_H
#define TINYRAY_SPHERE_H

#include "GeometricObject.h"

class Sphere : public GeometricObject {

public:
	Sphere(void);

	Sphere(Point3D c, double r);

	Sphere(const Sphere& sphere);

	~Sphere();

	virtual Sphere* clone(void) const;

	Sphere& operator=(const Sphere& sphere);

	void set_center(const Point3D& p);

	void set_center(const double x, const double y, const double z);

	void set_radius(const double r);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

	virtual bool shadow_hit(const Ray& ray, double& tmin) const;

protected:

	Point3D center;
	double radius;

	static const double kEpsilon;
};

inline void
Sphere::set_center(const Point3D& p)
{
	center = p;
}

inline void
Sphere::set_center(const double x, const double y, const double z)
{
	center.x = x;
	center.y = y;
	center.z = z;
}

inline void
Sphere::set_radius(const double r)
{
	radius = r;
}

#endif //TINYRAY_SPHERE_H
