//
//  BRDF.h
//  TinyRay
//
//  Created by eyefrog on 15/7/30.
//  Copyright (c) 2015年 eyefrog. All rights reserved.
//

#ifndef __TinyRay__BRDF__
#define __TinyRay__BRDF__

#include "../Utilities/Vector3D.h"
#include "../Sampler/Sampler.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/ShadeRec.h"

class BRDF {
public:

	BRDF(void);

	BRDF(const BRDF& brdf);

	virtual ~BRDF(void);

	BRDF&
			operator=(const BRDF& rhs);

	virtual BRDF*
			clone(void) const = 0;

	void set_sampler(Sampler* sPtr);

	virtual RGBColor
			f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	virtual RGBColor
			sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;

	virtual RGBColor
			sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi,
			const float& pdf) const;

	virtual RGBColor
			rho(const ShadeRec& sr, const Vector3D& wo) const;

protected:

	Sampler* sampler_ptr;

};

#endif /* defined(__TinyRay__BRDF__) */
