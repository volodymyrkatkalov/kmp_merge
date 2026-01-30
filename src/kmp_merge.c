#include <stdio.h>
#include <stdlib.h>
#include "kmp.h"

static unsigned char *read_file(const char *path, size_t *len)
{
	FILE *f = fopen(path, "rb");
	if (!f) { perror(path); exit(1); }

	fseek(f, 0, SEEK_END);
	*len = ftell(f);
	rewind(f);

	unsigned char *buf = malloc(*len);
	if (!buf) { perror("malloc"); exit(1); }

	fread(buf, 1, *len, f);
	fclose(f);
	return buf;
}

int main(int argc, char **argv)
{
	if (argc != 3) {
		fprintf(stderr, "usage: %s A B\n", argv[0]);
		return 1;
	}

	size_t lenA, lenB;
	unsigned char *A = read_file(argv[1], &lenA);
	unsigned char *B = read_file(argv[2], &lenB);

	size_t overlap = kmp_overlap(A, lenA, B, lenB);

	fwrite(A, 1, lenA, stdout);
	fwrite(B + overlap, 1, lenB - overlap, stdout);

	free(A);
	free(B);
	return 0;
}