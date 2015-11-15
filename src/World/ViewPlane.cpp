//
// Created by eyefrog on 15/7/15.
//

#include "ViewPlane.h"

ViewPlane::ViewPlane(void)
		:
		hres(200),
		vres(200),
		s(1.0),
		gamma(1.0),
		inv_gamma(1.0),
		num_samples(50),
		max_depth(0),
		sampler_ptr(nullptr) { }

ViewPlane::ViewPlane(const ViewPlane& vp)
		:
		hres(vp.hres),
		vres(vp.vres),
		s(vp.s),
		gamma(vp.gamma),
		inv_gamma(vp.inv_gamma),
		num_samples(vp.num_samples),
		max_depth(vp.max_depth),
		sampler_ptr(vp.sampler_ptr) { }

ViewPlane& ViewPlane::operator=(const ViewPlane& rhs)
{
	if (this==&rhs)
		return (*this);

	hres = rhs.hres;
	vres = rhs.vres;
	s = rhs.s;
	gamma = rhs.gamma;
	inv_gamma = rhs.inv_gamma;
	num_samples = rhs.num_samples;

	return (*this);
}

ViewPlane::~ViewPlane() { }

void
ViewPlane::set_samples(const int n)
{
	num_samples = n;

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if (num_samples>1)
		sampler_ptr = new MultiJittered(num_samples);
	else
		sampler_ptr = new Regular(1);
}

void
ViewPlane::set_sampler(Sampler* sp)
{
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	num_samples = sp->get_num_samples();
	sampler_ptr = sp;
}