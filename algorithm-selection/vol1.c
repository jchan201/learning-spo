// vol1.c - fixed-point volume scaling algorithm
// Chris Tyler 2017.11.29-2021.11.16 - Licensed under GPLv3.
// Modified by Joseph Chan
// For the Seneca College SPO600 Course

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "vol.h"

int16_t scale_sample(int16_t sample, int volume) {
    return ((((int32_t)sample) * ((int32_t)(32767 * volume / 100) << 1)) >> 16);
}

int main() {
    clock_t start, end;
    int             x;
    int             ttl = 0;

    // ---- Create in[] and out[] arrays
    int16_t* in;
    int16_t* out;
    in = (int16_t*)calloc(SAMPLES, sizeof(int16_t));
    out = (int16_t*)calloc(SAMPLES, sizeof(int16_t));

    // ---- Create dummy samples in in[]
    vol_createsample(in, SAMPLES);

    // ---- This is the part we're interested in!
    // ---- Scale the samples from in[], placing results in out[]
    start = clock();
    for (x = 0; x < SAMPLES; x++) {
        out[x] = scale_sample(in[x], VOLUME);
    }
    end = clock();

    // ---- This part sums the samples.
    for (x = 0; x < SAMPLES; x++) {
        ttl = (ttl + out[x]) % 1000;
    }

    // Print results.
    printf("=== FIXED-POINT VOLUME SCALING ALGORITHM ===\n");
    printf("Result: %d\n", ttl);
    printf("Scaling took: %.0f microseconds\n\n", (double)(end - start) / CLOCKS_PER_SEC * 1000000);
    return 0;
}