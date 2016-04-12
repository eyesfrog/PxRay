//
// Created by eyesfrog on 15/7/16.
//

#ifndef TINYRAY_TRACER_H
#define TINYRAY_TRACER_H

#include "../Utilities/Constants.h"
#include "../Utilities/ShadeRec.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Ray.h"

class World;

class Tracer {

public:
	Tracer(void);

	Tracer(World* w_ptr);

	virtual RGBColor
			trace_ray(const Ray& ray) const;

	virtual RGBColor
			trace_ray(const Ray ray, const int depth) const;

	//virtual RGBColor
	//trace_ray(const Ray& ray, double& tmin, const int depth) const;

	virtual ~Tracer();

protected:

	World* world_ptr;

};

#endif //TINYRAY_TRACER_H
