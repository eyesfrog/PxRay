//
// Created by eyesfrog on 15/7/15.
//

#ifndef TINYRAY_RGBCOLOR_H
#define TINYRAY_RGBCOLOR_H

class RGBColor {
public:
	float r, g, b;
public:
	RGBColor(void);

	RGBColor(float c);

	RGBColor(float _r, float _g, float _b);

	RGBColor(const RGBColor& c);

	~RGBColor();

	RGBColor& operator=(const RGBColor& rhs);

	RGBColor operator+(const RGBColor& c) const;

	RGBColor& operator+=(const RGBColor& c);

	RGBColor operator*(const float a) const;

	RGBColor& operator*=(const float a);

	RGBColor operator/(const float a) const;

	RGBColor& operator/=(const float a);

	RGBColor operator*(const RGBColor& c) const;

	bool operator==(const RGBColor& c) const;

	RGBColor powc(double p) const;

	double average(void) const;

};

inline RGBColor
RGBColor::operator+(const RGBColor& c) const
{
	return (RGBColor(r+c.r, g+c.g, b+c.b));
}

inline RGBColor&
RGBColor::operator+=(const RGBColor& c)
{
	r += c.r;
	g += c.g;
	b += c.b;
	return (*this);
}

inline RGBColor
RGBColor::operator*(const float a) const
{
	return (RGBColor(r*a, g*a, b*a));
}

inline RGBColor&
RGBColor::operator*=(const float a)
{
	r *= a;
	g *= a;
	b *= a;
	return (*this);
}

inline RGBColor
RGBColor::operator/(const float a) const
{
	return (RGBColor(r/a, g/a, b/a));
}

inline RGBColor&
RGBColor::operator/=(const float a)
{
	r /= a;
	g /= a;
	b /= a;
	return (*this);
}

inline RGBColor
RGBColor::operator*(const RGBColor& c) const
{
	return (RGBColor(r*c.r, g*c.g, b*c.b));
}

inline bool
RGBColor::operator==(const RGBColor& c) const
{
	return (r==c.r && g==c.g && b==c.b);
}

inline double
RGBColor::average(void) const
{
	return (0.333333333333*(r+g+b));
}

RGBColor operator*(const float a, const RGBColor& c);

inline RGBColor
operator*(const float a, const RGBColor& c)
{
	return (RGBColor(a*c.r, a*c.g, a*c.b));
}

#endif //TINYRAY_RGBCOLOR_H
