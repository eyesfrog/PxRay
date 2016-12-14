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

    Vector(float xx, float yy, float zz)
            : x(xx), y(yy), z(zz) {
        //Assert(!HasNaNs());
    }

    bool HasNaNs() const {
        return isnan(x) || isnan(y) || isnan(z);
    }

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

    Vector operator*(float f) const {
        return Vector(f * x, f * y, f * z);
    }

    Vector &operator*=(float f) {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }

    Vector operator/(float f) const {
        //Assert(f != 0);
        float inv = 1.f / f;
        return Vector(x * inv, y * inv, z * inv);
    }

    Vector &operator/=(float f) {
        //Assert(f != 0);
        float inv = 1.f / f;
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }

    Vector operator-() const {
        return Vector(-x, -y, -z);
    }

    float operator[](int i) const {
        //Assert(i >= 0 && i <= 2);
        return (&x)[i];
    }

    float &operator[](int i) {
        //Assert(i >= 0 && i <= 2);
        return (&x)[i];
    }

    float LengthSquared() const {
        return x * x + y * y + z * z;
    }

    float Length() const {
        return sqrtf(LengthSquared());
    }

    //Vector Public Data
    float x, y, z;
};

class Point {
public:
    // Point Public Methods
    Point() { x = y = z = 0.f; }

    Point(float xx, float yy, float zz)
            : x(xx), y(yy), z(zz) { }

    Point operator+(const Vector &v) const {
        return Point(x + v.x, y + v.y, z + v.z);
    }

    Point &operator+=(const Vector &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector operator-(const Point &p) const {
        return Vector(x - p.x, y - p.y, z - p.z);
    }

    Point operator-(const Vector &v) const {
        return Point(x - v.x, y - v.y, z - v.z);
    }

    Point &operator-=(const Vector &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    // Point Public Data
    float x, y, z;
};

class Normal {
public:
    //Normal Public Methods
    Normal() { x = y = z = 0.f; }

    Normal(float xx, float yy, float zz)
            : x(xx), y(yy), z(zz) {
        //Assert(!HasNaNs());
    }

    Normal operator-() const {
        return Normal(-x, -y, -z);
    }

    Normal operator+(const Normal &n) const {
        return Normal(x + n.x, y + n.y, z + n.z);
    }

    Normal &operator+=(const Normal &n) {
        x += n.x;
        y += n.y;
        z += n.z;
        return *this;
    }

    Normal operator-(const Normal &n) const {
        return Normal(x + n.x, y + n.y, z + n.z);
    }

    Normal operator-=(const Normal &n) {
        x -= n.x;
        y -= n.y;
        z -= n.z;
        return *this;
    }

    Normal operator*(float f) const {
        return Normal(x * f, y * f, z * f);
    }

    Normal &operator*=(float f) {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }

    Normal operator/(float f) const {
        float inv = 1.f / f;
        return Normal(x * inv, y * inv, z * inv);
    }

    Normal operator/=(float f) {
        float inv = 1.f / f;
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }

    explicit Normal(const Vector &v)
            : x(v.x), y(v.y), z(v.z) { }


    float LengthSquared() const { return x * x + y * y + z * z; }

    float Length() const { return sqrtf(LengthSquared()); }

    //Normal Public Data
    float x, y, z;
};

class Ray {
public:
    //Ray Public Methods
    Ray() : mint(0.f), maxt(INFINITY), time(0.f), depth(0) { }

    Ray(const Point &origin, const Vector &direction, float start,
        float end = INFINITY, float t = 0.f, int d = 0)
            : o(origin), d(direction), mint(start), maxt(end), time(t), depth(d) { }

    Ray(const Point &origin, const Vector &direction, const Ray &parent,
        float start, float end = INFINITY)
            : o(origin), d(direction), mint(start), maxt(end),
              time(parent.time), depth(parent.depth + 1) { }

    Point operator()(float t) const {
        return o + d*t;
    }

    //Ray Public Data
    Point o;
    Vector d;
    mutable float mint, maxt;
    float time;
    int depth;
};

inline Vector operator*(float f, const Vector &v) { return v * f; }

inline Vector operator/(float f, const Vector &v) { return v / f; }

inline float Dot(const Vector &v1, const Vector &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline float AbsDot(const Vector &v1, const Vector &v2) {
    return fabsf(Dot(v1, v2));
}

inline Vector Cross(const Vector &v1, const Vector &v2) {
    return Vector((v1.y * v2.z) - (v1.z * v2.y),
                  (v1.z * v2.x) - (v1.x * v2.z),
                  (v1.x * v2.y) - (v1.y * v2.x));
}

inline Vector Normalize(const Vector &v) { return v / v.Length(); }

inline void CoordinateSystem(const Vector &v1, Vector *v2, Vector *v3) {
    if (fabsf(v1.x) > fabsf(v1.y)) {
        float invLen = 1.f / sqrtf(v1.x * v1.x + v1.z * v1.z);
        *v2 = Vector(-v1.z * invLen, 0.f, v1.x * invLen);
    }
    else {
        float invLen = 1.f / sqrtf(v1.y * v1.y + v1.z * v1.z);
        *v2 = Vector(0.f, v1.z * invLen, -v1.y * invLen);
    }

    *v3 = Cross(v1, *v2);
}

inline float Distance(const Point &p1, const Point &p2) {
    return (p1 - p2).Length();
}

inline float DistanceSquared(const Point &p1, const Point &p2) {
    return (p1 - p2).LengthSquared();
}

inline float Dot(const Normal &n1, const Normal &n2) {
    return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
}

inline float Dot(const Normal &n1, const Vector &v2) {
    return n1.x * v2.x + n1.y * v2.y + n1.z * v2.z;
}


inline float Dot(const Vector &v1, const Normal &n2) {
    return v1.x * n2.x + v1.y * n2.y + v1.z * n2.z;
}

inline float AbsDot(const Normal &n1, const Normal &n2) {
    return fabsf(Dot(n1, n2));
}

inline Normal Faceforward(const Normal &n, const Vector &v) {
    return (Dot(n, v) < 0.f) ? -n : n;
}

#endif //PBRT_GEOMETRY_H