#ifndef RT_RAY_H
#define RT_RAY_H

#include "../Math/Double3.h"

// Convenience class for creating rays the simple way.

struct Ray
{
	Double3 point, direction;

	Double3 pointAt(double t) const
	{
		return this->point + (this->direction * t);
	}

	void init(const Double3 &point, const Double3 &direction)
	{
		this->point = point;
		this->direction = direction;
	}
};

#endif
