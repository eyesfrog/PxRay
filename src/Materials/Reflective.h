//
//  Reflective.h
//  TinyRay
//
//  Created by eyefrog on 15/8/3.
//  Copyright (c) 2015年 eyefrog. All rights reserved.
//

#ifndef __TinyRay__Reflective__
#define __TinyRay__Reflective__

#include "Phong.h"
#include "../BRDF/PerfectSpecular.h"

class Reflective : public Phong {
public:
	Reflective(void);

	Reflective(const Reflective& rm);

	Reflective&
			operator=(const Reflective& rhs);

	virtual Reflective*
			clone(void) const;

	~Reflective(void);

	void set_kr(const float k);

	void set_cr(const RGBColor& c);

	void set_cr(const float _r, const float _g, const float _b);

	void set_cr(const float c);

	virtual RGBColor
			shade(ShadeRec& s);

private:
	PerfectSpecular* reflective_brdf;
};

inline void
Reflective::set_kr(const float k)
{
	reflective_brdf->set_kr(k);
}

inline void
Reflective::set_cr(const RGBColor& c)
{
	reflective_brdf->set_cr(c);
}

inline void
Reflective::set_cr(const float c)
{
	reflective_brdf->set_cr(c);
}

inline void
Reflective::set_cr(const float _r, const float _g, const float _b)
{
	reflective_brdf->set_cr(_r, _g, _b);
}

#endif /* defined(__TinyRay__Reflective__) */
