//
// Created by eyesfrog on 2016-12-21.
//

#ifndef PBRT_INTERACTION_H
#define PBRT_INTERACTION_H

#include "pbrt.h"
#include "geometry.h"
#include "transform.h"

struct Interaction {
    //Interaction Public Methods
    Interaction() : time(0) { }

    Interaction(const Point3f& p, const Normal3f& n, const Vector3f& pError,
                const Vector3f& wo, Float time, const MediumInterface& mediumInterface)
            : p(p), time(time), pError(pError), wo(wo), n(n), mediumInterface(mediumInterface) { }

    bool IsSurfaceInteraction() const
    {
        return n != Normal3f();
    }

    //Interaction Public Data
    Point3f p;
    Float time;
    Vector3f pError;
    Vector3f wo;
    Normal3f n;
    MediumInterface mediumInterface;
};

class SurfaceInteraction : public Interaction {
public:
    //SurfaceInteraction Public Methods
    SurfaceInteraction() { }

    SurfaceInteraction(const Point3f& p, const Vector3f& pError,
                       const Point2f& uv, const Vector3f& wo,
                       const Vector3f& dpdu, const Vector3f& dpdv,
                       const Normal3f& dndu, const Normal3f& dndv, Float time,
                       const Shape* sh);

    void SetShadingGeometry(const Vector3f& dpdus, const Vector3f& dpdvs, const Normal3f& dndus, const Normal3f& dndvs,
                           bool orientaionaIsAuthoritative);

    //SurfaceInteraction Public Data
    Point2f uv;
    Vector3f dpdu, dpdv;
    Normal3f dndu, dndv;
    const Shape* shape = nullptr;
    struct {
        Normal3f n;
        Vector3f dpdu, dpdv;
        Normal3f dndu, dndv;
    } shading;
};

#endif //PBRT_INTERACTION_H
