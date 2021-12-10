// vol2.c - precalculated volume scaling table
// Chris Tyler 2017.11.29-2021.11.16 - Licensed under GPLv3.
// Modified by Joseph Chan
// For the Seneca College SPO600 Course

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "vol.h"

int main() {
    clock_t start, end;
    int             x;
    int             ttl = 0;

    // ---- Create in[] and out[] arrays
    int16_t* in;
    int16_t* out;
    in = (int16_t*)calloc(SAMPLES, sizeof(int16_t));
    out = (int16_t*)calloc(SAMPLES, sizeof(int16_t));

    static int16_t* precalc;

    // ---- Create dummy samples in in[]
    vol_createsample(in, SAMPLES);

    // ---- This is the part we're interested in!
    // ---- Scale the samples from in[], placing results in out[]
    start = clock();
    precalc = (int16_t*)calloc(65536, 2);
    if (precalc == NULL) {
        printf("malloc failed!\n");
        return 1;
    }

    for (x = -32768; x <= 32767; x++) {
        // Q: What is the purpose of the cast to unint16_t in the next line?
        precalc[(uint16_t)x] = (int16_t)((float)x * VOLUME / 100.0);
    }

    for (x = 0; x < SAMPLES; x++) {
        out[x] = precalc[(uint16_t)in[x]];
    }
    end = clock();

    for (x = 0; x < SAMPLES; x++) {
        ttl = (ttl + out[x]) % 1000;
    }

    // Print results.
    printf("=== PRECALCULATED VOLUME SCALING TABLE ===\n");
    printf("Result: %d\n", ttl);
    printf("Scaling took: %.0f microseconds\n\n", (double)(end - start) / CLOCKS_PER_SEC * 1000000);
    return 0;
}