//
//  Camera.h
//  TinyRay
//
//  Created by eyesfrog on 15/7/21.
//  Copyright (c) 2015年 eyesfrog. All rights reserved.
//

#ifndef __TinyRay__Camera__
#define __TinyRay__Camera__

#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"

class World;

class Camera {

public:
	Camera(void);

	Camera(const Camera& camera);

	virtual Camera*
			clone(void) const = 0;

	virtual ~Camera();

	Camera&
			operator=(const Camera& rhs);

	void set_eye(const Point3D& p);

	void set_eye(const float x, const float y, const float z);

	void set_lookat(const Point3D& p);

	void set_lookat(const float x, const float y, const float z);

	void set_up_vector(const Vector3D& v);

	void set_up_vector(const float x, const float y, const float z);

	void set_roll(const float ra);

	void set_exposure_time(const float e_time);

	void compute_uvw(void);

	virtual void
			render_scene(const World& w) = 0;

protected:

	Point3D eye;
	Point3D look_at;
	Vector3D up;
	Vector3D u, v, w;
	float exposure_time;
	float ra;
};

inline void
Camera::set_eye(const Point3D& p)
{
	eye.x = p.x;
	eye.y = p.y;
	eye.z = p.z;
}

inline void
Camera::set_eye(const float _x, const float _y, const float _z)
{
	eye.x = _x;
	eye.y = _y;
	eye.z = _z;
}

inline void
Camera::set_lookat(const Point3D& p)
{
	look_at.x = p.x;
	look_at.y = p.y;
	look_at.z = p.z;
}

inline void
Camera::set_lookat(const float _x, const float _y, const float _z)
{
	look_at.x = _x;
	look_at.y = _y;
	look_at.z = _z;
}

inline void
Camera::set_up_vector(const Vector3D& v)
{
	up = v;
}

inline void
Camera::set_up_vector(const float _x, const float _y, const float _z)
{
	up.x = _x;
	up.y = _y;
	up.z = _z;
}

inline void
Camera::set_roll(const float _ra)
{
	ra = _ra;
}

inline void
Camera::set_exposure_time(const float e_time)
{
	exposure_time = e_time;
}

#endif /* defined(__TinyRay__Camera__) */
