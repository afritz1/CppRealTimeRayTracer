#include <cassert>

#include "BoundingBox.h"

const Double3 &BoundingBox::getMin() const
{
	return this->min;
}

const Double3 &BoundingBox::getMax() const
{
	return this->max;
}

bool BoundingBox::contains(const Double3 &point) const
{
	return (this->min.x <= point.x) &&
		(this->min.y <= point.y) &&
		(this->min.z <= point.z) &&
		(this->max.x >= point.x) &&
		(this->max.y >= point.y) &&
		(this->max.z >= point.z);
}

bool BoundingBox::contains(const BoundingBox &bbox) const
{
	return (this->min.x <= bbox.min.x) &&
		(this->min.y <= bbox.min.y) &&
		(this->min.z <= bbox.min.z) &&
		(this->max.x >= bbox.max.x) &&
		(this->max.y >= bbox.max.y) &&
		(this->max.z >= bbox.max.z);
}

void BoundingBox::expandToInclude(const Double3 &point)
{
	double *minPtr = this->min.data();
	double *maxPtr = this->max.data();
	const double *pointPtr = point.data();

	for (int i = 0; i < 3; i++)
	{
		double &minRef = minPtr[i];
		double &maxRef = maxPtr[i];
		const double pointValue = pointPtr[i];

		if (minRef > pointValue)
		{
			minRef = pointValue;
		}
		else if (maxRef < pointValue)
		{
			maxRef = pointValue;
		}
	}
}

void BoundingBox::expandToInclude(const BoundingBox &bbox)
{
	double *minPtr = this->min.data();
	double *maxPtr = this->max.data();
	const double *bboxMinPtr = bbox.min.data();
	const double *bboxMaxPtr = bbox.max.data();

	for (int i = 0; i < 3; i++)
	{
		double &minRef = minPtr[i];
		double &maxRef = maxPtr[i];
		const double bboxMinValue = bboxMinPtr[i];
		const double bboxMaxValue = bboxMaxPtr[i];

		if (minRef > bboxMinValue)
		{
			minRef = bboxMinValue;
		}

		if (maxRef < bboxMaxValue)
		{
			maxRef = bboxMaxValue;
		}
	}
}

BoundingBox BoundingBox::encapsulate(const BoundingBox &a, const BoundingBox &b)
{
	BoundingBox bbox;
	bbox.init(a.min.componentMin(b.min), a.max.componentMax(b.max));
	return bbox;
}

void BoundingBox::init(const Double3 &min, const Double3 &max)
{
	assert(min.x <= max.x);
	assert(min.y <= max.y);
	assert(min.z <= max.z);

	this->min = min;
	this->max = max;
}
