//
//  Matte.h
//  TinyRay
//
//  Created by eyesfrog on 15/7/31.
//  Copyright (c) 2015年 eyesfrog. All rights reserved.
//

#ifndef __TinyRay__Matte__
#define __TinyRay__Matte__

#include "Material.h"
#include "../BRDF/Lambertian.h"

class Matte : public Material {
public:
	Matte(void);

	Matte(const Matte& m);

	Matte& operator=(const Matte& rhs);

	virtual Matte* clone(void) const;

	~Matte();

	void set_ka(const float ka);

	void set_kd(const float kd);

	void set_cd(const RGBColor c);

	void set_cd(const float _r, const float _g, const float _b);

	void set_cd(const float c);

	virtual RGBColor shade(ShadeRec& sr);

	virtual RGBColor area_light_shade(ShadeRec& sr);

private:
	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
};

inline void
Matte::set_ka(const float ka)
{
	ambient_brdf->set_kd(ka);
}

inline void
Matte::set_kd(const float kd)
{
	diffuse_brdf->set_kd(kd);
}

inline void
Matte::set_cd(const RGBColor c)
{
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

inline void
Matte::set_cd(const float _r, const float _g, const float _b)
{
	ambient_brdf->set_cd(_r, _g, _b);
	diffuse_brdf->set_cd(_r, _g, _b);
}

inline void
Matte::set_cd(const float c)
{
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

#endif /* defined(__TinyRay__Matte__) */
