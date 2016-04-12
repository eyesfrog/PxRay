//
// Created by eyesfrog on 15/7/16.
//

#ifndef TINYRAY_SINGLESPHERE_H
#define TINYRAY_SINGLESPHERE_H

#include "Tracer.h"

class SingleSphere : public Tracer {

public:
	SingleSphere(void);

	SingleSphere(World* world_ptr);

	virtual
	~SingleSphere();

	virtual RGBColor
			trace_ray(const Ray& ray) const;
};

#endif //TINYRAY_SINGLESPHERE_H
