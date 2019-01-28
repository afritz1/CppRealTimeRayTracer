#ifndef RT_RECT_H
#define RT_RECT_H

#include "../Math/Double2.h"
#include "../Math/Double3.h"

// Rectangles for speed; half the intersection cost of triangles.

// Layout:
// - point: center
// - p1: (0, 0)
// - p2: (1, 0)
// - p3: (0, 1)
// - p4: (1, 1)
// - normal: points out
// - tangent: points right
// - binormal: points up
// - uv1: @p3 (top left)
// - uv2: @p2 (bottom right)

class Rect
{
private:
	Double3 point, p1, p2, p3, p4;
	Double3 normal, tangent, binormal; // Normal: 'y', tangent: 'x', binormal: 'z'.
	Double2 uv1, uv2;
	double width, height;
	int materialIndex;
	bool dirty;

	void updatePoints();
public:
	const Double3 &getPoint() const;
	const Double3 &getP1();
	const Double3 &getP2();
	const Double3 &getP3();
	const Double3 &getP4();
	const Double3 &getNormal() const;
	const Double3 &getTangent() const;
	const Double3 &getBinormal() const;
	const Double2 &getUV1() const;
	const Double2 &getUV2() const;
	double getWidth() const;
	double getHeight() const;
	int getMaterialIndex() const;

	void setPoint(const Double3 &p);
	void setNormals(const Double3 &normal, const Double3 &tangent);
	void setUV1(const Double2 &uv);
	void setUV2(const Double2 &uv);
	void setWidth(double width);
	void setHeight(double height);
	void setMaterialIndex(int index);

	void init(const Double3 &point, const Double3 &normal, const Double3 &tangent, double width,
		double height, const Double2 &uv1, const Double2 &uv2, int materialIndex);
};

#endif
