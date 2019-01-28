#include "DirectionalLight.h"

const Double3 &DirectionalLight::getDirection() const
{
	return this->direction;
}

const Double3 &DirectionalLight::getColor() const
{
	return this->color;
}

void DirectionalLight::setDirection(const Double3 &direction)
{
	this->direction = direction;
}

void DirectionalLight::setColor(const Double3 &color)
{
	this->color = color;
}

void DirectionalLight::init(const Double3 &direction, const Double3 &color)
{
	this->direction = direction;
	this->color = color;
}
