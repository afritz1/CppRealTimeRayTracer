#include "World.h"

int World::getRectCount() const
{
	return static_cast<int>(this->rects.size());
}

int World::getTriangleCount() const
{
	return static_cast<int>(this->triangles.size());
}

const Rect &World::getRect(int index) const
{
	return this->rects.at(index);
}

const Triangle &World::getTriangle(int index) const
{
	return this->triangles.at(index);
}

const Double3 &World::getFogColor() const
{
	return this->fogColor;
}

double World::getFogDistance() const
{
	return this->fogDistance;
}

void World::addRect(Rect &&rect)
{
	this->rects.push_back(std::move(rect));
}

void World::addTriangle(Triangle &&triangle)
{
	this->triangles.push_back(std::move(triangle));
}

void World::setFogColor(const Double3 &fogColor)
{
	this->fogColor = fogColor;
}

void World::setFogDistance(double fogDistance)
{
	this->fogDistance = fogDistance;
}

void World::init(const Double3 &fogColor, double fogDistance)
{
	this->setFogColor(fogColor);
	this->setFogDistance(fogDistance);
}
