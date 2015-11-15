//
//  RayCast.cpp
//  TinyRay
//
//  Created by eyefrog on 15/7/31.
//  Copyright (c) 2015年 eyefrog. All rights reserved.
//

#include "RayCast.h"
#include "../World/World.h"
#include "../Materials/Material.h"

RayCast::RayCast(void)
		:
		Tracer() { }

RayCast::RayCast(World* _worldPtr)
		:
		Tracer(_worldPtr) { }

RayCast::~RayCast()
{
	if (world_ptr)
		world_ptr = NULL;
}

RGBColor
RayCast::trace_ray(const Ray& ray) const
{
	ShadeRec sr(world_ptr->hit_object(ray));

	if (sr.hit_an_object) {
		sr.ray = ray;
		return sr.material_ptr->shade(sr);
	}
	else
		return world_ptr->back_ground_color;
}