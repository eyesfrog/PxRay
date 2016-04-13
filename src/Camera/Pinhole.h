//
//  Pinhole.h
//  TinyRay
//
//  Created by eyesfrog on 15/7/21.
//  Copyright (c) 2015年 eyesfrog. All rights reserved.
//

#ifndef __TinyRay__Pinhole__
#define __TinyRay__Pinhole__

#include "Camera.h"
#include "../Utilities/Point2D.h"
#include "../World/World.h"

class Pinhole : public Camera {

public:

	Pinhole(void);

	Pinhole(const Pinhole& ph);

	virtual ~Pinhole();

	virtual Camera* clone(void) const;

	Pinhole&
			operator=(const Pinhole& rhs);

	void set_view_distance(const float _d);

	void set_zoom(const float zoom_factor);

	Vector3D get_direction(const Point2D& p) const;

	virtual void
			render_scene(const World& w);

private:

	float d;
	float zoom;

};

inline void
Pinhole::set_view_distance(const float _d)
{
	d = _d;
}

inline void
Pinhole::set_zoom(const float zoom_factor)
{
	zoom = zoom_factor;
}

#endif /* defined(__TinyRay__Pinhole__) */
