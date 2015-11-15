//
//  PointLight.h
//  TinyRay
//
//  Created by eyefrog on 15/7/31.
//  Copyright (c) 2015年 eyefrog. All rights reserved.
//

#ifndef __TinyRay__PointLight__
#define __TinyRay__PointLight__

#include "Light.h"

class PointLight : public Light {
public:
	PointLight(void);

	PointLight(const PointLight& pl);

	~PointLight();

	PointLight&
			operator=(const PointLight& rhs);

	virtual Light* clone(void) const;

	virtual Vector3D
			get_direction(ShadeRec& sr);

	virtual RGBColor
			L(ShadeRec& sr);

	void scale_radiance(const float b);

	void set_color(const float c);

	void set_color(const float _r, const float _g, const float _b);

	void set_color(const RGBColor& c);

	void set_location(const double _x, const double _y, const double _z);

	void set_location(const Point3D& p);

	bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

private:
	float ls;
	RGBColor color;
	Point3D location;
};

inline void
PointLight::scale_radiance(const float b)
{
	ls = b;
}

inline void
PointLight::set_color(const float c)
{
	color.r = c;
	color.g = c;
	color.b = c;
}

inline void
PointLight::set_color(const float _r, const float _g, const float _b)
{
	color.r = _r;
	color.g = _g;
	color.b = _b;
}

inline void
PointLight::set_color(const RGBColor& c)
{
	color = c;
}

inline void
PointLight::set_location(const Point3D& p)
{
	location = p;
}

inline void
PointLight::set_location(const double _x, const double _y, const double _z)
{
	location.x = _x;
	location.y = _y;
	location.z = _z;
}

#endif /* defined(__TinyRay__PointLight__) */
