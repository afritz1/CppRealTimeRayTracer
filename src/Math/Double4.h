#ifndef RT_DOUBLE4_H
#define RT_DOUBLE4_H

#include <immintrin.h>

class alignas(sizeof(__m256d)) Double4
{
public:
	union
	{
		__m256d m;
		struct
		{
			double x, y, z, w;
		};
	};

	static const Double4 Zero;
	static const Double4 UnitX;
	static const Double4 UnitY;
	static const Double4 UnitZ;
	static const Double4 UnitW;

	// Don't initialize in default constructor for speed.
	Double4() = default;

	Double4(double x, double y, double z, double w)
	{
		this->m = _mm256_set_pd(w, z, y, x);
	}

	Double4(const double *ptr)
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
};

#endif
