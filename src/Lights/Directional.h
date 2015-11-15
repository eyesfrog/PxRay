//
//  Directional.h
//  TinyRay
//
//  Created by eyefrog on 15/7/31.
//  Copyright (c) 2015年 eyefrog. All rights reserved.
//

#ifndef __TinyRay__Directional__
#define __TinyRay__Directional__

#include "Light.h"
#include "../World/World.h"
#include "../Utilities/ShadeRec.h"

class Directional : public Light {
public:
	Directional(void);

	Directional(const Directional& dl);

	virtual Light* clone(void) const;

	Directional&
			operator=(const Directional& rhs);

	virtual ~Directional();

	void scale_radiance(const float b);

	void set_color(const float c);

	void set_color(const RGBColor& c);

	void set_color(const float _r, const float _g, const float _b);

	void set_direction(const Vector3D& d);

	void set_direction(const double _x, const double _y, const double _z);

	virtual Vector3D get_direction(ShadeRec& sr);

	virtual RGBColor
			L(ShadeRec& sr);

	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

private:
	float ls;
	RGBColor color;
	Vector3D dir;
};

inline void
Directional::scale_radiance(const float b)
{
	ls = b;
}

inline void
Directional::set_color(const float c)
{
	color.r = c;
	color.g = c;
	color.b = c;
}

inline void
Directional::set_color(const RGBColor& c)
{
	color = c;
}

inline void
Directional::set_color(const float _r, const float _g, const float _b)
{
	color.r = _r;
	color.g = _g;
	color.b = _b;
}

inline void
Directional::set_direction(const Vector3D& d)
{
	dir = d;
	dir.normalize();
}

inline void
Directional::set_direction(const double _x, const double _y, const double _z)
{
	dir.x = _x;
	dir.y = _y;
	dir.z = _z;
	dir.normalize();
}

#endif /* defined(__TinyRay__Directional__) */
