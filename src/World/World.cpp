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
	vp.set_pixel_size(1);
	vp.set_samples(num_samples);

	tracer_ptr = new RayCast(this);

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 10000);
	pinhole_ptr->set_lookat(0.0);
	pinhole_ptr->set_view_distance(30000);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);

	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(100, 100, 200);
	light_ptr->scale_radiance(3.0);
	light_ptr->set_shadows(true);
	add_light(light_ptr);

	RGBColor yellow(1, 1, 0);                                // yellow
	RGBColor brown(0.71, 0.40, 0.16);                                // brown
	RGBColor dark_green(0.0, 0.41, 0.41);                            // dark_green
	RGBColor orange(1, 0.75, 0);                            // orange
	RGBColor green(0, 0.6, 0.3);                                    // green
	RGBColor light_green(0.65, 1, 0.30);                // light green
	RGBColor dark_yellow(0.61, 0.61, 0);                            // dark yellow
	RGBColor light_purple(0.65, 0.3, 1);                            // light purple
	RGBColor dark_purple(0.5, 0, 1);                                // dark purple


	// Phong materials' reflection coefficients

	float ka = 0.25;
	float kd = 0.75;
	float ks = 0.12;
	float exp = 20;


	// spheres

	Phong* phong_ptr1 = new Phong;
	phong_ptr1->set_ka(ka);
	phong_ptr1->set_kd(kd);
	phong_ptr1->set_ks(ks);
	phong_ptr1->set_exp(exp);
	phong_ptr1->set_cd(yellow);

	Sphere* sphere_ptr1 = new Sphere(Point3D(5, 3, 0), 30);
	sphere_ptr1->set_material(phong_ptr1);                                // yellow
	add_object(sphere_ptr1);

	Phong* phong_ptr2 = new Phong;
	phong_ptr2->set_ka(ka);
	phong_ptr2->set_kd(kd);
	phong_ptr2->set_ks(ks);
	phong_ptr2->set_exp(exp);
	phong_ptr2->set_cd(brown);

	Sphere* sphere_ptr2 = new Sphere(Point3D(45, -7, -60), 20);
	sphere_ptr2->set_material(phong_ptr2);                                // brown
	add_object(sphere_ptr2);

	Phong* phong_ptr3 = new Phong;
	phong_ptr3->set_ka(ka);
	phong_ptr3->set_kd(kd);
	phong_ptr3->set_ks(ks);
	phong_ptr3->set_exp(exp);
	phong_ptr3->set_cd(dark_green);

	Sphere* sphere_ptr3 = new Sphere(Point3D(40, 43, -100), 17);
	sphere_ptr3->set_material(phong_ptr3);                                // dark green
	add_object(sphere_ptr3);

	Phong* phong_ptr4 = new Phong;
	phong_ptr4->set_ka(ka);
	phong_ptr4->set_kd(kd);
	phong_ptr4->set_ks(ks);
	phong_ptr4->set_exp(exp);
	phong_ptr4->set_cd(orange);

	Sphere* sphere_ptr4 = new Sphere(Point3D(-20, 28, -15), 20);
	sphere_ptr4->set_material(phong_ptr4);                                // orange
	add_object(sphere_ptr4);

	Phong* phong_ptr5 = new Phong;
	phong_ptr5->set_ka(ka);
	phong_ptr5->set_kd(kd);
	phong_ptr5->set_ks(ks);
	phong_ptr5->set_exp(exp);
	phong_ptr5->set_cd(green);

	Sphere* sphere_ptr5 = new Sphere(Point3D(-25, -7, -35), 27);
	sphere_ptr5->set_material(phong_ptr5);                                // green
	add_object(sphere_ptr5);

	Phong* phong_ptr6 = new Phong;
	phong_ptr6->set_ka(ka);
	phong_ptr6->set_kd(kd);
	phong_ptr6->set_ks(ks);
	phong_ptr6->set_exp(exp);
	phong_ptr6->set_cd(light_green);

	Sphere* sphere_ptr6 = new Sphere(Point3D(20, -27, -35), 25);
	sphere_ptr6->set_material(phong_ptr6);                                // light green
	add_object(sphere_ptr6);

	Phong* phong_ptr7 = new Phong;
	phong_ptr7->set_ka(ka);
	phong_ptr7->set_kd(kd);
	phong_ptr7->set_ks(ks);
	phong_ptr7->set_exp(exp);
	phong_ptr7->set_cd(green);

	Sphere* sphere_ptr7 = new Sphere(Point3D(35, 18, -35), 22);
	sphere_ptr7->set_material(phong_ptr7);                            // green
	add_object(sphere_ptr7);

	Phong* phong_ptr8 = new Phong;
	phong_ptr8->set_ka(ka);
	phong_ptr8->set_kd(kd);
	phong_ptr8->set_ks(ks);
	phong_ptr8->set_exp(exp);
	phong_ptr8->set_cd(brown);

	Sphere* sphere_ptr8 = new Sphere(Point3D(-57, -17, -50), 15);
	sphere_ptr8->set_material(phong_ptr8);                                // brown
	add_object(sphere_ptr8);

	Phong* phong_ptr9 = new Phong;
	phong_ptr9->set_ka(ka);
	phong_ptr9->set_kd(kd);
	phong_ptr9->set_ks(ks);
	phong_ptr9->set_exp(exp);
	phong_ptr9->set_cd(light_green);

	Sphere* sphere_ptr9 = new Sphere(Point3D(-47, 16, -80), 23);
	sphere_ptr9->set_material(phong_ptr9);                                // light green
	add_object(sphere_ptr9);

	Phong* phong_ptr10 = new Phong;
	phong_ptr10->set_ka(ka);
	phong_ptr10->set_kd(kd);
	phong_ptr10->set_ks(ks);
	phong_ptr10->set_exp(exp);
	phong_ptr10->set_cd(dark_green);

	Sphere* sphere_ptr10 = new Sphere(Point3D(-15, -32, -60), 22);
	sphere_ptr10->set_material(phong_ptr10);                            // dark green
	add_object(sphere_ptr10);

	Phong* phong_ptr11 = new Phong;
	phong_ptr11->set_ka(ka);
	phong_ptr11->set_kd(kd);
	phong_ptr11->set_ks(ks);
	phong_ptr11->set_exp(exp);
	phong_ptr11->set_cd(dark_yellow);

	Sphere* sphere_ptr11 = new Sphere(Point3D(-35, -37, -80), 22);
	sphere_ptr11->set_material(phong_ptr11);                            // dark yellow
	add_object(sphere_ptr11);

	Phong* phong_ptr12 = new Phong;
	phong_ptr12->set_ka(ka);
	phong_ptr12->set_kd(kd);
	phong_ptr12->set_ks(ks);
	phong_ptr12->set_exp(exp);
	phong_ptr12->set_cd(dark_yellow);

	Sphere* sphere_ptr12 = new Sphere(Point3D(10, 43, -80), 22);
	sphere_ptr12->set_material(phong_ptr12);                            // dark yellow
	add_object(sphere_ptr12);

	Phong* phong_ptr13 = new Phong;
	phong_ptr13->set_ka(ka);
	phong_ptr13->set_kd(kd);
	phong_ptr13->set_ks(ks);
	phong_ptr13->set_exp(exp);
	phong_ptr13->set_cd(dark_yellow);

	Sphere* sphere_ptr13 = new Sphere(Point3D(30, -7, -80), 10);
	sphere_ptr13->set_material(phong_ptr13);
	add_object(sphere_ptr13);                                            // dark yellow (hidden)


	Phong* phong_ptr14 = new Phong;
	phong_ptr14->set_ka(ka);
	phong_ptr14->set_kd(kd);
	phong_ptr14->set_ks(ks);
	phong_ptr14->set_exp(exp);
	phong_ptr14->set_cd(dark_green);

	Sphere* sphere_ptr14 = new Sphere(Point3D(-40, 48, -110), 18);
	sphere_ptr14->set_material(phong_ptr14);                            // dark green
	add_object(sphere_ptr14);

	Phong* phong_ptr15 = new Phong;
	phong_ptr15->set_ka(ka);
	phong_ptr15->set_kd(kd);
	phong_ptr15->set_ks(ks);
	phong_ptr15->set_exp(exp);
	phong_ptr15->set_cd(brown);

	Sphere* sphere_ptr15 = new Sphere(Point3D(-10, 53, -120), 18);
	sphere_ptr15->set_material(phong_ptr15);                            // brown
	add_object(sphere_ptr15);

	Phong* phong_ptr16 = new Phong;
	phong_ptr16->set_ka(ka);
	phong_ptr16->set_kd(kd);
	phong_ptr16->set_ks(ks);
	phong_ptr16->set_exp(exp);
	phong_ptr16->set_cd(light_purple);

	Sphere* sphere_ptr16 = new Sphere(Point3D(-55, -52, -100), 10);
	sphere_ptr16->set_material(phong_ptr16);                            // light purple
	add_object(sphere_ptr16);

	Phong* phong_ptr17 = new Phong;
	phong_ptr17->set_ka(ka);
	phong_ptr17->set_kd(kd);
	phong_ptr17->set_ks(ks);
	phong_ptr17->set_exp(exp);
	phong_ptr17->set_cd(brown);

	Sphere* sphere_ptr17 = new Sphere(Point3D(5, -52, -100), 15);
	sphere_ptr17->set_material(phong_ptr17);                            // browm
	add_object(sphere_ptr17);

	Phong* phong_ptr18 = new Phong;
	phong_ptr18->set_ka(ka);
	phong_ptr18->set_kd(kd);
	phong_ptr18->set_ks(ks);
	phong_ptr18->set_exp(exp);
	phong_ptr18->set_cd(dark_purple);

	Sphere* sphere_ptr18 = new Sphere(Point3D(-20, -57, -120), 15);
	sphere_ptr18->set_material(phong_ptr18);                            // dark purple
	add_object(sphere_ptr18);

	Phong* phong_ptr19 = new Phong;
	phong_ptr19->set_ka(ka);
	phong_ptr19->set_kd(kd);
	phong_ptr19->set_ks(ks);
	phong_ptr19->set_exp(exp);
	phong_ptr19->set_cd(dark_green);

	Sphere* sphere_ptr19 = new Sphere(Point3D(55, -27, -100), 17);
	sphere_ptr19->set_material(phong_ptr19);                            // dark green
	add_object(sphere_ptr19);

	Phong* phong_ptr20 = new Phong;
	phong_ptr20->set_ka(ka);
	phong_ptr20->set_kd(kd);
	phong_ptr20->set_ks(ks);
	phong_ptr20->set_exp(exp);
	phong_ptr20->set_cd(brown);

	Sphere* sphere_ptr20 = new Sphere(Point3D(50, -47, -120), 15);
	sphere_ptr20->set_material(phong_ptr20);                            // browm
	add_object(sphere_ptr20);

	Phong* phong_ptr21 = new Phong;
	phong_ptr21->set_ka(ka);
	phong_ptr21->set_kd(kd);
	phong_ptr21->set_ks(ks);
	phong_ptr21->set_exp(exp);
	phong_ptr21->set_cd(light_purple);

	Sphere* sphere_ptr21 = new Sphere(Point3D(70, -42, -150), 10);
	sphere_ptr21->set_material(phong_ptr21);                            // light purple
	add_object(sphere_ptr21);

	Phong* phong_ptr22 = new Phong;
	phong_ptr22->set_ka(ka);
	phong_ptr22->set_kd(kd);
	phong_ptr22->set_ks(ks);
	phong_ptr22->set_exp(exp);
	phong_ptr22->set_cd(light_purple);

	Sphere* sphere_ptr22 = new Sphere(Point3D(5, 73, -130), 12);
	sphere_ptr22->set_material(phong_ptr22);                            // light purple
	add_object(sphere_ptr22);

	Phong* phong_ptr23 = new Phong;
	phong_ptr23->set_ka(ka);
	phong_ptr23->set_kd(kd);
	phong_ptr23->set_ks(ks);
	phong_ptr23->set_exp(exp);
	phong_ptr23->set_cd(dark_purple);

	Sphere* sphere_ptr23 = new Sphere(Point3D(66, 21, -130), 13);
	sphere_ptr23->set_material(phong_ptr23);                            // dark purple
	add_object(sphere_ptr23);

	Phong* phong_ptr24 = new Phong;
	phong_ptr24->set_ka(ka);
	phong_ptr24->set_kd(kd);
	phong_ptr24->set_ks(ks);
	phong_ptr24->set_exp(exp);
	phong_ptr24->set_cd(light_purple);

	Sphere* sphere_ptr24 = new Sphere(Point3D(72, -12, -140), 12);
	sphere_ptr24->set_material(phong_ptr24);                            // light purple
	add_object(sphere_ptr24);

	Phong* phong_ptr25 = new Phong;
	phong_ptr25->set_ka(ka);
	phong_ptr25->set_kd(kd);
	phong_ptr25->set_ks(ks);
	phong_ptr25->set_exp(exp);
	phong_ptr25->set_cd(green);

	Sphere* sphere_ptr25 = new Sphere(Point3D(64, 5, -160), 11);
	sphere_ptr25->set_material(phong_ptr25);                            // green
	add_object(sphere_ptr25);

	Phong* phong_ptr26 = new Phong;
	phong_ptr26->set_ka(ka);
	phong_ptr26->set_kd(kd);
	phong_ptr26->set_ks(ks);
	phong_ptr26->set_exp(exp);
	phong_ptr26->set_cd(light_purple);

	Sphere* sphere_ptr26 = new Sphere(Point3D(55, 38, -160), 12);
	sphere_ptr26->set_material(phong_ptr26);                            // light purple
	add_object(sphere_ptr26);

	Phong* phong_ptr27 = new Phong;
	phong_ptr27->set_ka(ka);
	phong_ptr27->set_kd(kd);
	phong_ptr27->set_ks(ks);
	phong_ptr27->set_exp(exp);
	phong_ptr27->set_cd(light_purple);

	Sphere* sphere_ptr27 = new Sphere(Point3D(-73, -2, -160), 12);
	sphere_ptr27->set_material(phong_ptr27);                            // light purple
	add_object(sphere_ptr27);

	Phong* phong_ptr28 = new Phong;
	phong_ptr28->set_ka(ka);
	phong_ptr28->set_kd(kd);
	phong_ptr28->set_ks(ks);
	phong_ptr28->set_exp(exp);
	phong_ptr28->set_cd(dark_purple);

	Sphere* sphere_ptr28 = new Sphere(Point3D(30, -62, -140), 15);
	sphere_ptr28->set_material(phong_ptr28);                            // dark purple
	add_object(sphere_ptr28);

	Phong* phong_ptr29 = new Phong;
	phong_ptr29->set_ka(ka);
	phong_ptr29->set_kd(kd);
	phong_ptr29->set_ks(ks);
	phong_ptr29->set_exp(exp);
	phong_ptr29->set_cd(dark_purple);

	Sphere* sphere_ptr29 = new Sphere(Point3D(25, 63, -140), 15);
	sphere_ptr29->set_material(phong_ptr29);                            // dark purple
	add_object(sphere_ptr29);

	Phong* phong_ptr30 = new Phong;
	phong_ptr30->set_ka(ka);
	phong_ptr30->set_kd(kd);
	phong_ptr30->set_ks(ks);
	phong_ptr30->set_exp(exp);
	phong_ptr30->set_cd(dark_purple);

	Sphere* sphere_ptr30 = new Sphere(Point3D(-60, 46, -140), 15);
	sphere_ptr30->set_material(phong_ptr30);                            // dark purple
	add_object(sphere_ptr30);

	Phong* phong_ptr31 = new Phong;
	phong_ptr31->set_ka(ka);
	phong_ptr31->set_kd(kd);
	phong_ptr31->set_ks(ks);
	phong_ptr31->set_exp(exp);
	phong_ptr31->set_cd(light_purple);

	Sphere* sphere_ptr31 = new Sphere(Point3D(-30, 68, -130), 12);
	sphere_ptr31->set_material(phong_ptr31);                            // light purple
	add_object(sphere_ptr31);

	Phong* phong_ptr32 = new Phong;
	phong_ptr32->set_ka(ka);
	phong_ptr32->set_kd(kd);
	phong_ptr32->set_ks(ks);
	phong_ptr32->set_exp(exp);
	phong_ptr32->set_cd(green);

	Sphere* sphere_ptr32 = new Sphere(Point3D(58, 56, -180), 11);
	sphere_ptr32->set_material(phong_ptr32);                            //  green
	add_object(sphere_ptr32);

	Phong* phong_ptr33 = new Phong;
	phong_ptr33->set_ka(ka);
	phong_ptr33->set_kd(kd);
	phong_ptr33->set_ks(ks);
	phong_ptr33->set_exp(exp);
	phong_ptr33->set_cd(green);

	Sphere* sphere_ptr33 = new Sphere(Point3D(-63, -39, -180), 11);
	sphere_ptr33->set_material(phong_ptr33);                            // green
	add_object(sphere_ptr33);

	Phong* phong_ptr34 = new Phong;
	phong_ptr34->set_ka(ka);
	phong_ptr34->set_kd(kd);
	phong_ptr34->set_ks(ks);
	phong_ptr34->set_exp(exp);
	phong_ptr34->set_cd(light_purple);

	Sphere* sphere_ptr34 = new Sphere(Point3D(46, 68, -200), 10);
	sphere_ptr34->set_material(phong_ptr34);                            // light purple
	add_object(sphere_ptr34);

	Phong* phong_ptr35 = new Phong;
	phong_ptr35->set_ka(ka);
	phong_ptr35->set_kd(kd);
	phong_ptr35->set_ks(ks);
	phong_ptr35->set_exp(exp);
	phong_ptr35->set_cd(light_purple);

	Sphere* sphere_ptr35 = new Sphere(Point3D(-3, -72, -130), 12);
	sphere_ptr35->set_material(phong_ptr35);                            // light purple
	add_object(sphere_ptr35);
	/*
	int num_samples = 16;

	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_samples(num_samples);
	vp.set_max_depth(20);

	tracer_ptr = new Whitted(this);

	Pinhole* pinhole_ptr = new Pinhole;

	pinhole_ptr->set_eye(7.5, 3, 9.5);
	pinhole_ptr->set_lookat(0);
	pinhole_ptr->set_view_distance(300);
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
	 */
}

