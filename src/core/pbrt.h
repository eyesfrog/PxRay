//
// Created by eyesfrog on 16/5/31.
//

#pragma once

#ifndef PBRT_PBRT_H
#define PBRT_PBRT_H

#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#define PBRT_VERSION "3.0.0"

// Global Forward Declarations
class Scene;
class Integrator;
class SamplerIntegrator;
template <typename T>
class Vector2;
template <typename T>
class Vector3;
template <typename T>
class Point3;
template <typename T>
class Point2;
template <typename T>
class Normal3;
class Ray;
class RayDifferential;
template <typename T>
class Bounds2;
template <typename T>
class Bounds3;
class Transform;
struct Interaction;
class SurfaceInteraction;
class Shape;
class Primitive;
class GeometricPrimitive;
template <int nSpectrumSamples>
class CoefficientSpectrum;
class RGBSpectrum;
class SampledSpectrum;
typedef RGBSpectrum Spectrum;
// typedef SampledSpectrum Spectrum;
class Camera;
struct CameraSample;
class ProjectiveCamera;
class Sampler;
class Filter;
class Film;
class FilmTile;
class BxDF;
class BRDF;
class BTDF;
class BSDF;
class Material;
template <typename T>
class Texture;
class Medium;
class MediumInteraction;
struct MediumInterface;
class BSSRDF;
class SeparableBSSRDF;
class TabulatedBSSRDF;
struct BSSRDFTable;
class Light;
class VisibilityTester;
class AreaLight;
struct Distribution1D;
class Distribution2D;

#ifdef PBRT_FLOAT_AS_DOUBLE
typedef double Float;
#else
typedef float Float;
#endif  // PBRT_FLOAT_AS_DOUBLE

class RNG;
class ProgressReporter;
class MemoryArena;
template <typename T, int logBlockSize = 2>
class BlockedArray;
struct Matrix4x4;
class ParamSet;
template <typename T>
struct ParamSetItem;
struct Options {
    int nThreads = 0;
    bool quickRender = false;
    bool quiet = false;
    bool cat = false, toPly = false;
    std::string imageFile;
};

extern Options PbrtOptions;
class TextureParams;


// Global Constants
static constexpr Float MaxFloat = std::numeric_limits<Float>::max();
static constexpr Float Infinity = std::numeric_limits<Float>::infinity();
static constexpr Float MachineEpsilon = std::numeric_limits<Float>::epsilon() * 0.5;
static constexpr Float ShadowEpsilon = 0.0001f;
static constexpr Float Pi = 3.14159265358979323846;
static constexpr Float InvPi = 0.31830988618379067154;
static constexpr Float Inv2Pi = 0.15915494309189533577;
static constexpr Float Inv4Pi = 0.07957747154594766788;
static constexpr Float PiOver2 = 1.57079632679489661923;
static constexpr Float PiOver4 = 0.78539816339744830961;
static constexpr Float Sqrt2 = 1.41421356237309504880;


template <typename T>
class Vector2;

template <typename T>
class Vector3;

template <typename T>
class Point3;

template <typename T>
class Point2;

template <typename T>
class Normal3;

class Medium;

//Global inline functions

inline Float Lerp(Float t, Float v1, Float v2)
{
    return (1 - t) * v1 + t * v2;
}

inline Float Radians(Float deg) { return (Pi / 180) * deg; }


#endif //PBRT_PBRT_H
