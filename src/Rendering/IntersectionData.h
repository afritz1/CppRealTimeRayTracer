#ifndef RT_INTERSECTION_DATA_H
#define RT_INTERSECTION_DATA_H

#include "../Math/Double2.h"
#include "../Math/Double3.h"

struct IntersectionData
{
	Double3 point, normal;
	Double2 uv;
	double t;
	union
	{
		int rectIndex;
		int triangleIndex;
	};
};

#endif
