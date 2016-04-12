//
//  Material.h
//  TinyRay
//
//  Created by eyesfrog on 15/7/31.
//  Copyright (c) 2015年 eyesfrog. All rights reserved.
//

#ifndef __TinyRay__Material__
#define __TinyRay__Material__

#include "../World/World.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/ShadeRec.h"

class Material {
public:

	Material(void);

	Material(const Material& material);

	virtual Material*
			clone(void) const = 0;

	virtual ~Material();

	virtual RGBColor
			shade(ShadeRec& sr);

protected:
	Material&
			operator=(const Material& rhs);
};

#endif /* defined(__TinyRay__Material__) */
