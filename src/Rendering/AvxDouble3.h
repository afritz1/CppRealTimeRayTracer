#ifndef RT_AVX_DOUBLE3_H
#define RT_AVX_DOUBLE3_H

#include "Avx.h"

// SIMD vector type for calculating four Double3's in parallel.

struct alignas(sizeof(__m256d)) AvxDouble3
{
	Avx xs, ys, zs;

	AvxDouble3() = default;

	AvxDouble3(Avx xs, Avx ys, Avx zs)
		: xs(xs), ys(ys), zs(zs) { }

	AvxDouble3(__m256d xs, __m256d ys, __m256d zs)
	{
		this->xs.m = xs;
		this->ys.m = ys;
		this->zs.m = zs;
	}

	static const AvxDouble3 Zero;
	static const AvxDouble3 UnitX;
	static const AvxDouble3 UnitY;
	static const AvxDouble3 UnitZ;

	AvxDouble3 operator+(const AvxDouble3 &v) const
	{
		return AvxDouble3(
			my_add_p(this->xs.m, v.xs.m),
			my_add_p(this->ys.m, v.ys.m),
			my_add_p(this->zs.m, v.zs.m));
	}

	AvxDouble3 operator-() const
	{
		const __m256d &zeroes = AvxDouble3::Zero.xs.m;
		return AvxDouble3(
			my_sub_p(zeroes, this->xs.m),
			my_sub_p(zeroes, this->ys.m),
			my_sub_p(zeroes, this->zs.m));
	}

	AvxDouble3 operator-(const AvxDouble3 &v) const
	{
		return AvxDouble3(
			my_sub_p(this->xs.m, v.xs.m),
			my_sub_p(this->ys.m, v.ys.m),
			my_sub_p(this->zs.m, v.zs.m));
	}

	AvxDouble3 operator*(__m256d scale) const
	{
		return AvxDouble3(
			my_mul_p(this->xs.m, scale),
			my_mul_p(this->ys.m, scale),
			my_mul_p(this->zs.m, scale));
	}

	AvxDouble3 operator*(const AvxDouble3 &v) const
	{
		return AvxDouble3(
			my_mul_p(this->xs.m, v.xs.m),
			my_mul_p(this->ys.m, v.ys.m),
			my_mul_p(this->zs.m, v.zs.m));
	}

	AvxDouble3 operator/(__m256d scale) const
	{
		return AvxDouble3(
			my_div_p(this->xs.m, scale),
			my_div_p(this->ys.m, scale),
			my_div_p(this->zs.m, scale));
	}

	AvxDouble3 operator/(const AvxDouble3 &v) const
	{
		return AvxDouble3(
			my_div_p(this->xs.m, v.xs.m),
			my_div_p(this->ys.m, v.ys.m),
			my_div_p(this->zs.m, v.zs.m));
	}

	// @todo: Visual Studio thinks this needs to be a constant expression?
	/*AvxDouble3 compare(const AvxDouble3 &v, const int imm8) const
	{
		return AvxDouble3(
			my_cmp_p(this->xs.m, v.xs.m, imm8),
			my_cmp_p(this->ys.m, v.ys.m, imm8),
			my_cmp_p(this->zs.m, v.zs.m, imm8));
	}*/
};

#endif
