#ifndef KMP_H
#define KMP_H

#include <stddef.h>

size_t kmp_overlap(
	const unsigned char *target, size_t tsize,
	const unsigned char *pattern, size_t psize
);

#endif