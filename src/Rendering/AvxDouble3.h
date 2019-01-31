#ifndef RT_AVX_DOUBLE3_H
#define RT_AVX_DOUBLE3_H

#include <immintrin.h>

// SIMD vector type for calculating four Double3's in parallel.

struct alignas(sizeof(__m256d)) AvxDouble3
{
	__m256d xs, ys, zs;
};

#endif
