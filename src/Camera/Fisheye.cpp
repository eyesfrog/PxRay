//
//  Fisheye.cpp
//  TinyRay
//
//  Created by eyefrog on 15/11/15.
//  Copyright © 2015年 eyefrog. All rights reserved.
//

#include "Fisheye.h"

Fisheye::Fisheye(void)
        : Camera(),
          psi_max(90) { }

Fisheye::Fisheye(const Fisheye& fe)
        : Camera(fe),
          psi_max(fe.psi_max) { }

Camera*
Fisheye::clone(void) const
{
    return (new Fisheye(*this));
}

Fisheye&
Fisheye::operator=(const Fisheye& rhs)
{
    if (this == &rhs) {
        return *this;
    }

    Camera::operator=(rhs);

    psi_max = rhs.psi_max;

    return *this;
}

Fisheye::~Fisheye() { }

Vector3D
Fisheye::ray_direction(const Point2D& p, const int hres,
        const int vres, const float s, float& r_squared) const
{
    Point2D pn(2.0 / (s * hres) * p.x, 2.0 / (s * vres) * p.y);
    r_squared = pn.x * pn.x + pn.y * pn.y;

    if (r_squared < 1.0) {
        float r = sqrt(r_squared);
        float psi = r * psi_max * PI_ON_180;
        float sin_psi = sin(psi);
        float cos_psi = cos(psi);
        float sin_alpha = pn.y / r;
        float cos_alpha = pn.x / r;

        Vector3D dir = sin_psi * cos_alpha * u + sin_psi
                * sin_alpha * v - cos_psi * w;

        return dir;
    }
    else
        return (Vector3D(0.0));
}

void
Fisheye::render_scene(const World& w)
{
    RGBColor L;
    ViewPlane vp(w.vp);
    Ray ray;
    int depth = 10;
    Point2D sp, pp;
    float r_squared;

    ray.o = eye;

    FILE* f = fopen("/Users/eyefrog/Desktop/image.bmp", "w");
    fprintf(f, "P3\n%d %d\n%d\n", vp.hres, vp.vres, 255);

    for (int r = vp.vres - 1; r >= 0; --r) {
        for (int c = 0; c < vp.vres; ++c) {
            L = black;
            for (int j = 0; j < vp.num_samples; ++j) {
                sp = w.vp.sampler_ptr->sample_unit_square();
                pp.x = vp.s * (c - 0.5 * vp.hres + sp.x);
                pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);
                ray.d = ray_direction(pp, vp.hres, vp.vres, vp.s, r_squared);
                if (r_squared <= 1.0)
                    L += w.tracer_ptr->trace_ray(ray, depth);
            }
            L /= vp.num_samples;
            L *= exposure_time;
            //L = w.clamp_to_color(L);
            L = w.max_to_one(L);
            fprintf(f, "%d %d %d \n", int(L.r * 255), int(L.g * 255), int(L.b * 255));
        }
    }
    fclose(f);

}
