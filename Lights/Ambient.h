//
//  Ambient.h
//  TinyRay
//
//  Created by eyefrog on 15/7/31.
//  Copyright (c) 2015年 eyefrog. All rights reserved.
//

#ifndef __TinyRay__Ambient__
#define __TinyRay__Ambient__

#include "Light.h"

class Ambient : public Light {
public:
	Ambient(void);

	Ambient(const Ambient& a);

	virtual ~Ambient();

	Ambient&
			operator=(const Ambient& rhs);

	virtual Light* clone(void) const;

	void scale_radiance(const float b);

	void set_color(const float c);

	void set_color(const RGBColor& c);

	void set_color(const float _r, const float _g, const float _b);

	virtual Vector3D
			get_direction(ShadeRec& s);

	virtual RGBColor
			L(ShadeRec& s);

	virtual bool
			in_shadow(const Ray& ray, const ShadeRec& sr) const;

private:
	float ls;
	RGBColor color;
};

inline void
Ambient::scale_radiance(const float b)
{
	ls = b;
}

inline void
Ambient::set_color(const float c)
{
	color.r = c;
	color.g = c;
	color.b = c;
}

inline void
Ambient::set_color(const float _r, const float _g, const float _b)
{
	color.r = _r;
	color.g = _g;
	color.b = _b;
}

inline void
Ambient::set_color(const RGBColor& c)
{
	color = c;
}

#endif /* defined(__TinyRay__Ambient__) */
