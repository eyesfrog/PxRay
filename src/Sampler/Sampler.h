//
//  Sampler.h
//  TinyRay
//
//  Created by eyefrog on 15/7/20.
//  Copyright (c) 2015年 eyefrog. All rights reserved.
//

#ifndef __TinyRay__Sampler__
#define __TinyRay__Sampler__

#include <vector>
#include <math.h>

#include "math.h"
#include "../Utilities/Point2D.h"
#include "../Utilities/Point3D.h"

class Sampler {

public:
	Sampler(void);

	Sampler(const int num);

	Sampler(const int num, const int num_sets);

	Sampler(const Sampler& s);

	Sampler& operator=(const Sampler& rhs);

	virtual Sampler* clone(void) const = 0;

	virtual ~Sampler(void);

	void set_num_sets(const int np);

	int get_num_samples(void);

	virtual void generate_samples(void) = 0;

	void shuffle_x_coordinates(void);

	void shuffle_y_coordinates(void);

	void setup_shuffled_indices(void);

	void map_samples_to_unit_disk(void);

	void map_samples_to_hemisphere(const float p);

	void map_samples_to_sphere(void);

	Point2D sample_unit_square(void);

	Point2D sample_unit_disk(void);

	Point3D sample_hemisphere(void);

	Point3D sample_sphere(void);

	Point2D sample_one_set(void);

protected:

	int num_samples;
	int num_sets;
	std::vector<Point2D> samples;
	std::vector<int> shuffled_indices;
	std::vector<Point2D> disk_samples;
	std::vector<Point3D> hemisphere_samples;
	std::vector<Point3D> sphere_samples;
	unsigned long count;
	int jump;
};

#endif /* defined(__TinyRay__Sampler__) */
