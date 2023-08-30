/**
 * Implementing algorithms from the following paper:
 *
 * Title:   Generalising the Fast Reciprocal Square Root Algorithm
 * Author:  Day, Mike
 * Year:    2023
 * DOI:     10.48550/arXiv.2307.15600
 *
 */

#include <stdio.h>

#define as_int(x) (*(int *)&x)
#define as_float(x) (*(float *)&x)

void print_bits(int x) {
    int len = sizeof(int) * 8;
    for (int i = 0; i < len; ++i) {
        printf("%c", x & (1 << (len - i - 1)) ? '1' : '0');
    }
}

void print_bits_examples() {
    for (float x = 1.0f; x < 100.0f; x += 1.0f) {
        printf("\n(binary)   ");
        print_bits(as_int(x));
        printf("\n(float)    %f", x);
        printf("\n(int)      %d\n", as_int(x));
    }

    int x = 0x5F3759DF;
    printf("\nQuake III 'magic constant' 0x5F3759DF");
    printf("\n(binary)   ");
    print_bits(x);
    printf("\n(float)    %f", as_float(x));
    printf("\n(int)      %d\n", x);
}

float frsr_quake(float x) {
    printf("\nFast Reciprocal Square Root (Quake III: Arena, 1998)");

    int X = as_int(x);
    int Y = 0x5F3759DF - (X >> 1);
    float y = as_float(Y);
    float result = y * (1.5f - 0.5f * x * y * y);

    printf("\n(x)             %f", x);
    printf("\n(1 / sqrt(x))   %f\n", result);

    return result;
}

int main(void) {
    frsr_quake(16.0f);

    return 0;
}
