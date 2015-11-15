//
//  Pinhole.cpp
//  TinyRay
//
//  Created by eyefrog on 15/7/21.
//  Copyright (c) 2015年 eyefrog. All rights reserved.
//

#include "Pinhole.h"

Pinhole::Pinhole(void)
		:
		Camera(),
		d(500),
		zoom(1.0) { }

Pinhole::Pinhole(const Pinhole& ph)
		:
		Camera(ph),
		d(ph.d),
		zoom(ph.zoom) { }

Camera*
Pinhole::clone(void) const
{
	return (new Pinhole(*this));
}

Pinhole&
Pinhole::operator=(const Pinhole& rhs)
{
	if (this==&rhs) {
		return *this;
	}

	Camera::operator=(rhs);

	d = rhs.d;
	zoom = rhs.zoom;

	return *this;
}

Pinhole::~Pinhole() { }

Vector3D
Pinhole::get_direction(const Point2D& p) const
{
	Vector3D dir = p.x*u+p.y*v-d*w;
	dir.normalize();

	return dir;
}

void
Pinhole::render_scene(const World& w)
{
	RGBColor L;
	ViewPlane vp(w.vp);
	Ray ray;
	//int depth = 0;
	Point2D pp;
	Point2D sp;

	vp.s /= zoom;

	ray.o = eye;

	FILE* f = fopen("/Users/eyefrog/Desktop/image.bmp", "w");
	fprintf(f, "P3\n%d %d\n%d\n", vp.hres, vp.vres, 255);

	for (int r = vp.vres-1; r>=0; --r) {
		for (int c = 0; c<vp.vres; ++c) {
			L = black;
			for (int j = 0; j<vp.num_samples; ++j) {
				sp = w.vp.sampler_ptr->sample_unit_square();
				pp.x = vp.s*(c-0.5*vp.hres+sp.x);
				pp.y = vp.s*(r-0.5*vp.vres+sp.y);
				ray.d = get_direction(pp);
				L += w.tracer_ptr->trace_ray(ray);
			}
			L /= vp.num_samples;
			L *= exposure_time;
			//L = w.clamp_to_color(L);
			L = w.max_to_one(L);
			fprintf(f, "%d %d %d \n", int(L.r*255), int(L.g*255), int(L.b*255));
		}
	}
	fclose(f);
}