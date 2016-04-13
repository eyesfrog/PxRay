//
// Created by eyesfrog on 16/4/13.
//

#ifndef TINYRAY_AREALIGHT_H
#define TINYRAY_AREALIGHT_H

#include "Light.h"
#include "../GeometricObjects/GeometricObject.h"
class Material;

class AreaLight: public Light {
public:
	AreaLight(void);

	AreaLight(const AreaLight& al);

	virtual AreaLight* clone(void) const;

	virtual ~AreaLight();

	AreaLight& operator= (const AreaLight& rhs);

	void set_object(GeometricObject* obj_ptr);

	virtual Vector3D get_direction(ShadeRec& sr);

	virtual RGBColor L(ShadeRec& sr);

	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

	virtual float G(const ShadeRec& sr) const;

	virtual float pdf(ShadeRec& sr) const;

private:

	GeometricObject* object_ptr;
	Material* material_ptr;
	Point3D sample_point;
	Normal light_normal;
	Vector3D wi;
};

inline
void AreaLight::set_object(GeometricObject* obj_ptr) {
	object_ptr = obj_ptr;
	material_ptr = object_ptr->get_material();
}

#endif //TINYRAY_AREALIGHT_H
