//
//  Fisheye.hpp
//  TinyRay
//
//  Created by eyefrog on 15/11/15.
//  Copyright © 2015年 eyefrog. All rights reserved.
//

#ifndef Fisheye_h
#define Fisheye_h

#include "Camera.h"
#include "../Utilities/Point2D.h"
#include "../World/World.h"

class Fisheye : public Camera {

public:
    Fisheye(void);

    Fisheye(const Fisheye& fe);

    virtual ~Fisheye();

    virtual Camera* clone(void) const;

    Fisheye& operator=(const Fisheye& rhs);

    void set_fov(const int fov);

    Vector3D ray_direction(const Point2D& p, const int hres,
            const int vres, const float s, float& r_squared) const;

    virtual void render_scene(const World& w);

private:
    float psi_max;
};

inline void Fisheye::set_fov(const int fov)
{
    psi_max = fov / 2;
}

#endif /* Fisheye_h */
