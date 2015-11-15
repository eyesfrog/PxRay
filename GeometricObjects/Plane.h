//
// Created by eyefrog on 15/7/15.
//

#ifndef TINYRAY_PLANE_H
#define TINYRAY_PLANE_H

#include "GeometricObject.h"

class Plane : public GeometricObject {

public:
	Plane(void);

	Plane(const Point3D& p, const Normal& n);

	Plane(const Plane& plane);

	virtual Plane*
			clone(void) const;

	Plane&
			operator=(const Plane& rhs);

	virtual bool
			hit(const Ray& ray, double& tmin, ShadeRec& s) const;

	virtual bool
			shadow_hit(const Ray& ray, double& tmin) const;

	~Plane();

private:
	Point3D point;  //point through which plane pass

	Normal normal;  //Normal to the plane

	static const double kEpsilon;
};

#endif //TINYRAY_PLANE_H
