//
// Created by eyesfrog on 15/7/15.
//

#include "Constants.h"
#include "ShadeRec.h"

ShadeRec::ShadeRec(World& wr)
		:
		hit_an_object(false),
		material_ptr(NULL),
		local_hit_point(),
		hit_point(),
		normal(),
		color(black),
		ray(),
		depth(0),
		t(0.0),
		dir(),
		w(wr) { }

ShadeRec::ShadeRec(const ShadeRec& sr)
		:
		hit_an_object(sr.hit_an_object),
		material_ptr(sr.material_ptr),
		local_hit_point(sr.local_hit_point),
		hit_point(sr.hit_point),
		normal(sr.normal),
		color(sr.color),
		ray(sr.ray),
		depth(sr.depth),
		t(sr.t),
		dir(sr.dir),
		w(sr.w) { }

ShadeRec::~ShadeRec() { }