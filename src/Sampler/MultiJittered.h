//
//  MultiJittered.h
//  TinyRay
//
//  Created by eyesfrog on 15/7/21.
//  Copyright (c) 2015年 eyesfrog. All rights reserved.
//

#ifndef __TinyRay__MultiJittered__
#define __TinyRay__MultiJittered__

#include "Sampler.h"

class MultiJittered : public Sampler {

public:
	MultiJittered(void);

	MultiJittered(const int num_samples);

	MultiJittered(const int num_samples, const int m);

	MultiJittered(const MultiJittered& mjs);

	MultiJittered&
			operator=(const MultiJittered& rhs);

	virtual MultiJittered*
			clone(void) const;

	virtual ~MultiJittered(void);

private:

	virtual void
			generate_samples(void);
};

#endif /* defined(__TinyRay__MultiJittered__) */
