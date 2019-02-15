#ifndef RT_WORLD_H
#define RT_WORLD_H

#include <vector>

#include "../Shapes/Rect.h"
#include "../Shapes/Triangle.h"

class World
{
private:
	std::vector<Rect> rects;
	std::vector<Triangle> triangles;
	Double3 fogColor;
	double fogDistance;
public:
	int getRectCount() const;
	int getTriangleCount() const;
	const Rect &getRect(int index) const;
	const Triangle &getTriangle(int index) const;
	const Double3 &getFogColor() const;
	double getFogDistance() const;

	void addRect(Rect &&rect);
	void addTriangle(Triangle &&triangle);
	void setFogColor(const Double3 &fogColor);
	void setFogDistance(double fogDistance);

	void init(const Double3 &fogColor, double fogDistance);
};

#endif
