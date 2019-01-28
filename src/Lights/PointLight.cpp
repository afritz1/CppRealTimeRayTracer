#include "PointLight.h"

const Double3 &PointLight::getPoint() const
{
	return this->point;
}

const Double3 &PointLight::getColor() const
{
	return this->color;
}

double PointLight::getRadius() const
{
	return this->radius;
}

void PointLight::setPoint(const Double3 &point)
{
	this->point = point;
}

void PointLight::setColor(const Double3 &color)
{
	this->color = color;
}

void PointLight::setRadius(double radius)
{
	this->radius = radius;
}

void PointLight::init(const Double3 &point, const Double3 &color, double radius)
{
	this->point = point;
	this->color = color;
	this->radius = radius;
}
