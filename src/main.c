/*
 * Implementing algorithms and playing around with stuff from this cool paper:
 *
 * Title:   Generalising the Fast Reciprocal Square Root Algorithm
 * Author:  Day, Mike
 * Year:    2023
 * DOI:     10.48550/arXiv.2307.15600
 *
 */

#include <stdint.h>
#include <stdio.h>

typedef uint32_t u32;
typedef float f32;

#define as_u32(x) (*(u32 *)&x)
#define as_f32(x) (*(f32 *)&x)

// Util stuff

void print_bits(u32 x) {
  u32 len = sizeof(u32) * 8;
  for (u32 i = 0; i < len; ++i) {
    printf("%c", x & (1 << (len - i - 1)) ? '1' : '0');
  }
}

void print_bits_examples() {
  for (f32 x = 1.0f; x < 100.0f; x += 1.0f) {
    printf("\n(binary)   ");
    print_bits(as_u32(x));
    printf("\n(f32)    %f", x);
    printf("\n(int)      %d\n", as_u32(x));
  }

  u32 x = 0x5F3759DF;
  printf("\nQuake III 'magic constant' 0x5F3759DF");
  printf("\n(binary)   ");
  print_bits(x);
  printf("\n(f32)    %f", as_f32(x));
  printf("\n(int)      %d\n", x);
}

// From the paper

f32 frsr_quake(f32 x) {
  printf("\nFRSR Quake");

  const u32 C = 0x5F3759DF;

  u32 X = as_u32(x);
  u32 Y = C - (X >> 1);
  f32 y = as_f32(Y);
  f32 result = y * (1.5f - 0.5f * x * y * y);

  printf("\n(x)             %f", x);
  printf("\n(1 / sqrt(x))   %f\n", result);

  return result;
}

f32 frsr_mon_0(f32 x) {
  printf("\nFRSR degree-0 monic");

  const u32 C = 0x5F37642F;

  u32 X = as_u32(x);
  u32 Y = C - (X >> 1);
  f32 result = as_f32(Y);

  printf("\n(x)             %f", x);
  printf("\n(1 / sqrt(x))   %f\n", result);

  return result;
}

f32 frsr_deg_0(f32 x) {
  printf("\nFRSR degree-0 polynomial");

  const u32 C = 0xBEBFFDAA;

  u32 X = as_u32(x);
  u32 Y = (C - X) >> 1;
  f32 y = as_f32(Y);
  f32 result = y * 0.79247999f;

  printf("\n(x)             %f", x);
  printf("\n(1 / sqrt(x))   %f\n", result);

  return result;
}

int main(void) {
  frsr_quake(16.0f);
  frsr_mon_0(16.0f);
  frsr_deg_0(16.0f);

  return 0;
}
