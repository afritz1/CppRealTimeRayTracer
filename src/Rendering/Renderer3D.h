#ifndef RT_RENDERER3D_H
#define RT_RENDERER3D_H

#include <cstdint>
#include <vector>

class Camera;
class World;

struct IntersectionData;
struct Ray;

class Renderer3D
{
private:
	std::vector<double> depthBuffer;
	int width, height;

	// @todo: need to intersect four triangles/rectangles at a time.

	// Generates a ray from the camera through the screen at the given XY coordinate.
	static Ray generateRay(double xPercent, double yPercent, const Camera &camera);
public:
	Renderer3D();

	bool isInited() const;

	void init(int width, int height);
	void resize(int width, int height);

	// Destination buffer is in ARGB8888.
	void render(const Camera &camera, const World &world, uint32_t *dst);
};

#endif
