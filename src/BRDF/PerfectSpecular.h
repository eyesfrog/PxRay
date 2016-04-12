//
//  PerfectSpecular.h
//  TinyRay
//
//  Created by eyesfrog on 15/8/3.
//  Copyright (c) 2015年 eyesfrog. All rights reserved.
//

#ifndef __TinyRay__PerfectSpecular__
#define __TinyRay__PerfectSpecular__

#include "BRDF.h"
#include "../Utilities/Normal.h"

class PerfectSpecular : public BRDF {
public:
	PerfectSpecular(void);

	~PerfectSpecular();

	virtual PerfectSpecular*
			clone(void) const;

	void
			set_kr(const float k);

	void
			set_cr(const RGBColor& c);

	void
			set_cr(const float _r, const float _g, const float _b);

	void
			set_cr(const float c);

	virtual RGBColor
			f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	virtual RGBColor
			sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;

	virtual RGBColor
			sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

	virtual RGBColor
			rho(const ShadeRec& sr, const Vector3D& wo) const;

private:
	float kr;
	RGBColor cr;
};

inline void
PerfectSpecular::set_kr(const float k)
{
	kr = k;
}

inline void
PerfectSpecular::set_cr(const RGBColor& c)
{
	cr = c;
}

inline void
PerfectSpecular::set_cr(const float _r, const float _g, const float _b)
{
	cr.r = _r;
	cr.g = _g;
	cr.b = _b;
}

inline void
PerfectSpecular::set_cr(const float c)
{
	cr.r = c;
	cr.g = c;
	cr.b = c;
}

#endif /* defined(__TinyRay__PerfectSpecular__) */
