#include <cassert>

#include "Material.h"

Material::Material()
{
	this->width = 0;
	this->height = 0;
}

int Material::getIndex(int x, int y) const
{
	return x + (y * this->width);
}

const Material::Texel &Material::getTexel(int x, int y) const
{
	const int index = this->getIndex(x, y);
	return this->texels.at(index);
}

void Material::init(int width, int height, const uint32_t *argb)
{
	assert(width > 0);
	assert(height > 0);

	this->texels = std::vector<Texel>(width * height);
	this->width = width;
	this->height = height;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			const int index = this->getIndex(x, y);
			const uint32_t srcTexel = argb[index];
			const uint8_t r = static_cast<uint8_t>(srcTexel >> 16);
			const uint8_t g = static_cast<uint8_t>(srcTexel >> 8);
			const uint8_t b = static_cast<uint8_t>(srcTexel);
			const uint8_t a = static_cast<uint8_t>(srcTexel >> 24);

			auto u8ToDouble = [](uint8_t u)
			{
				return (static_cast<double>(u) / 255.0);
			};

			Texel &dstTexel = this->texels.at(index);
			dstTexel.r = u8ToDouble(r);
			dstTexel.g = u8ToDouble(g);
			dstTexel.b = u8ToDouble(b);
			dstTexel.transparent = a == 0;
		}
	}
}
