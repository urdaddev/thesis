
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int fib(int n) {
  int x, y;
  if (n < 2) return n;
#pragma omp task shared(x)
  x = fib(n - 1);
#pragma omp task shared(y) 
  y = fib(n - 2);
#pragma omp taskwait
  
  return x + y;
}
int main() {
  int NN = 70;
  int res;
#pragma omp parallel
  {
#pragma omp master
   res=fib(NN);
   printf("results %d \n",res);
  }
  return 0;
}
