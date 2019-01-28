#ifndef RT_DIRECTIONAL_LIGHT_H
#define RT_DIRECTIONAL_LIGHT_H

#include "../Math/Double3.h"

class DirectionalLight
{
private:
	Double3 direction, color;
public:
	const Double3 &getDirection() const;
	const Double3 &getColor() const;

	void setDirection(const Double3 &direction);
	void setColor(const Double3 &color);

	void init(const Double3 &direction, const Double3 &color);
};

#endif
