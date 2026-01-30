#include "kmp.h"
#include <stdlib.h>

static int *compute_prefix_function(const unsigned char *pattern, int psize)
{
	if (psize <= 0)
		return NULL;

	int k = -1;
	int *pi = malloc(sizeof(int) * psize);
	if (!pi)
		return NULL;

	pi[0] = k;
	for (int i = 1; i < psize; i++) {
		while (k > -1 && pattern[k + 1] != pattern[i])
			k = pi[k];
		if (pattern[i] == pattern[k + 1])
			k++;
		pi[i] = k;
	}
	return pi;
}

size_t kmp_overlap(
	const unsigned char *target, size_t tsize,
	const unsigned char *pattern, size_t psize)
{
	if (tsize == 0 || psize == 0)
		return 0;

	int *pi = compute_prefix_function(pattern, (int)psize);
	if (!pi)
		return 0;

	int k = -1;
	for (int i = 0; i < (int)tsize; i++) {
		while (k > -1 && pattern[k + 1] != target[i])
			k = pi[k];
		if (target[i] == pattern[k + 1])
			k++;
		if (k == (int)psize - 1)
			k = pi[k];
	}

	free(pi);
	return (size_t)(k + 1);
}