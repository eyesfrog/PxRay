//
//  Camera.cpp
//  TinyRay
//
//  Created by eyefrog on 15/7/21.
//  Copyright (c) 2015年 eyefrog. All rights reserved.
//

#include "Camera.h"

Camera::Camera(void)
		:
		eye(0, 0, 500),
		lookat(0),
		up(0, 1, 0),
		u(1, 0, 0),
		v(0, 1, 0),
		w(0, 0, 1),
		exposure_time(1.0) { }

Camera::Camera(const Camera& camera)
		:
		eye(camera.eye),
		lookat(camera.lookat),
		up(camera.lookat),
		u(camera.u),
		v(camera.v),
		w(camera.w),
		exposure_time(camera.exposure_time) { }

Camera::~Camera() { }

Camera&
Camera::operator=(const Camera& rhs)
{
	if (this==&rhs)
		return *this;

	eye = rhs.eye;
	lookat = rhs.lookat;
	ra = rhs.ra;
	up = rhs.up;
	u = rhs.u;
	v = rhs.v;
	w = rhs.w;
	exposure_time = rhs.exposure_time;

	return *this;
}

void
Camera::compute_uvw(void)
{
	w = eye-lookat;
	w.normalize();
	u = up ^ w;
	u.normalize();
	v = w ^ u;

	if (eye.x==lookat.x && eye.z==lookat.z && eye.y>lookat.y) {
		u = Vector3D(0, 0, 1);
		v = Vector3D(1, 0, 0);
		w = Vector3D(0, 1, 0);
	}

	if (eye.x==lookat.x && eye.z==lookat.z && eye.y<lookat.y) {
		u = Vector3D(1, 0, 0);
		v = Vector3D(0, 0, 1);
		w = Vector3D(0, -1, 0);
	}
}