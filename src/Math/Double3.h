#ifndef RT_DOUBLE3_H
#define RT_DOUBLE3_H

#include <cmath>
#include <immintrin.h>

#include "Constants.h"

class alignas(sizeof(__m256d)) Double3
{
public:
	union
	{
		__m256d m;
		struct
		{
			double x, y, z;
		};
	};

	static const Double3 Zero;
	static const Double3 UnitX;
	static const Double3 UnitY;
	static const Double3 UnitZ;

	// Don't initialize in default constructor for speed.
	Double3() = default;

	Double3(double x, double y, double z)
	{
		this->m = _mm256_set_pd(0.0, z, y, x);
	}

	Double3(__m256d m)
	{
		_mm256_store_pd(&this->x, m);
	}

	Double3(const double *ptr)
	{
		this->m = _mm256_load_pd(ptr);
	}

	double *data()
	{
		return &this->x;
	}

	const double *data() const
	{
		return &this->x;
	}

	bool operator==(const Double3 &v) const
	{
		return (this->x == v.x) && (this->y == v.y) && (this->z == v.z);
	}

	bool operator!=(const Double3 &v) const
	{
		return (this->x != v.x) || (this->y != v.y) || (this->z != v.z);
	}

	Double3 operator+(const Double3 &v) const
	{
		return Double3(_mm256_add_pd(this->m, v.m));
	}

	Double3 operator-() const
	{
		return Double3(_mm256_sub_pd(_mm256_set1_pd(0.0), this->m));
	}

	Double3 operator-(const Double3 &v) const
	{
		return Double3(_mm256_sub_pd(this->m, v.m));
	}

	Double3 operator*(double scale) const
	{
		return Double3(_mm256_mul_pd(this->m, _mm256_set1_pd(scale)));
	}

	Double3 operator*(const Double3 &v) const
	{
		return Double3(_mm256_mul_pd(this->m, v.m));
	}

	Double3 operator/(double scale) const
	{
		return Double3(_mm256_div_pd(this->m, _mm256_set1_pd(scale)));
	}

	Double3 operator/(const Double3 &v) const
	{
		return Double3(_mm256_div_pd(this->m, v.m));
	}

	double lengthSquared() const
	{
		return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
	}

	double length() const
	{
		return std::sqrt(this->lengthSquared());
	}

	Double3 normalized() const
	{
		const double lenRecip = 1.0 / this->length();
		return Double3(_mm256_mul_pd(this->m, _mm256_set1_pd(lenRecip)));
	}

	bool isNormalized() const
	{
		return std::abs(1.0 - this->lengthSquared()) < Constants::Epsilon;
	}

	double dot(const Double3 &v) const
	{
		return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);
	}

	Double3 cross(const Double3 &v) const
	{
		return Double3(
			(this->y * v.z) - (v.y * this->z),
			(v.x * this->z) - (this->x * v.z),
			(this->x * v.y) - (v.x * this->y));
	}

	Double3 lerp(const Double3 &end, double percent) const
	{
		const __m256d diff = _mm256_sub_pd(end.m, this->m);
		return Double3(_mm256_add_pd(this->m, _mm256_mul_pd(diff, _mm256_set1_pd(percent))));
	}

	Double3 clamped(double low, double high) const
	{
		const __m256d mins = _mm256_min_pd(this->m, _mm256_set1_pd(high));
		return Double3(_mm256_max_pd(mins, _mm256_set1_pd(low)));
	}

	Double3 clamped() const
	{
		return this->clamped(0.0, 1.0);
	}
};

#endif
