//
// Created by eyesfrog on 2016-12-23.
//

#ifndef PBRT_SHAPE_H
#define PBRT_SHAPE_H

#include "transform.h"
#include "interaction.h"

class Shape {
public:
    //Shape Interface
    Shape(const Transform* ObjectToWorld, const Transform* WorldToObject, bool reverseOrientation);

    virtual ~Shape();

    virtual Bounds3f ObjectBound() const = 0;

    virtual Bounds3f WorldBound() const;

    virtual bool
    Intersect(const Ray& ray, Float* tHit, SurfaceInteraction* isect, bool testAlphaTexture = true) const = 0;

    virtual bool
    Intersect(const Ray& ray, bool testAlphaTexture = true) const
    {
        Float tHit = ray.tMax;
        SurfaceInteraction isect;
        return Intersect(ray, &tHit, &isect, testAlphaTexture);
    }
    virtual Float Area() const = 0;
    virtual Interaction Sample(const Point2f &u) const = 0;
    virtual Float Pdf(const Interaction &) const { return 1/Area(); }
    virtual Interaction Sample(const Interaction &ref, const Point2f &u) const {
        return Sample(u);
    }
    virtual Float Pdf(const Interaction& ref, const Vector3f& wi) const;

    //Shape Public Data
    const Transform* ObjectToWorld, * WorldToObject;
    const bool reverseOrientation;
    const bool transformSwapsHandedness;
};

#endif //PBRT_SHAPE_H
