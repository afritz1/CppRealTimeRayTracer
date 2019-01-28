#ifndef RT_MATERIAL_H
#define RT_MATERIAL_H

#include <cstdint>
#include <vector>

class Material
{
public:
	struct Texel
	{
		double r, g, b;
		bool transparent;
	};
private:
	std::vector<Texel> texels;
	int width, height;

	int getIndex(int x, int y) const;
public:
	Material();

	const Texel &getTexel(int x, int y) const;

	void init(int width, int height, const uint32_t *argb);
};

#endif
