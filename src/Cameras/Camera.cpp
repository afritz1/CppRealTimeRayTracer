#include <cassert>

#include "Camera.h"
#include "../Math/Quaternion.h"

Camera::Camera(const Double3 &eye, const Double3 &direction)
	: eye(eye)
{
	this->forward = direction.normalized();
	this->right = this->forward.cross(Double3::UnitY).normalized();
	this->up = this->right.cross(this->forward).normalized();
}

const Double3 &Camera::getEye() const
{
	return this->eye;
}

const Double3 &Camera::getForward() const
{
	return this->forward;
}

const Double3 &Camera::getRight() const
{
	return this->right;
}

const Double3 &Camera::getUp() const
{
	return this->up;
}

void Camera::pitch(double radians)
{
	const Quaternion q = Quaternion::fromAxisAngle(this->right, radians) *
		Quaternion(this->forward, 0.0);

	this->forward = Double3(q.x, q.y, q.z).normalized();
	this->right = this->forward.cross(Double3::UnitY).normalized();
	this->up = this->right.cross(this->forward).normalized();
}

void Camera::yaw(double radians)
{
	const Quaternion q = Quaternion::fromAxisAngle(Double3::UnitY, radians) *
		Quaternion(this->forward, 0.0);

	this->forward = Double3(q.x, q.y, q.z).normalized();
	this->right = this->forward.cross(Double3::UnitY).normalized();
	this->up = this->right.cross(this->forward).normalized();
}

void Camera::rotate(double dxRadians, double dyRadians, double pitchLimit)
{
	assert(std::isfinite(this->forward.length()));
	assert(pitchLimit >= 0.0);
	assert(pitchLimit < 90.0);

	const double lookRightRads = dxRadians;
	double lookUpRads = dyRadians;

	const double currentDec = std::acos(this->forward.normalized().y);
	const double requestedDec = currentDec - lookUpRads;

	// Clamp the range that the camera can tilt up or down to avoid breaking
	// the vector cross product at extreme angles.
	const double zenithMaxDec = (90.0 - pitchLimit) * Constants::DegToRad;
	const double zenithMinDec = (90.0 + pitchLimit) * Constants::DegToRad;

	lookUpRads = (requestedDec > zenithMinDec) ? (currentDec - zenithMinDec) :
		((requestedDec < zenithMaxDec) ? (currentDec - zenithMaxDec) : lookUpRads);

	// Only divide by zoom when sensitivity depends on field of view (which it doesn't here).
	//const double zoom = 1.0 / std::tan((fovY * 0.5) * DEG_TO_RAD);
	this->pitch(lookUpRads/* / zoom*/);
	this->yaw(-lookRightRads/* / zoom*/);
}

void Camera::lookAt(const Double3 &point)
{
	const Double3 newForward = (point - this->eye).normalized();
	const Double3 newRight = newForward.cross(Double3::UnitY).normalized();
	const Double3 newUp = newRight.cross(newForward).normalized();

	// Only accept the change if it's valid.
	if (std::isfinite(newUp.length()))
	{
		this->forward = newForward;
		this->right = newRight;
		this->up = newUp;
	}
}