/*
void
World::build(void) {
	vp.set_hres(1000);
	vp.set_vres(1000);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);

	back_ground_color = black;
	tracer_ptr = new SingleSphere(this);

	sphere.set_center(0.0);
	sphere.set_radius(400.0);
}
*/

/*  normal build (without Camera)
void World::build(void)
{
	vp.set_hres(400);
	vp.set_vres(400);
    vp.set_samples(100);
    eye = 200;
    d = 100;

	back_ground_color = black;
	tracer_ptr = new MultipleObjects(this);

	Sphere* sphere_ptr1 = new Sphere;
	sphere_ptr1->set_center(0, -25, 0);
	sphere_ptr1->set_radius(80);
	sphere_ptr1->set_color(1, 0, 0);
	add_object(sphere_ptr1);

    Sphere* sphere_ptr2 = new Sphere;
    sphere_ptr2->set_center(0, 30, 0);
    sphere_ptr2->set_radius(60);
	sphere_ptr2->set_color(1, 1, 0);
	add_object(sphere_ptr2);
    
	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 1));
	plane_ptr->set_color(0.0, 0.25, 0.0);
	add_object(plane_ptr);
}
*/

/*void
World::render_perspective(void) const
{
    RGBColor pixel_color;
    Ray ray;
    
    ray.o = Point3D(0.0, 0.0, eye);
    
    FILE *f = fopen("image.ppm", "w");
    fprintf(f, "P3\n%d %d\n%d\n", vp.hres, vp.vres, 255);
    
    for (int r = vp.vres-1; r >= 0; --r) {
        for (int c = 0; c < vp.vres; ++c) {
            ray.d = Vector3D(vp.s * (c - 0.5*(vp.hres -1.0)),
                             vp.s * (r - 0.5 * (vp.vres - 1.0)), -d);
            ray.d.normalize();
            pixel_color = tracer_ptr->trace_ray(ray);
            fprintf(f, "%d %d %d \n", int(pixel_color.r * 255), int(pixel_color.g * 255), int(pixel_color.b * 255)); 
        }
    }
    fclose(f);
}
*/

