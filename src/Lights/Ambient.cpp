//
//  Ambient.cpp
//  TinyRay
//
//  Created by eyefrog on 15/7/31.
//  Copyright (c) 2015年 eyefrog. All rights reserved.
//

#include "Ambient.h"

Ambient::Ambient(void)
		:
		Light(), ls(1.0), color(1.0) { }

Ambient::Ambient(const Ambient& a)
		:
		Light(a), ls(a.ls), color(a.color) { }

Ambient::~Ambient() { }

Ambient&
Ambient::operator=(const Ambient& rhs)
{
	if (this==&rhs) {
		return *this;
	}
	Light::operator=(rhs);

	ls = rhs.ls;
	color = rhs.color;

	return *this;
}

Light* Ambient::clone(void) const
{
	return new Ambient(*this);
}

Vector3D
Ambient::get_direction(ShadeRec& s)
{
	return Vector3D(0.0);
}

RGBColor
Ambient::L(ShadeRec& sr)
{
	return ls*color;
}

bool
Ambient::in_shadow(const Ray& ray, const ShadeRec& sr) const
{
	return false;
}