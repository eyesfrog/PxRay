//
// Created by eyesfrog on 2016-12-23.
//

#ifndef PBRT_SPHERE_H
#define PBRT_SPHERE_H

#include "../core/shape.h"

class Sphere : public Shape {
public:
    //Sphere Public Methods
    Sphere(const Transform* ObjectToWorld, const Transform* WorldToObject, bool reverseOrientation, Float radius,
           Float zMin, Float zMax, Float phiMax)
            : Shape(ObjectToWorld, WorldToObject, reverseOrientation), radius(radius),
              zMin(Clamp(std::min(zMin, zMax), -radius, radius)), zMax(Clamp(std::max(zMin, zMax), -radius, radius)),
              thetaMin(std::acos(Clamp(zMin / radius, -1, 1))), thetaMax(std::acos(Clamp(zMax / radius, -1, 1))),
              phiMax(Radians(Clamp(phiMax, 0, 360))) { }

    Bounds3f ObjectBound() const;

    bool Intersect(const Ray& r, Float* tHit, SurfaceInteraction* isect, bool testAlphaTexture) const;

private:
    //Sphere Private Data
    const Float radius;
    const Float zMin, zMax;
    const Float thetaMin, thetaMax, phiMax;
};

#endif //PBRT_SPHERE_H
