#ifndef RT_DOUBLE2_H
#define RT_DOUBLE2_H

#include <cmath>
#include <emmintrin.h>

#include "Constants.h"

class alignas(sizeof(__m128d)) Double2
{
public:
	union
	{
		__m128d m;
		struct
		{
			double x, y;
		};
	};

	static const Double2 Zero;
	static const Double2 UnitX;
	static const Double2 UnitY;

	// Don't initialize in default constructor for speed.
	Double2() = default;

	Double2(double x, double y)
	{
		this->m = _mm_set_pd(y, x);
	}

	Double2(__m128d m)
	{
		_mm_store_pd(&this->x, m);
	}

	Double2(const double *ptr)
	{
		this->m = _mm_load_pd(ptr);
	}

	double *data()
	{
		return &this->x;
	}

	const double *data() const
	{
		return &this->x;
	}

	bool operator==(const Double2 &v) const
	{
		return (this->x == v.x) && (this->y == v.y);
	}

	bool operator!=(const Double2 &v) const
	{
		return (this->x != v.x) || (this->y != v.y);
	}

	Double2 operator+(const Double2 &v) const
	{
		return Double2(_mm_add_pd(this->m, v.m));
	}

	Double2 operator-() const
	{
		return Double2(_mm_sub_pd(_mm_set1_pd(0.0), this->m));
	}

	Double2 operator-(const Double2 &v) const
	{
		return Double2(_mm_sub_pd(this->m, v.m));
	}

	Double2 operator*(double scale) const
	{
		return Double2(_mm_mul_pd(this->m, _mm_set1_pd(scale)));
	}

	Double2 operator*(const Double2 &v) const
	{
		return Double2(_mm_mul_pd(this->m, v.m));
	}

	Double2 operator/(double scale) const
	{
		return Double2(_mm_div_pd(this->m, _mm_set1_pd(scale)));
	}

	Double2 operator/(const Double2 &v) const
	{
		return Double2(_mm_div_pd(this->m, v.m));
	}

	double lengthSquared() const
	{
		return (this->x * this->x) + (this->y * this->y);
	}

	double length() const
	{
		return std::sqrt(this->lengthSquared());
	}

	Double2 normalized() const
	{
		const double lenRecip = 1.0 / this->length();
		return Double2(_mm_mul_pd(this->m, _mm_set1_pd(lenRecip)));
	}

	bool isNormalized() const
	{
		return std::abs(1.0 - this->lengthSquared()) < Constants::Epsilon;
	}

	double dot(const Double2 &v) const
	{
		return (this->x * v.x) + (this->y * v.y);
	}

	Double2 lerp(const Double2 &end, double percent) const
	{
		const __m128d diff = _mm_sub_pd(end.m, this->m);
		return Double2(_mm_add_pd(this->m, _mm_mul_pd(diff, _mm_set1_pd(percent))));
	}

	Double2 leftPerp() const
	{
		return Double2(-this->y, this->x);
	}

	Double2 rightPerp() const
	{
		return Double2(this->y, -this->x);
	}
};

#endif