/*
void
World::render_scene(void) const
{
	RGBColor pixel_color;
	Ray ray;
	double zw = 100.0;
    Point2D pp;
    Point2D sp;
	
    ray.d = Vector3D(0, 0, -1);

	FILE *f = fopen("image.ppm", "w");
	fprintf(f, "P3\n%d %d\n%d\n", vp.hres, vp.vres, 255);
    
    for (int r = vp.vres-1; r >= 0; --r) {
        for (int c = 0; c < vp.hres; ++c) {
            pixel_color = black;
            for (int j = 0; j < vp.num_samples; ++j) {
                sp = vp.sampler_ptr->sample_unit_square();
                pp.x = vp.s * (c - 0.5 * vp.hres + sp.x);
                pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);
                ray.o = Point3D(pp.x, pp.y, zw);
                pixel_color += tracer_ptr->trace_ray(ray);
            }
            pixel_color /= vp.num_samples;
            fprintf(f, "%d %d %d \n", int(pixel_color.r * 255), int(pixel_color.g * 255), int(pixel_color.b * 255));
        }
    }
    fclose(f);
}
*/

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


// old version of render
/*for (int r = vp.vres-1; r >= 0; --r) {
    for (int c = 0; c < vp.hres; ++c) {
        for (int p = 0; p < n; ++p) {
            for (int q = 0; q < n; ++q) {

                // Regular Sampling
                // pp.x = vp.s * (c - 0.5 * vp.hres + (q + 0.5) / n);
                // pp.y = vp.s * (r - 0.5 * vp.vres + (p + 0.5) / n);

                // Random Sampling
                // pp.x = vp.s * (c - 0.5 * vp.hres + rand_float());
                // pp.y = vp.s * (r - 0.5 * vp.vres + rand_float());

                // Jittered Sampling
                pp.x = vp.s * (c - 0.5 * vp.hres + (q + rand_float()) / n);
                pp.y = vp.s * (r - 0.5 * vp.vres + (p + rand_float()) / n);
                ray.o = Point3D(pp.x, pp.y, zw);
                pixel_color += tracer_ptr->trace_ray(ray);
            }
        }
        pixel_color /= vp.num_samples;
        fprintf(f, "%d %d %d \n", int(pixel_color.r * 255), int(pixel_color.g * 255), int(pixel_color.b * 255));
    }
}
 */

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


