//
// Created by eyefrog on 15/7/15.
//

#ifndef TINYRAY_VECTOR3D_H
#define TINYRAY_VECTOR3D_H

#include <sys/dtrace.h>
#include "Matrix.h"

class Normal;

class Point3D;

class Vector3D {
public:
	double x, y, z;
public:
	Vector3D(void);

	Vector3D(double a);

	Vector3D(double _x, double _y, double _z);

	Vector3D(const Vector3D& v);

	Vector3D(const Normal& n);

	Vector3D(const Point3D& p);

	~Vector3D();

	Vector3D& operator=(const Vector3D& rhs);

	Vector3D& operator=(const Normal& rhs);

	Vector3D& operator=(const Point3D& rhs);

	Vector3D operator-(void) const;

	double length(void);

	double len_squared(void);

	Vector3D operator*(const double a) const;

	Vector3D operator/(const double a) const;

	Vector3D operator+(const Vector3D& v) const;

	Vector3D& operator+=(const Vector3D& v);

	Vector3D operator-(const Vector3D& v) const;

	double operator*(const Vector3D& v) const;

	Vector3D operator^(const Vector3D& v) const;

	void normalize(void);

	Vector3D& hat(void);
};

inline Vector3D
Vector3D::operator-(void) const
{
	return (Vector3D(-x, -y, -z));
}

inline double
Vector3D::len_squared(void)
{
	return (x*x+y*y+z*z);
}

inline Vector3D
Vector3D::operator*(const double a) const
{
	return (Vector3D(x*a, y*a, z*a));
}

inline Vector3D
Vector3D::operator/(const double a) const
{
	return (Vector3D(x/a, y/a, z/a));
}

inline Vector3D
Vector3D::operator+(const Vector3D& v) const
{
	return (Vector3D(x+v.x, y+v.y, z+v.z));
}

inline Vector3D
Vector3D::operator-(const Vector3D& v) const
{
	return (Vector3D(x-v.x, y-v.y, z-v.z));
}

inline double
Vector3D::operator*(const Vector3D& v) const
{
	return (x*v.x+y*v.y+z*v.z);
}

inline Vector3D
Vector3D::operator^(const Vector3D& v) const
{
	return (Vector3D(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x));
}

inline Vector3D&
Vector3D::operator+=(const Vector3D& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return (*this);
}

Vector3D operator*(const double a, const Vector3D& v);

inline Vector3D
operator*(const double a, const Vector3D& v)
{
	return (Vector3D(a*v.x, a*v.y, a*v.z));
}

Vector3D operator*(const Matrix& mat, const Vector3D& v);

#endif //TINYRAY_VECTOR3D_H
