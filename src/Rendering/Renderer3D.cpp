#include <algorithm>
#include <limits>

#include "Renderer3D.h"

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

void Renderer3D::render(uint32_t *dst)
{
	for (int y = 0; y < this->height; y++)
	{
		const double yPercent = (static_cast<double>(y) + 0.50) / static_cast<double>(this->height);

		for (int x = 0; x < this->width; x++)
		{
			const int index = x + (y * this->width);
			const double xPercent = (static_cast<double>(x) + 0.50) / static_cast<double>(this->width);

			const double r = std::min(std::max(xPercent, 0.0), 1.0);
			const double g = std::min(std::max(yPercent, 0.0), 1.0);
			const double b = std::min(std::max(1.0 - (xPercent * 0.50) - (yPercent * 0.50), 0.0), 1.0);

			const uint32_t color =
				(static_cast<uint8_t>(r * 255.0) << 16) |
				(static_cast<uint8_t>(g * 255.0) << 8) |
				(static_cast<uint8_t>(b * 255.0));

			dst[index] = color;
		}
	}
}
