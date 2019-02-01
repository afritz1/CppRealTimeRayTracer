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

	Avx lengthSquared() const
	{
		const __m256d xsSqr = my_mul_p(this->xs.m, this->xs.m);
		const __m256d ysSqr = my_mul_p(this->ys.m, this->ys.m);
		const __m256d zsSqr = my_mul_p(this->zs.m, this->zs.m);
		return Avx(my_add_p(xsSqr, my_add_p(ysSqr, zsSqr)));
	}

	Avx length() const
	{
		return my_sqrt_p(this->lengthSquared().m);
	}

	AvxDouble3 normalized() const
	{
		const Avx lenRecip = my_div_p(my_set1_p(1.0), this->length().m);
		return AvxDouble3(
			my_mul_p(this->xs.m, lenRecip.m),
			my_mul_p(this->ys.m, lenRecip.m),
			my_mul_p(this->zs.m, lenRecip.m));
	}

	// @todo: do abs() in AVX instructions.
	/*bool isNormalized() const
	{
		return std::abs(1.0 - this->lengthSquared()) < Constants::Epsilon;
	}*/

	Avx dot(const AvxDouble3 &v) const
	{
		const __m256d xsMult = my_mul_p(this->xs.m, v.xs.m);
		const __m256d ysMult = my_mul_p(this->ys.m, v.ys.m);
		const __m256d zsMult = my_mul_p(this->zs.m, v.zs.m);
		return Avx(my_add_p(xsMult, my_add_p(ysMult, zsMult)));
	}

	AvxDouble3 cross(const AvxDouble3 &v) const
	{
		const __m256d x1 = my_mul_p(this->ys.m, v.zs.m);
		const __m256d x2 = my_mul_p(v.ys.m, this->zs.m);
		const __m256d y1 = my_mul_p(v.xs.m, this->zs.m);
		const __m256d y2 = my_mul_p(this->xs.m, v.zs.m);
		const __m256d z1 = my_mul_p(this->xs.m, v.ys.m);
		const __m256d z2 = my_mul_p(v.xs.m, this->ys.m);
		return AvxDouble3(my_sub_p(x1, x2), my_sub_p(y1, y2), my_sub_p(z1, z2));
	}

	AvxDouble3 lerp(const AvxDouble3 &end, Avx percent) const
	{
		const AvxDouble3 diff(
			my_sub_p(end.xs.m, this->xs.m),
			my_sub_p(end.ys.m, this->ys.m),
			my_sub_p(end.zs.m, this->zs.m));
		return AvxDouble3(
			my_add_p(this->xs.m, my_mul_p(diff.xs.m, percent.m)),
			my_add_p(this->ys.m, my_mul_p(diff.ys.m, percent.m)),
			my_add_p(this->zs.m, my_mul_p(diff.zs.m, percent.m)));
	}

	AvxDouble3 clamped(Avx low, Avx high) const
	{
		const AvxDouble3 mins(
			my_min_p(this->xs.m, high.m),
			my_min_p(this->ys.m, high.m),
			my_min_p(this->zs.m, high.m));
		return AvxDouble3(
			my_max_p(mins.xs.m, low.m),
			my_max_p(mins.ys.m, low.m),
			my_max_p(mins.zs.m, low.m));
	}

	AvxDouble3 clamped() const
	{
		return this->clamped(my_set1_p(0.0), my_set1_p(1.0));
	}

	AvxDouble3 componentMin(const AvxDouble3 &v) const
	{
		return AvxDouble3(
			my_min_p(this->xs.m, v.xs.m),
			my_min_p(this->ys.m, v.ys.m),
			my_min_p(this->zs.m, v.zs.m));
	}

	AvxDouble3 componentMax(const AvxDouble3 &v) const
	{
		return AvxDouble3(
			my_max_p(this->xs.m, v.xs.m),
			my_max_p(this->ys.m, v.ys.m),
			my_max_p(this->zs.m, v.zs.m));
	}
};

#endif
