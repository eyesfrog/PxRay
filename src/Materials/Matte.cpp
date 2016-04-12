//
//  Matte.cpp
//  TinyRay
//
//  Created by eyesfrog on 15/7/31.
//  Copyright (c) 2015年 eyesfrog. All rights reserved.
//

#include "Matte.h"

Matte::Matte(void)
		:
		Material(),
		ambient_brdf(new Lambertian),
		diffuse_brdf(new Lambertian) { }

Matte::Matte(const Matte& m)
		:
		Material(m)
{
	if (m.ambient_brdf) {
		ambient_brdf = (Lambertian*) m.ambient_brdf->clone();
	}
	else ambient_brdf = NULL;

	if (m.diffuse_brdf) {
		diffuse_brdf = (Lambertian*) m.diffuse_brdf->clone();
	}
	else diffuse_brdf = NULL;
}

Material*
Matte::clone(void) const
{
	return new Matte(*this);
}

Matte&
Matte::operator=(const Matte& rhs)
{
	if (this==&rhs) {
		return *this;
	}
	Material::operator=(rhs);

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if (rhs.ambient_brdf) {
		ambient_brdf = (Lambertian*) rhs.ambient_brdf->clone();
	}

	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}

	if (rhs.diffuse_brdf) {
		diffuse_brdf = (Lambertian*) rhs.diffuse_brdf->clone();
	}

	return *this;
}

Matte::~Matte()
{
	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}
}

RGBColor
Matte::shade(ShadeRec& sr)
{
	Vector3D wo = -sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr, wo)*sr.w.ambient_ptr->L(sr);
	int num_lights = int(sr.w.lights.size());

	for (int j = 0; j<num_lights; ++j) {
		Vector3D wi = sr.w.lights[j]->get_direction(sr);
		float ndotwi = sr.normal*wi;

		if (ndotwi>0.0) {
			bool in_shadow = false;
			if (sr.w.lights[j]->casts_shadows()) {
				Ray shadowRay(sr.hit_point, wi);
				in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
			}
			if (!in_shadow) {
				L += diffuse_brdf->f(sr, wo, wi)*sr.w.lights[j]->L(sr)*ndotwi;
			}
		}
	}

	return L;

}