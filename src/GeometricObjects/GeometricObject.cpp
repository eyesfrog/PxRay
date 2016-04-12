//
// Created by eyesfrog on 15/7/15.
//

#include "GeometricObject.h"

GeometricObject::GeometricObject(void) { }

GeometricObject::~GeometricObject() { }

void GeometricObject::set_color(double _r, double _g, double _b)
{
	color.r = _r;
	color.g = _g;
	color.b = _b;
}

void GeometricObject::set_color(const RGBColor& _color)
{
	color.r = _color.r;
	color.g = _color.g;
	color.b = _color.b;
}

void GeometricObject::set_material(Material* mPtr)
{
	material_ptr = mPtr;
}

Material*
GeometricObject::get_material(void) const
{
	return material_ptr;
}