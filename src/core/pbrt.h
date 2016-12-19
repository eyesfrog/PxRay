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

#include <string>
#include <vector>

#define PBRT_VERSION "3.0.0"

#ifdef PBRT_FLOAT_AS_DOUBLE
typedef double Float;
#else
typedef float Float;
#endif  // PBRT_FLOAT_AS_DOUBLE

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

#endif //PBRT_PBRT_H
