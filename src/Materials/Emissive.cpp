//
// Created by eyesfrog on 16/4/12.
//

#include "Emissive.h"

Emissive::Emissive(void)
		:
		Material() { }

Emissive::Emissive(const Emissive& m)
		:
		Material(m) { }

Emissive*
Emissive::clone(void) const
{
	return (new Emissive(*this));
}

Emissive&
Emissive::operator=(const Emissive& rhs)
{
	if (this==&rhs) {
		return *this;
	}
	Material::operator=(rhs);

	return *this;
}

Emissive::~Emissive() { }

RGBColor
Emissive::shade(ShadeRec& sr)
{
	if(-sr.normal * sr.ray.d > 0.0)
		return (ls*ce);
	else
		return black;
}

RGBColor
Emissive::area_light_shade(ShadeRec& sr) {
	if(-sr.normal * sr.ray.d > 0.0)
		return (ls*ce);
	else
		return black;
};
