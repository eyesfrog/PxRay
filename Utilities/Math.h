//
// Created by eyefrog on 15/7/15.
//

#ifndef TINYRAY_MATH_H
#define TINYRAY_MATH_H

#include <stdlib.h>

#include "Constants.h"

double
		min(double x0, double x1);

double
		max(double x0, double x1);

float
		rand_float(void);

int
		rand_int(void);

float
		rand_float(int l, float h);

int
		rand_int(int l, int h);

void
		set_rand_seed(const int seed);

//--------------------------------------------------

inline double
min(double x0, double x1)
{
	return ((x0<x1) ? x0 : x1);
}

inline double
max(double x0, double x1)
{
	return ((x0>x1) ? x0 : x1);
}

inline int
rand_int(void)
{
	return rand();
}

inline float
rand_float(void)
{
	return (float) rand_int()*invRAND_MAX;
}

inline void
set_rand_seed(const int seed)
{
	srand(seed);
}

inline int
rand_int(int l, int h)
{
	return int((rand_float(0, h-l+1)+l));
}

inline float
rand_float(int l, float h)
{
	return (rand_float()*(h-l)+l);
}

#endif //TINYRAY_MATH_H
