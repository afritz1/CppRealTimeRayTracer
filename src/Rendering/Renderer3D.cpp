#include <algorithm>
#include <limits>

#include "Renderer3D.h"
#include "../Cameras/Camera.h"
#include "../Math/Ray.h"
#include "../World/World.h"

Renderer3D::Renderer3D()
{
	this->width = 0;
	this->height = 0;
}

bool Renderer3D::isInited() const
{
	return (this->width > 0) && (this->height > 0);
}

void Renderer3D::init(int width, int height)
{
	const int pixelCount = width * height;
	this->depthBuffer = std::vector<double>(pixelCount, std::numeric_limits<double>::max());
	this->width = width;
	this->height = height;
}

void Renderer3D::resize(int width, int height)
{
	const int pixelCount = width * height;
	this->depthBuffer.resize(pixelCount);
	std::fill(this->depthBuffer.begin(), this->depthBuffer.end(),
		std::numeric_limits<double>::max());

	this->width = width;
	this->height = height;
}

Ray Renderer3D::generateRay(double xPercent, double yPercent, const Camera &camera)
{
	const Double3 point = camera.getEye();
	const Double3 direction = [xPercent, yPercent, &camera]()
	{
		const double rightComponent = -1.0 + (2.0 * xPercent);
		const double upComponent = 1.0 - (2.0 * yPercent);
		return (camera.getForward() + (camera.getRight() * rightComponent) +
			(camera.getUp() * upComponent)).normalized();
	}();

	Ray ray;
	ray.init(point, direction);
	return ray;
}

void Renderer3D::render(const Camera &camera, const World &world, uint32_t *dst)
{
	for (int y = 0; y < this->height; y++)
	{
		const double yPercent = (static_cast<double>(y) + 0.50) / static_cast<double>(this->height);

		for (int x = 0; x < this->width; x++)
		{
			const int index = x + (y * this->width);
			const double xPercent = (static_cast<double>(x) + 0.50) / static_cast<double>(this->width);

			Ray ray = Renderer3D::generateRay(xPercent, yPercent, camera);

			const double r = std::min(std::max(ray.direction.x, 0.0), 1.0);
			const double g = std::min(std::max(ray.direction.y, 0.0), 1.0);
			const double b = std::min(std::max(ray.direction.z, 0.0), 1.0);

			const uint32_t color =
				(static_cast<uint8_t>(r * 255.0) << 16) |
				(static_cast<uint8_t>(g * 255.0) << 8) |
				(static_cast<uint8_t>(b * 255.0));

			dst[index] = color;
		}
	}
}
