#include <stdio.h>
#include <omp.h>
long long r = 1;

int main(void) {
  r = 10;
#pragma omp target teams distribute parallel for reduction(+:r) map(tofrom:r)
  for (unsigned long long n = 0; n < 0x800000000ull; ++n)
    r += n;
  printf("r=%llX\n", r);
  return 0;
}
