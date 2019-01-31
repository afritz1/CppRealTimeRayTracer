#ifndef RT_RAY_PACKET_H
#define RT_RAY_PACKET_H

#include "AvxDouble3.h"

// Each packet contains 4 rays; intended for calculating rays in parallel.

struct alignas(sizeof(__m256d)) RayPacket
{
	__m256d pointsX, pointsY, pointsZ;
	__m256d dirsX, dirsY, dirsZ;

	void pointsAt(__m256d ts, AvxDouble3 &dst) const
	{
		const __m256d dXs = _mm256_mul_pd(dirsX, ts);
		const __m256d dYs = _mm256_mul_pd(dirsY, ts);
		const __m256d dZs = _mm256_mul_pd(dirsZ, ts);
		dst.xs = _mm256_add_pd(pointsX, dXs);
		dst.ys = _mm256_add_pd(pointsY, dYs);
		dst.zs = _mm256_add_pd(pointsZ, dZs);
	}
};

#endif
