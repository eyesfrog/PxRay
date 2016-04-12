//
//  Light.cpp
//  TinyRay
//
//  Created by eyesfrog on 15/7/31.
//  Copyright (c) 2015年 eyesfrog. All rights reserved.
//

#include "Light.h"

#include "../Utilities/Constants.h"

Light::Light(void)
		:
		shadows(false) { }

Light::Light(const Light& ls) { }

Light&
Light::operator=(const Light& rhs)
{
	if (this==&rhs) {
		return *this;
	}

	return *this;
}

Light::~Light() { }

RGBColor
Light::L(ShadeRec& sr)
{
	return black;
}