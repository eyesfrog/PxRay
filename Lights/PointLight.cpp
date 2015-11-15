//
//  PointLight.cpp
//  TinyRay
//
//  Created by eyefrog on 15/7/31.
//  Copyright (c) 2015年 eyefrog. All rights reserved.
//

#include "PointLight.h"
#include "../Utilities/ShadeRec.h"
#include "../World/World.h"

PointLight::PointLight(void)
		:
		Light(), ls(1.0), color(1.0), location(0.0) { }

PointLight::PointLight(const PointLight& pl)
		:
		Light(pl), ls(pl.ls), color(pl.color), location(pl.location) { }

PointLight::~PointLight() { }

PointLight&
PointLight::operator=(const PointLight& rhs)
{
	if (this==&rhs) {
		return *this;
	}

	Light::operator=(rhs);

	ls = rhs.ls;
	color = rhs.color;
	location = rhs.location;

	return *this;
}

Light*
PointLight::clone(void) const
{
	return new PointLight(*this);
}

Vector3D
PointLight::get_direction(ShadeRec& sr)
{
	return (location-sr.hit_point).hat();
}

RGBColor
PointLight::L(ShadeRec& sr)
{
	return ls*color;
}

bool
PointLight::in_shadow(const Ray& ray, const ShadeRec& sr) const
{
	double t;
	int num_objects = int(sr.w.objects.size());

	float d = location.distance(ray.o);

	for (int j = 0; j<num_objects; ++j) {
		if (sr.w.objects[j]->shadow_hit(ray, t) && t<d) {
			return true;
		}
	}

	return false;
}