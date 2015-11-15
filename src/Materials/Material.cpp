//
//  Material.cpp
//  TinyRay
//
//  Created by eyefrog on 15/7/31.
//  Copyright (c) 2015年 eyefrog. All rights reserved.
//

#include "Material.h"

Material::Material(void) { }

Material::Material(const Material& m) { }

Material&
Material::operator=(const Material& rhs)
{
	if (this==&rhs) {
		return *this;
	}

	return *this;
}

Material::~Material() { }

RGBColor
Material::shade(ShadeRec& sr)
{
	return black;
}