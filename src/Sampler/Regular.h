//
//  Regular.h
//  TinyRay
//
//  Created by eyesfrog on 15/7/20.
//  Copyright (c) 2015年 eyesfrog. All rights reserved.
//

#ifndef __TinyRay__Regular__
#define __TinyRay__Regular__

#include "Sampler.h"

class Regular : public Sampler {

public:
	Regular(void);

	Regular(const int num);

	Regular(const Regular& u);

	Regular&
			operator=(const Regular& rhs);

	virtual Regular*
			clone(void) const;

	virtual ~Regular();

private:

	virtual void
			generate_samples(void);

};

#endif /* defined(__TinyRay__Regular__) */
