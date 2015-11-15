//
//  BBox.h
//  TinyRay
//
//  Created by eyefrog on 15/7/30.
//  Copyright (c) 2015年 eyefrog. All rights reserved.
//

#ifndef __TinyRay__BBox__
#define __TinyRay__BBox__

#include "Ray.h"
#include "Point3D.h"

class BBox {
public:
	double x0, x1, y0, y1, z0, z1;

	BBox(void);

	BBox(const double _x0, const double _x1,
			const double _y0, const double _y1,
			const double _z0, const double _z1);

	BBox(const Point3D& p0, const Point3D& p1);

	BBox(const BBox& bbox);

	BBox&
			operator=(const BBox& rhs);

	~BBox();

	bool
			hit(const Ray& ray) const;

	bool
			inside(const Point3D& p) const;
};

#endif /* defined(__TinyRay__BBox__) */
