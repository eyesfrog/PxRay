//
//  Whitted.h
//  TinyRay
//
//  Created by eyefrog on 15/8/3.
//  Copyright (c) 2015年 eyefrog. All rights reserved.
//

#ifndef __TinyRay__Whitted__
#define __TinyRay__Whitted__

#include "Tracer.h"

class Whitted : public Tracer {
public:
	Whitted(void);

	Whitted(World* _worldptr);

	virtual ~Whitted(void);

	virtual RGBColor
			trace_ray(const Ray ray, const int depth) const;
};

#endif /* defined(__TinyRay__Whitted__) */
