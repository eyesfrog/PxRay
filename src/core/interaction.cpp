//
// Created by eyesfrog on 2016-12-21.
//

#include "interaction.h"

SurfaceInteraction::SurfaceInteraction(const Point3f& p, const Vector3f& pError, const Point2f& uv, const Vector3f& wo,
                                       const Vector3f& dpdu, const Vector3f& dpdv, const Normal3f& dndu,
                                       const Normal3f& dndv, Float time, const Shape* shape)
        : Interaction(p, Normal3f(Normalize(Cross(dpdu, dpdv))), pError, wo, time, nullptr), uv(uv), dpdu(dpdu),
          dndu(dndu), dndv(dndv), shape(shape)
{
    //Initialize shading geometry from true geometry
    shading.n = n;
    shading.dpdu = dpdu;
    shading.dpdv = dpdv;
    shading.dndu = dndu;
    shading.dndv = dndv;
    //Adjust normal based on orientation and handedness
    if (shape && (shape->reverseOrientation ^ shape->transformSwapsHandedness)) {
        n *= -1;
        shading.n *= -1;
    }
}

void SurfaceInteraction::SetShadingGeometry(const Vector3f& dpdus, const Vector3f& dpdvs, const Normal3f& dndus,
                                            const Normal3f& dndvs, bool orientaionaIsAuthoritative)
{
    //Compute shading.n for SurfaceInteraction
    shading.n = Normalize((Normal3f)Cross(dpdus, dpdvs));
    if (shape && (shape->reverseOrientation ^ shape->transformSwapsHandedness))
        shading.n = -shading.n;
    if (orientaionaIsAuthoritative)
        n = Faceforward(n, shading.n);
    else
        shading.n = Faceforward(shading.n, n);
    //Initialize shading partial derivative values
    shading.dpdu = dpdus;
    shading.dpdv = dpdvs;
    shading.dndu = dndus;
    shading.dndv = dndvs;
}
