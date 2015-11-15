//
// Created by eyefrog on 15/7/16.
//

#include "SingleSphere.h"
#include "../World/World.h"

SingleSphere::SingleSphere(void)
		:
		Tracer() { }

SingleSphere::SingleSphere(World* world_ptr)
		:
		Tracer(world_ptr) { }

SingleSphere::~SingleSphere() { }

RGBColor
SingleSphere::trace_ray(const Ray& ray) const
{
	ShadeRec sr(*world_ptr);
	double t;

	if (world_ptr->sphere.hit(ray, t, sr))
		return (red);
	else
		return (black);
}