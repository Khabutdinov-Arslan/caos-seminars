#include <limits.h>
#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>

extern double
very_important_function(int N, const float *A, const float *B, float *R);

int main(){
	const size_t n = 8;
	const size_t alig = alignof(float) * CHAR_BIT;
	const size_t sz = alig * n;
	float *a = aligned_alloc(alig , sz);
	float *b = aligned_alloc(alig, sz);
	float *c = aligned_alloc(alig, sz);
	for (int i = 0; i < n; i++){
		a[i] = i + 1;
		b[i] = 2 * (i + 1);
	}
	double res = (float)very_important_function(8, a, b, c);
	for (int i = 0; i < n; i++) {
		printf("%f ", c[i]);
	}
	printf("\n");
	return 0;
}
