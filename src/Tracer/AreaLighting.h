//
// Created by eyesfrog on 16/4/12.
//

#ifndef TINYRAY_AREALIGHTING_H
#define TINYRAY_AREALIGHTING_H

#include "Tracer.h"

class AreaLighting : public Tracer {
public:
	AreaLighting(void);

	AreaLighting(World* w_ptr);

	virtual ~AreaLighting();

	virtual RGBColor trace_ray(const Ray ray, const int depth) const;

};

#endif //TINYRAY_AREALIGHTING_H
