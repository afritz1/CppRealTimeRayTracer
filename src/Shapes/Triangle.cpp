#include "Triangle.h"
#include "../Acceleration/BoundingBox.h"

const Double3 &Triangle::getP1() const
{
	return this->p1;
}

const Double3 &Triangle::getP2() const
{
	return this->p2;
}

const Double3 &Triangle::getP3() const
{
	return this->p3;
}

const Double3 &Triangle::getNormal()
{
	if (this->dirty)
	{
		this->normal = (p2 - p1).cross(p3 - p2).normalized();
		this->dirty = false;
	}

	return this->normal;
}

const Double2 &Triangle::getUV1() const
{
	return this->uv1;
}

const Double2 &Triangle::getUV2() const
{
	return this->uv2;
}

const Double2 &Triangle::getUV3() const
{
	return this->uv3;
}

int Triangle::getMaterialIndex() const
{
	return this->materialIndex;
}

BoundingBox Triangle::getBoundingBox() const
{
	const Double3 min = this->p1.componentMin(this->p2).componentMin(this->p3);
	const Double3 max = this->p1.componentMax(this->p2).componentMax(this->p3);

	BoundingBox bbox;
	bbox.init(min, max);
	return bbox;
}

void Triangle::setP1(const Double3 &p)
{
	this->p1 = p;
	this->dirty = true;
}

void Triangle::setP2(const Double3 &p)
{
	this->p2 = p;
	this->dirty = true;
}

void Triangle::setP3(const Double3 &p)
{
	this->p3 = p;
	this->dirty = true;
}

void Triangle::setUV1(const Double2 &uv)
{
	this->uv1 = uv;
}

void Triangle::setUV2(const Double2 &uv)
{
	this->uv2 = uv;
}

void Triangle::setUV3(const Double2 &uv)
{
	this->uv3 = uv;
}

void Triangle::setMaterialIndex(int index)
{
	this->materialIndex = index;
}

void Triangle::init(const Double3 &p1, const Double3 &p2, const Double3 &p3,
	const Double2 &uv1, const Double2 &uv2, const Double2 &uv3, int materialIndex)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->uv1 = uv1;
	this->uv2 = uv2;
	this->uv3 = uv3;
	this->materialIndex = materialIndex;
	this->dirty = true;
}
