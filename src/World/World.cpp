//
// Created by eyesfrog on 15/7/15.
//

#include "../World/World.h"


World::World(void)
		:
		back_ground_color(black),
		tracer_ptr(NULL),
		camera_ptr(NULL),
		ambient_ptr(new Ambient) { }

World::~World()
{
	if (tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}

	if (ambient_ptr) {
		delete ambient_ptr;
		ambient_ptr = NULL;
	}
	if (camera_ptr) {
		delete camera_ptr;
		camera_ptr = NULL;
	}

	delete_objects();
	delete_lights();
	delete_materials();
}



RGBColor
World::max_to_one(const RGBColor& c) const
{
	float max_value = max(c.r, max(c.g, c.b));

	if (max_value>1.0) {
		return c/max_value;
	}
	else
		return c;
}

RGBColor
World::clamp_to_color(const RGBColor& raw_color) const
{
	RGBColor c(raw_color);

	if (raw_color.r>1.0 || raw_color.g>1.0 || raw_color.b>1.0) {
		c.r = 1.0;
		c.g = 0.0;
		c.b = 0.0;
	}

	return c;
}

ShadeRec World::hit_bare_bones_objects(const Ray& ray)
{
	ShadeRec sr(*this);
	double t;
	double tmin = kHugeValue;
	int num_objects = int(objects.size());

	for (int j = 0; j<num_objects; ++j) {
		if (objects[j]->hit(ray, t, sr) && (t<tmin)) {
			sr.hit_an_object = true;
			tmin = t;
			sr.color = objects[j]->get_color();
		}
	}
	return sr;
}

ShadeRec World::hit_object(const Ray& ray)
{
	ShadeRec sr(*this);
	double t;
	Normal normal;
	Point3D local_hit_point;
	double tmin = kHugeValue;
	int num_objects = int(objects.size());

	for (int j = 0; j<num_objects; ++j) {
		if (objects[j]->hit(ray, t, sr) && (t<tmin)) {
			sr.hit_an_object = true;
			tmin = t;
			sr.material_ptr = objects[j]->get_material();
			sr.hit_point = ray.o+t*ray.d;
			normal = sr.normal;
			local_hit_point = sr.local_hit_point;
		}
	}

	if (sr.hit_an_object) {
		sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}

	return sr;
}

void
World::delete_lights()
{
	int num_lights = int(lights.size());

	for (int j = 0; j<num_lights; ++j) {
		delete lights[j];
		lights[j] = NULL;
	}

	lights.erase(lights.begin(), lights.end());
}

void
World::delete_objects()
{
	int num_objects = int(objects.size());

	for (int j = 0; j<num_objects; ++j) {
		delete objects[j];
		objects[j] = NULL;
	}

	objects.erase(objects.begin(), objects.end());
}

void
World::delete_materials()
{
	int num_materials = int(objects.size());

	for (int j = 0; j<num_materials; ++j) {
		delete materials[j];
		materials[j] = NULL;
	}

	materials.erase(materials.begin(), materials.end());
}


