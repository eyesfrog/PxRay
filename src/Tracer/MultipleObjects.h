//
// Created by eyesfrog on 15/7/17.
//

#ifndef TINYRAY_MULTIPLEOBJECTS_H
#define TINYRAY_MULTIPLEOBJECTS_H

#include "Tracer.h"
#include "../World/World.h"

class MultipleObjects : public Tracer {

public:

	MultipleObjects(void);

	MultipleObjects(World* w_ptr);

	virtual ~MultipleObjects();

	virtual RGBColor trace_ray(const Ray& ray) const;

};

#endif //TINYRAY_MULTIPLEOBJECTS_H
