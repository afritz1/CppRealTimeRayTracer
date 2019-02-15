#ifndef RT_RENDERER3D_H
#define RT_RENDERER3D_H

#include <cstdint>
#include <vector>

class Camera;
class IntersectionData;
class World;

class Renderer3D
{
private:
	std::vector<double> depthBuffer;
	int width, height;

	// @todo: need to intersect four triangles/rectangles at a time.


public:
	Renderer3D();

	bool isInited() const;

	void init(int width, int height);
	void resize(int width, int height);

	// Destination buffer is in ARGB8888.
	void render(const Camera &camera, const World &world, uint32_t *dst);
};

#endif
