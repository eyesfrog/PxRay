//
// Created by eyefrog on 15/7/15.
//

#ifndef TINYRAY_GEOMETRICOBJECT_H
#define TINYRAY_GEOMETRICOBJECT_H

class Material;

#include "../Utilities/RGBColor.h"
#include "../Utilities/BBox.h"
#include "../Utilities/Ray.h"
#include "../Utilities/ShadeRec.h"

class GeometricObject {

public:

	GeometricObject(void);

	virtual GeometricObject*
			clone(void) const = 0;

	virtual ~GeometricObject();

	virtual bool
			hit(const Ray& ray, double& tmin, ShadeRec& sr) const = 0;

	virtual bool
			shadow_hit(const Ray& ray, double& tmin) const = 0;

	virtual void set_material(Material* mPtr);

	Material* get_material(void) const;

	void set_color(double _r, double _g, double _b);

	void set_color(const RGBColor& _color);

	RGBColor get_color(void);

protected:
	RGBColor color;
	mutable Material* material_ptr;
};

inline RGBColor GeometricObject::get_color(void)
{
	return color;
}

#endif //TINYRAY_GEOMETRICOBJECT_H
