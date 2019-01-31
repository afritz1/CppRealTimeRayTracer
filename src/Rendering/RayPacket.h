#ifndef RT_RAY_PACKET_H
#define RT_RAY_PACKET_H

#include "AvxDouble3.h"

// Each packet contains 4 rays; intended for calculating rays in parallel.

struct alignas(sizeof(__m256d)) RayPacket
{
	AvxDouble3 points;
	AvxDouble3 dirs;

	AvxDouble3 pointsAt(__m256d ts) const
	{
		return this->points + (this->dirs * ts);
	}

	void init(const AvxDouble3 &points, const AvxDouble3 &dirs)
	{
		this->points = points;
		this->dirs = dirs;
	}
};

#endif
