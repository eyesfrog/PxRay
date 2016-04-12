//
//  Phong.h
//  TinyRay
//
//  Created by eyesfrog on 15/8/3.
//  Copyright (c) 2015年 eyesfrog. All rights reserved.
//

#ifndef __TinyRay__Phong__
#define __TinyRay__Phong__

#include "Material.h"
#include "../Utilities/Ray.h"
#include "../BRDF/Lambertian.h"
#include "../BRDF/GlossySpecular.h"

class Phong : public Material {
public:
	Phong(void);

	Phong(const Phong& p);

	~Phong();

	Phong&
			operator=(const Phong& rhs);

	virtual Material*
			clone(void) const;

	virtual RGBColor shade(ShadeRec& sr);

	void set_ka(const float ka);

	void set_kd(const float kd);

	void set_ks(const float ks);

	void set_exp(const float exp);

	void set_cd(const RGBColor c);

	void set_cd(const float _r, const float _g, const float _b);

	void set_cd(const float c);

protected:
	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
	GlossySpecular* specular_brdf;
};

inline void
Phong::set_ka(const float ka)
{
	ambient_brdf->set_kd(ka);
}

inline void
Phong::set_kd(const float kd)
{
	diffuse_brdf->set_kd(kd);
}

inline void
Phong::set_ks(const float ks)
{
	specular_brdf->set_ks(ks);
}

inline void
Phong::set_exp(const float exp)
{
	specular_brdf->set_exp(exp);
}

inline void
Phong::set_cd(const RGBColor c)
{
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
	specular_brdf->set_cd(c);
}

inline void
Phong::set_cd(const float _r, const float _g, const float _b)
{
	ambient_brdf->set_cd(_r, _g, _b);
	diffuse_brdf->set_cd(_r, _g, _b);
	specular_brdf->set_cd(_r, _g, _b);
}

inline void
Phong::set_cd(const float c)
{
	ambient_brdf->set_cd(c);
	ambient_brdf->set_cd(c);
	specular_brdf->set_cd(c);
}

#endif /* defined(__TinyRay__Phong__) */
