//
// Created by eyefrog on 15/7/17.
//

#include "MultipleObjects.h"

MultipleObjects::MultipleObjects(void)
		:
		Tracer() { }

MultipleObjects::MultipleObjects(World* w_ptr)
		:
		Tracer(w_ptr) { }

MultipleObjects::~MultipleObjects() { }

RGBColor MultipleObjects::trace_ray(const Ray& ray) const
{
	ShadeRec sr(world_ptr->hit_bare_bones_objects(ray));

	if (sr.hit_an_object)
		return sr.color;
	else
		return world_ptr->back_ground_color;
}