#ifndef RT_RAY_PACKET_H
#define RT_RAY_PACKET_H

#include <array>

// Each packet contains NxN rays; intended for calculating rays in parallel.

struct alignas(32) RayPacket
{
	static constexpr int N = 2;
	static constexpr int COUNT = N * N;

	std::array<double, COUNT> pointsX, pointsY, pointsZ;
	std::array<double, COUNT> directionsX, directionsY, directionsZ;
};

#endif
