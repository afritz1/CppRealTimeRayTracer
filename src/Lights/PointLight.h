#ifndef RT_POINT_LIGHT_H
#define RT_POINT_LIGHT_H

#include "../Math/Double3.h"

class PointLight
{
private:
	Double3 point, color;
	double radius;
public:
	const Double3 &getPoint() const;
	const Double3 &getColor() const;
	double getRadius() const;

	void setPoint(const Double3 &point);
	void setColor(const Double3 &color);
	void setRadius(double radius);

	void init(const Double3 &point, const Double3 &color, double radius);
};

#endif
