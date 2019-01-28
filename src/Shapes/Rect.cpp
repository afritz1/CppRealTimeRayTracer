#include "Rect.h"
#include "../Acceleration/BoundingBox.h"

const Double3 &Rect::getPoint() const
{
	return this->point;
}

const Double3 &Rect::getP1()
{
	if (this->dirty)
	{
		this->updatePoints();
	}

	return this->p1;
}

const Double3 &Rect::getP2()
{
	if (this->dirty)
	{
		this->updatePoints();
	}

	return this->p2;
}

const Double3 &Rect::getP3()
{
	if (this->dirty)
	{
		this->updatePoints();
	}

	return this->p3;
}

const Double3 &Rect::getP4()
{
	if (this->dirty)
	{
		this->updatePoints();
	}

	return this->p4;
}

const Double3 &Rect::getNormal() const
{
	return this->normal;
}

const Double3 &Rect::getTangent() const
{
	return this->tangent;
}

const Double3 &Rect::getBinormal() const
{
	return this->binormal;
}

const Double2 &Rect::getUV1() const
{
	return this->uv1;
}

const Double2 &Rect::getUV2() const
{
	return this->uv2;
}

double Rect::getWidth() const
{
	return this->width;
}

double Rect::getHeight() const
{
	return this->height;
}

int Rect::getMaterialIndex() const
{
	return this->materialIndex;
}

BoundingBox Rect::getBoundingBox() const
{
	const Double3 min = this->p1.componentMin(this->p2)
		.componentMin(this->p3).componentMin(this->p4);
	const Double3 max = this->p1.componentMax(this->p2)
		.componentMax(this->p3).componentMax(this->p4);

	BoundingBox bbox;
	bbox.init(min, max);
	return bbox;
}

void Rect::setPoint(const Double3 &p)
{
	this->point = p;
	this->dirty = true;
}

void Rect::setNormals(const Double3 &normal, const Double3 &tangent)
{
	this->normal = normal;
	this->tangent = tangent;
	this->binormal = normal.cross(tangent).normalized();
	this->dirty = true;
}

void Rect::setUV1(const Double2 &uv)
{
	this->uv1 = uv;
}

void Rect::setUV2(const Double2 &uv)
{
	this->uv2 = uv;
}

void Rect::setWidth(double width)
{
	this->width = width;
	this->dirty = true;
}

void Rect::setHeight(double height)
{
	this->height = height;
	this->dirty = true;
}

void Rect::setMaterialIndex(int index)
{
	this->materialIndex = index;
}

void Rect::init(const Double3 &point, const Double3 &normal, const Double3 &tangent, double width,
	double height, const Double2 &uv1, const Double2 &uv2, int materialIndex)
{
	this->point = point;
	this->setNormals(normal, tangent);
	this->width = width;
	this->height = height;
	this->uv1 = uv1;
	this->uv2 = uv2;
	this->materialIndex = materialIndex;
	this->dirty = true;
}

void Rect::updatePoints()
{
	const Double3 scaledTangent = this->tangent * (this->width * 0.50);
	const Double3 scaledBinormal = this->binormal * (this->height * 0.50);
	this->p1 = this->point - scaledTangent - scaledBinormal;
	this->p2 = this->point + scaledTangent - scaledBinormal;
	this->p3 = this->point - scaledTangent + scaledBinormal;
	this->p4 = this->point + scaledTangent + scaledBinormal;
	this->dirty = false;
}
