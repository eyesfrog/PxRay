//
//  RayCast.h
//  TinyRay
//
//  Created by eyefrog on 15/7/31.
//  Copyright (c) 2015年 eyefrog. All rights reserved.
//

#ifndef __TinyRay__RayCast__
#define __TinyRay__RayCast__

#include "Tracer.h"

class RayCast : public Tracer {
public:
	RayCast(void);

	RayCast(World* _worldPtr);

	virtual ~RayCast();

	virtual RGBColor
			trace_ray(const Ray& ray) const;
};

#endif /* defined(__TinyRay__RayCast__) */
