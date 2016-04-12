//
// Created by eyesfrog on 15/7/15.
//

#ifndef TINYRAY_VIEWPLANE_H
#define TINYRAY_VIEWPLANE_H

#include "../Sampler/Regular.h"
#include "../Sampler/MultiJittered.h"
#include "../Sampler/Sampler.h"

class ViewPlane {
public:
	int hres;   // horizontal image resolution
	int vres;   // vertical image resolution
	float s;    // pixel size
	float gamma;    // monitor gamma factor
	float inv_gamma;    // one over gamma
	int num_samples;    //num of samples per pixel
	int max_depth;
	Sampler* sampler_ptr;

public:
	ViewPlane(void);

	ViewPlane(const ViewPlane& vp);

	ViewPlane& operator=(const ViewPlane& rhs);

	~ViewPlane();

	void set_hres(const int h_res);

	void set_vres(const int v_res);

	void set_pixel_size(const float size);

	void set_gamma(const float g);

	//void set_gamut_display(const bool show);

	void set_samples(const int n);

	void set_sampler(Sampler* sp);

	void set_max_depth(const int n);

};

inline void
ViewPlane::set_hres(const int h_res)
{
	hres = h_res;
}

inline void
ViewPlane::set_vres(const int v_res)
{
	vres = v_res;
}

inline void
ViewPlane::set_pixel_size(const float size)
{
	s = size;
}

inline void
ViewPlane::set_gamma(const float g)
{
	gamma = g;
	inv_gamma = 1.0/gamma;
}

inline void
ViewPlane::set_max_depth(const int n)
{
	max_depth = n;
}

#endif //TINYRAY_VIEWPLANE_H
