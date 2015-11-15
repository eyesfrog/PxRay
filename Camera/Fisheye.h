//
//  Fisheye.hpp
//  TinyRay
//
//  Created by eyefrog on 15/11/15.
//  Copyright © 2015年 eyefrog. All rights reserved.
//

#ifndef Fisheye_h
#define Fisheye_h

#include "Camera.h"

class Fisheye : public Camera {

public:
	Fisheye(void);

	Fisheye(const Fisheye& fe);

	virtual ~Fisheye();

	virtual Camera* clone(void) const;

	Fisheye&
			operator=(const Fisheye& rhs);

};

#endif /* Fisheye_h */
