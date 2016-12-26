//
// Created by eyesfrog on 2016-12-23.
//

#include "sphere.h"
#include "../core/efloat.h"

Bounds3f Sphere::ObjectBound() const
{
    return Bounds3f(Point3f(-radius, -radius, zMin),
                    Point3f(radius, radius, zMax));
}

bool Sphere::Intersect(const Ray& r, Float* tHit, SurfaceInteraction* isect, bool testAlphaTexture) const
{
    Float phi;
    Point3f pHit;
    //Transform Ray to object space
    Vector3f oErr, dErr;
    Ray ray = (*WorldToObject)(r, &oErr, &dErr);
    //Compute quadratic sphere coefficients
    EFloat ox(ray.o.x, oErr.x), oy(ray.o.y, oErr.y), oz(ray.o.z, oErr.z);
    EFloat dx(ray.d.x, dErr.x), dy(ray.d.y, dErr.y), dz(ray.d.z, dErr.z);
    EFloat a = dx * dx dy * dy + dz * dz;
    EFloat b = 2 * (dx * ox + dy * oy + dz * oz);
    EFloat c = ox * ox + oy * oy + oz * oz - EFloat(radius) * EFloat(radius);
    //Solve quadratic equation for t values
    EFloat t0, t1;
    if (!Quadratic(a, b, c, &t0, &t1))
        return false;
    //Check quadric shape t0 and t1 for nearest intersection
    if (t0.UpperBound() > ray.tMax || t1.LowerBound() <= 0)
        return false;
    EFloat tShapeHit = t0;
    if (tShapeHit.LowerBound() <= 0){
        tShapeHit = t1;
        if (tShapeHit.UpperBound() > ray.tMax)
            return false;
    }
    //Compute sphere hit position and phi
    //Test sphere intersection against clipping parameters
    //Find parametric representation of sphere hit
    //Compute error bounds for sphere intersection
    //Initialize SurfaceInteraction from parametric information
    //Update tHit for quadratic intersection
    return true;
}
