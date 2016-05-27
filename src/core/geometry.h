//
// Created by eyesfrog on 16/5/13.
//

#ifndef PBRT_GEOMETRY_H
#define PBRT_GEOMETRY_H

#include <cmath>

class Vector {
public:
    //Vector Public Method
    Vector() { x = y = z = 0.f; }

    Vector()(float xx, float yy, float zz)
            : x(xx), y(yy), z(zz) {
        Assert(!HasNaNs());
    }

    bool HasNaNs() const { return isnan(x) || isnan(y) || isnan(z); }

    Vector operator+(const Vector &v) const {
        return Vector(x + v.x, y + v.y, z + v.z);
    }

    Vector &operator+=(const Vector &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector operator-(const Vector &v) const {
        return Vector(x - v.x, y - v.y, z - v.z);
    }

    Vector &operator-=(const Vector &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector operator*(float f) const { return Vector(f * x, f * y, f * z); }

    Vector &operator*=(float f) {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }

    Vector operator/(float f) const {
        Assert(f != 0);
        float inv = 1.f/f;
        return Vector(x * inv, y * inv, z * inv);
    }

    Vector &operator/=(float f) {
        Assert(f != 0);
        float inv = 1.f/f;
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }

    Vector operator-() const { return Vector(-x, -y, -z); }

    float operator[](int i) const {
        Assert(i >= 0 && i <= 2);
        return (&x)[i];
    }

    float &operator[](int i) {
        Assert(i >= 0 && i <= 2);
        return (&x)[i];
    }
    //Vector Public Data
    float x, y, z;
};

inline Vector operator*(float f, const Vector &v) { return v * f; }

inline Vector operator/(float f, const Vector &v) { return v / f; }

#endif //PBRT_GEOMETRY_H
