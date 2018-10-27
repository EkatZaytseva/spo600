#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "vol.h"

int main() {

	// Allocate memory for large in and out arrays
	int16_t*	in;
	int16_t*	out;
	int16_t*	table;
	in = (int16_t*) calloc(SAMPLES, sizeof(int16_t));
	out = (int16_t*) calloc(SAMPLES, sizeof(int16_t));
	table = (int16_t*) calloc(65536, sizeof(int16_t));

	int		x;
	int		ttl;

	// Seed the pseudo-random number generator
	srand(-1);

	// Fill the array with random data
	for (x = 0; x < SAMPLES; x++) {
		in[x] = (rand()%65536)-32768;
	}

	// Populate the lookup table
	for (int i = -32768; i < 32768; i++) {
		table[i + 32768] = (int16_t)(i * 0.75);
	}

	// ######################################
	// This is the interesting part!
	// Scale the volume of all of the samples
	for (x = 0; x < SAMPLES; x++) {
		out[x] = table[in[x] + 32768];
		if (x == 1 || x == 100 || x == 32768 || x == 65536) {
			printf("x=%d, in[x]=%d, out[x]=%d\n", x, in[x], out[x]);
		}
	}
	// ######################################

	// Sum up the data
	for (x = 0; x < SAMPLES; x++) {
		ttl = (ttl+out[x])%1000;
	}

	// Print the sum
	printf("Result: %d\n", ttl);

	return 0;

}

