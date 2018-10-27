#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "vol.h"

// Function to scale a sound sample using a volume_factor
// in the range of 0.00 to 1.00.
static inline int16_t scale_sample(int16_t sample, int16_t  volume_factor) {
	return (int16_t) ((volume_factor * sample) >> 8);
}

int main() {

	// Allocate memory for large in and out arrays
	int16_t*	in;
	int16_t*	out;
	in = (int16_t*) calloc(SAMPLES, sizeof(int16_t));
	out = (int16_t*) calloc(SAMPLES, sizeof(int16_t));

	int		x;
	int		ttl;
	int16_t factor = 0.75 * 256;

	// Seed the pseudo-random number generator
	srand(-1);

	// Fill the array with random data
	for (x = 0; x < SAMPLES; x++) {
		in[x] = (rand()%65536)-32768;
	}

	// ######################################
	// This is the interesting part!
	// Scale the volume of all of the samples
	for (x = 0; x < SAMPLES; x++) {
		out[x] = scale_sample(in[x], factor);
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

