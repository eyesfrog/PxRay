//
//  Rectangle.h
//  TinyRay
//
//  Created by eyesfrog on 15/8/3.
//  Copyright (c) 2015年 eyesfrog. All rights reserved.
//

#ifndef __TinyRay__Rectangle__
#define __TinyRay__Rectangle__

#include "GeometricObject.h"
#include "../Sampler/Sampler.h"

class Rectangle : public GeometricObject {
public:
	Rectangle(void);

	Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b);

	Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& _n);

	virtual Rectangle* clone(void) const;

	Rectangle(const Rectangle& r);

	virtual ~Rectangle(void);

	Rectangle& operator=(const Rectangle& rhs);

	BBox get_bounding_box(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& s) const;

	virtual bool shadow_hit(const Ray& ray, double& tmin) const;

	void set_sampler(Sampler* sampler);

	virtual Point3D sample(void);

	virtual Normal get_normal(const Point3D& p);

	virtual float pdf(ShadeRec& sr);

private:
	Point3D p0;
	Vector3D a;
	Vector3D b;
	double a_len_squared;
	double b_len_squared;
	Normal normal;

	float area;
	float inv_area;
	Sampler* sampler_ptr;

	static const double kEpsilon;
};

#endif /* defined(__TinyRay__Rectangle__) */
