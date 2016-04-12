//
//  Whitted.cpp
//  TinyRay
//
//  Created by eyesfrog on 15/8/3.
//  Copyright (c) 2015年 eyesfrog. All rights reserved.
//

#include "Whitted.h"
#include "../World/World.h"
#include "../Materials/Material.h"

Whitted::Whitted(void)
		:
		Tracer() { }

Whitted::Whitted(World* _worldPtr)
		:
		Tracer(_worldPtr) { }

Whitted::~Whitted() { }

RGBColor
Whitted::trace_ray(const Ray ray, const int depth) const
{
	if (depth>world_ptr->vp.max_depth)
		return black;
	else {
		ShadeRec sr(world_ptr->hit_object(ray));

		if (sr.hit_an_object) {
			sr.depth = depth;
			sr.ray = ray;
			return sr.material_ptr->shade(sr);
		}
		else
			return world_ptr->back_ground_color;
	}
}