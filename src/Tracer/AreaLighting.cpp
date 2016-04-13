//
// Created by eyesfrog on 16/4/12.
//

#include "AreaLighting.h"
#include "../Materials/Material.h"

AreaLighting::AreaLighting(void)
		:Tracer() { }

AreaLighting::AreaLighting(World* w_ptr)
		:Tracer(w_ptr) { }

AreaLighting::~AreaLighting() { }

RGBColor
AreaLighting::trace_ray(const Ray ray, const int depth) const
{
	if (depth>world_ptr->vp.max_depth)
		return (black);
	else {
		ShadeRec sr(world_ptr->hit_object(ray));

		if (sr.hit_an_object) {
			sr.depth = depth;
			sr.ray = ray;

			return (sr.material_ptr->area_light_shade(sr));
		}
		else
			return (world_ptr->back_ground_color);
	}
}
