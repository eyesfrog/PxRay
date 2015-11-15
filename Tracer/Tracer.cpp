//
// Created by eyefrog on 15/7/16.
//

#include "Tracer.h"

Tracer::Tracer(void)
		:
		world_ptr(NULL) { }

Tracer::Tracer(World* w_ptr)
		:
		world_ptr(w_ptr) { }

Tracer::~Tracer()
{
	if (world_ptr)
		world_ptr = NULL;
}

RGBColor
Tracer::trace_ray(const Ray& ray) const
{
	return black;
}

RGBColor
Tracer::trace_ray(const Ray ray, const int depth) const
{
	return black;
}