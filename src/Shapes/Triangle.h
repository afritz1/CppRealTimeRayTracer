#ifndef RT_TRIANGLE_H
#define RT_TRIANGLE_H

#include "../Math/Double2.h"
#include "../Math/Double3.h"

// Triangles for flexibility, when a rectangle isn't enough.

// Layout:
// - p1: (0, 0)
// - p2: (1, 0)
// - p3: (0, 1)

class BoundingBox;
class IntersectionData;
class Ray;

class Triangle
{
private:
	Double3 p1, p2, p3;
	Double3 normal;
	Double2 uv1, uv2, uv3;
	int materialIndex;
	bool dirty;
public:
	const Double3 &getP1() const;
	const Double3 &getP2() const;
	const Double3 &getP3() const;
	const Double3 &getNormal();
	const Double2 &getUV1() const;
	const Double2 &getUV2() const;
	const Double2 &getUV3() const;
	int getMaterialIndex() const;

	BoundingBox getBoundingBox() const;

	void setP1(const Double3 &p);
	void setP2(const Double3 &p);
	void setP3(const Double3 &p);
	void setUV1(const Double2 &uv);
	void setUV2(const Double2 &uv);
	void setUV3(const Double2 &uv);
	void setMaterialIndex(int index);

	void init(const Double3 &p1, const Double3 &p2, const Double3 &p3,
		const Double2 &uv1, const Double2 &uv2, const Double2 &uv3, int materialIndex);

	bool intersect(const Ray &ray, IntersectionData &intersection);
};

#endif
