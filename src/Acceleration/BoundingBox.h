#ifndef RT_BOUNDING_BOX_H
#define RT_BOUNDING_BOX_H

#include "../Math/Double3.h"

class BoundingBox
{
private:
	Double3 min, max;
public:
	const Double3 &getMin() const;
	const Double3 &getMax() const;

	bool contains(const Double3 &point) const;
	bool contains(const BoundingBox &bbox) const;

	void expandToInclude(const Double3 &point);
	void expandToInclude(const BoundingBox &bbox);

	static BoundingBox encapsulate(const BoundingBox &a, const BoundingBox &b);

	void init(const Double3 &min, const Double3 &max);
};

#endif
