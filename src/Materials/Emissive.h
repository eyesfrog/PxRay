//
// Created by eyesfrog on 16/4/12.
//

#ifndef TINYRAY_EMISSIVE_H
#define TINYRAY_EMISSIVE_H

#include "Material.h"

class Emissive : public Material {
public:
	Emissive(void);

	Emissive(const Emissive& m);

	virtual Emissive* clone(void) const;

	Emissive& operator=(const Emissive& rhs);

	~Emissive();

	void scale_radiance(const float ls);

	void set_ce(const RGBColor& color);

	virtual RGBColor get_Le(ShadeRec& sr) const;

	virtual RGBColor shade(ShadeRec& sr);

	virtual RGBColor area_light_shade(ShadeRec& sr);

private:

	float ls;

	RGBColor ce;
};

inline void Emissive::scale_radiance(const float ls) {
	this->ls = ls;
}

inline void Emissive::set_ce(const RGBColor& color) {
	this->ce = color;
}

inline RGBColor Emissive::get_Le(ShadeRec& sr) const
{
	return (ls*ce);
}

#endif //TINYRAY_EMISSIVE_H
