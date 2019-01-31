#ifndef RT_AVX_H
#define RT_AVX_H

#include <immintrin.h>

struct Avx
{
	union
	{
		__m256d m;
		struct { double x, y, z, w; };
	};

	Avx() = default;

	Avx(__m256d m)
		: m(m) { }

	Avx &operator=(__m256d m)
	{
		this->m = m;
		return *this;
	}
};

// Abbreviations for AVX double vector intrinsics. It might be easy in theory to have
// an ifdef for whether to use floats or doubles, but I'm going to stick exclusively
// with doubles for simplicity.

#define my_set_p(x, y, z, w) _mm256_set_pd(w, z, y, x)
#define my_set1_p(x) _mm256_set1_pd(x)
#define my_load_p(ptr) _mm256_load_pd(ptr)
#define my_add_p(a, b) _mm256_add_pd(a, b)
#define my_sub_p(a, b) _mm256_sub_pd(a, b)
#define my_mul_p(a, b) _mm256_mul_pd(a, b)
#define my_div_p(a, b) _mm256_div_pd(a, b)
#define my_cmp_p(a, b, imm8) _mm256_cmp_pd(a, b, imm8)

#endif
