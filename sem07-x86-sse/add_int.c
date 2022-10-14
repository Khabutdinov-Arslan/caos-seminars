#include <stdio.h>
#include <stdlib.h>

#include <immintrin.h>

int main(){
	const size_t n = 8;
	float *a = aligned_alloc(32, 32 * n);
	float *b = aligned_alloc(32, 32 * n);
	float *c = aligned_alloc(32, 32 * n);
	for (int i = 0; i < n; i++){
		a[i] = i + 1;
		b[i] = 2 * (i + 1);
	}
	for (int i = 0; i < n; i+= 8) {
        __m256 r1 = _mm256_load_ps((const float*)&a[i]);
        __m256 r2 = _mm256_load_ps((const float*)&b[i]);
        __m256 r3 = _mm256_add_ps(r1, r2);
        _mm256_store_ps(&c[i], r3);
    }
	for (int i = 0; i < n; i++) {
		printf("%f ", c[i]);
	}
	printf("\n");
	return 0;
}
