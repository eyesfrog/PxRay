//
// Created by eyesfrog on 16/4/12.
//

#include "../World/World.h"
//#include "../World/World.cpp"

//Tracers
#include "../Tracer/RayCast.h"
#include "../Tracer/Whitted.h"

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
#include "../Camera/Fisheye.h"


void
World::build()
{
	int num_samples = 16;

	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_samples(num_samples);
	vp.set_max_depth(20);

	tracer_ptr = new Whitted(this);

	//Fisheye* fisheye_ptr = new Fisheye;

	Pinhole* pinhole_ptr = new Pinhole;

	pinhole_ptr->set_eye(7.5, 3, 9.5);
	pinhole_ptr->set_lookat(0);
	//pinhole_ptr->set_zoom(1);
	pinhole_ptr->set_view_distance(300.0);
	//pinhole_ptr->set_fov(360);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);

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
	reflective_ptr1->set_cd(0.5,0,0);
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
