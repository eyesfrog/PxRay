//
//  Light.h
//  TinyRay
//
//  Created by eyesfrog on 15/7/31.
//  Copyright (c) 2015年 eyesfrog. All rights reserved.
//

#ifndef __TinyRay__Light__
#define __TinyRay__Light__

#include "../Utilities/Vector3D.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Ray.h"

class ShadeRec;

class Light {
public:
	Light(void);

	Light(const Light& ls);

	virtual ~Light();

	Light&
			operator=(const Light& rhs);

	virtual Light* clone(void) const = 0;

	virtual Vector3D
			get_direction(ShadeRec& sr) = 0;

	void set_shadows(bool tf);

	bool casts_shadows();

	virtual RGBColor L(ShadeRec& sr);

	virtual float G(const ShadeRec& sr) const;

	virtual float pdf(const ShadeRec& sr) const;

	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const = 0;

protected:
	bool shadows;
};

inline void
Light::set_shadows(bool tf)
{
	shadows = tf;
}

inline bool
Light::casts_shadows()
{
	return shadows;
}

#endif /* defined(__TinyRay__Light__) */
