//
//  Lambertian.h
//  TinyRay
//
//  Created by eyefrog on 15/7/31.
//  Copyright (c) 2015年 eyefrog. All rights reserved.
//

#ifndef __TinyRay__Lambertian__
#define __TinyRay__Lambertian__

#include "BRDF.h"

class Lambertian : public BRDF {
public:
	Lambertian(void);

	Lambertian(const Lambertian& lamb);

	virtual
	~Lambertian();

	Lambertian&
			operator=(const Lambertian& rhs);

	virtual BRDF*
			clone(void) const;

	virtual RGBColor
			f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	virtual RGBColor
			sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

	virtual RGBColor
			rho(const ShadeRec& sr, const Vector3D& wo) const;

	void set_ka(const float _ka);

	void set_kd(const float _kd);

	void set_cd(const float _r, const float _g, const float _b);

	void set_cd(const RGBColor& c);

	void set_cd(const float c);

private:
	float kd;
	RGBColor cd;
};

inline void
Lambertian::set_ka(const float _ka)
{
	kd = _ka;
}

inline void
Lambertian::set_kd(const float _kd)
{
	kd = _kd;
}

inline void
Lambertian::set_cd(const float c)
{
	cd.r = c;
	cd.g = c;
	cd.b = c;
}

inline void
Lambertian::set_cd(const RGBColor& c)
{
	cd = c;
}

inline void
Lambertian::set_cd(const float _r, const float _g, const float _b)
{
	cd.r = _r;
	cd.g = _g;
	cd.b = _b;
}

#endif /* defined(__TinyRay__Lambertian__) */
