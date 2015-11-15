//
// Created by eyefrog on 15/7/15.
//

#ifndef TINYRAY_SHADEREC_H
#define TINYRAY_SHADEREC_H

#include <vector>

class World;

class Material;

#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "RGBColor.h"

class ShadeRec {
public:

	bool hit_an_object;
	Material* material_ptr;
	Point3D hit_point;
	Point3D local_hit_point;
	Vector3D dir;
	Normal normal;
	Ray ray;
	int depth;
	double t;
	World& w;
	RGBColor color;

	ShadeRec(World& wr);

	ShadeRec(const ShadeRec& sr);

	~ShadeRec();

};

#endif //TINYRAY_SHADEREC_H
