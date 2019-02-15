#ifndef RT_CAMERA_H
#define RT_CAMERA_H

#include "../Math/Double3.h"

class Camera
{
private:
	Double3 eye, forward, right, up;

	void pitch(double radians);
	void yaw(double radians);
public:
	Camera();
	Camera(const Double3 &eye, const Double3 &direction);

	const Double3 &getEye() const;
	const Double3 &getForward() const;
	const Double3 &getRight() const;
	const Double3 &getUp() const;

	void rotate(double dxRadians, double dyRadians, double pitchLimit);
	void lookAt(const Double3 &point);
};

#endif
