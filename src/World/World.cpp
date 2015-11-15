//
// Created by eyefrog on 15/7/15.
//

//Utilities
#include "../Utilities/Constants.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Normal.h"
#include "../Utilities/Ray.h"
#include "../Utilities/Math.h"

#include "World.h"

//Geomatric objects

//Tracers
#include "../Tracer/RayCast.h"

//Cameras
#include "../Camera/Pinhole.h"

//BRDFs

//Lights
#include "../Lights/PointLight.h"
#include "../Lights/Ambient.h"

//Materials
#include "../Materials/Matte.h"
#include "../Materials/Phong.h"
#include "../GeometricObjects/Plane.h"
#include "../Materials/Reflective.h"
#include "../GeometricObjects/Rectangle.h"
#include "../Tracer/Whitted.h"
#include "../Camera/Fisheye.h"

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

void
World::build()
{
	int num_samples = 16;

	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_samples(num_samples);
	vp.set_max_depth(20);

	tracer_ptr = new Whitted(this);

    Fisheye* fisheye_ptr = new Fisheye;

    fisheye_ptr->set_eye(7.5, 3, 9.5);
    fisheye_ptr->set_lookat(0);
    fisheye_ptr->compute_uvw();
    set_camera(fisheye_ptr);

	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(10, 10, 0);
	light_ptr1->scale_radiance(2.0);
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);

	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(0, 10, 10);
	light_ptr2->scale_radiance(2.0);
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);

	PointLight* light_ptr3 = new PointLight;
	light_ptr3->set_location(-10, 10, 0);
	light_ptr3->scale_radiance(2.0);
	light_ptr3->set_shadows(true);
	add_light(light_ptr3);

	PointLight* light_ptr4 = new PointLight;
	light_ptr4->set_location(0, 10, -10);
	light_ptr4->scale_radiance(2.0);
	light_ptr4->set_shadows(true);
	add_light(light_ptr4);

	Reflective* reflective_ptr1 = new Reflective;
	reflective_ptr1->set_ka(0.1);
	reflective_ptr1->set_kd(0.4);
	reflective_ptr1->set_cd(0.6);
	reflective_ptr1->set_ks(0.25);
	reflective_ptr1->set_exp(100.0);
	reflective_ptr1->set_kr(0.75);
	reflective_ptr1->set_cr(1, 1, 1);

	Sphere*	sphere_ptr1 = new Sphere(Point3D(0, 0.5, 0), 4);
	sphere_ptr1->set_material(reflective_ptr1);
	add_object(sphere_ptr1);

	double room_size = 11.0;

	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.50);
	matte_ptr1->set_kd(0.50);
	matte_ptr1->set_cd(1);

	Plane* ceiling_ptr = new Plane(Point3D(0, room_size,  0), Normal(0, -1, 0));
	ceiling_ptr->set_material(matte_ptr1);
	add_object(ceiling_ptr);

	Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(0.15);
	matte_ptr3->set_kd(0.60);
	matte_ptr3->set_cd(0.5, 0.5, 0.75);

	Plane* backWall_ptr = new Plane(Point3D(0, 0,  -room_size), Normal(0, 0, 1));
	backWall_ptr->set_material(matte_ptr3);
	add_object(backWall_ptr);

	Plane* frontWall_ptr = new Plane(Point3D(0, 0,  room_size), Normal(0, 0, -1));
	frontWall_ptr->set_material(matte_ptr3);
	add_object(frontWall_ptr);

	Matte* matte_ptr4 = new Matte;
	matte_ptr4->set_ka(0.15);
	matte_ptr4->set_kd(0.60);
	matte_ptr4->set_cd(0.75, 0.50, 0.50);

	Plane* leftWall_ptr = new Plane(Point3D(-room_size, 0, 0), Normal(1, 0, 0));
	leftWall_ptr->set_material(matte_ptr4);
	add_object(leftWall_ptr);

	Plane* rightWall_ptr = new Plane(Point3D(room_size, 0, 0), Normal(-1, 0, 0));
	rightWall_ptr->set_material(matte_ptr4);
	add_object(rightWall_ptr);

	double mirror_size 	= 8;
	double offset 		= 1.0;

	Reflective* reflective_ptr2 = new Reflective;
	reflective_ptr2->set_ka(0);
	reflective_ptr2->set_kd(0);
	reflective_ptr2->set_cd(0);
	reflective_ptr2->set_ks(0);
	reflective_ptr2->set_kr(0.85);
	reflective_ptr2->set_cr(1);

	Point3D p0;
	Vector3D a, b;

	p0 = Point3D(-mirror_size, -mirror_size, -(room_size - offset));
	a = Vector3D(2.0 * mirror_size, 0, 0);
	b = Vector3D(0, 2.0 * mirror_size, 0);
	Normal n(0, 0, 1);
	Rectangle* rectangle_ptr1 = new Rectangle(p0, a, b, n);
	rectangle_ptr1->set_material(reflective_ptr2);
	add_object(rectangle_ptr1);

	p0 = Point3D(-mirror_size, -mirror_size, +(room_size - offset));
	n = Normal(0, 0, -1);
	Rectangle* rectangle_ptr2 = new Rectangle(p0, a, b, n);
	rectangle_ptr2->set_material(reflective_ptr2);
	add_object(rectangle_ptr2);

	p0 = Point3D(-(room_size - offset), -mirror_size, +mirror_size);
	a = Point3D(0, 0, -2.0 * mirror_size);
	n = Normal(1, 0, 0);
	Rectangle* rectangle_ptr3 = new Rectangle(p0, a, b, n);
	rectangle_ptr3->set_material(reflective_ptr2);
	add_object(rectangle_ptr3);

	Reflective* reflective_ptr3 = new Reflective;
	reflective_ptr3->set_ka(0);
	reflective_ptr3->set_kd(0);
	reflective_ptr3->set_cd(0);
	reflective_ptr3->set_ks(0);
	reflective_ptr3->set_kr(1);
	reflective_ptr3->set_cr(1, 1, 1);

	Plane* floor_ptr = new Plane(Point3D(0, -room_size,  0), Normal(0, 1, 0));
	floor_ptr->set_material(reflective_ptr3);
	add_object(floor_ptr);
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


/*
void World::display() const
{
    SDL_Surface *image = NULL;
    SDL_Surface *screen = NULL;
    SDL_Event event;
    bool running = true;
    
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init failed\n");
        return;
    }
    
    atexit(SDL_Quit);
    
    screen = SDL_SetVideoMode(vp.hres, vp.vres, 32, SDL_SWSURFACE);
    
    if(screen == NULL) {
        SDL_Quit();
        fprintf(stderr, "SDL_SetVideoMode failed\n");
        return;
    }
    
    SDL_WM_SetCaption("TinyRay", NULL);
    
    image = IMG_Load("/Users/eyefrog/Desktop/image.png");
    
    if (image == NULL) {
        SDL_Quit();
        fprintf(stderr, "IMG_Load failed\n");
        return;
    }
    
    SDL_BlitSurface(image, NULL, screen, NULL);
    
    SDL_Flip( screen );
    
    while (running) {
        if (SDL_WaitEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    
    SDL_FreeSurface(image);

    SDL_Quit();
}
*/

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


