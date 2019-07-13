#include <iostream>
#include <omp.h>

void mian() {

  int x[10];
  int temp[10];
  int i;
  int chunk=4;
  double sum=0.0;
  for (int p = 0; p < 10; p++) {
  
  temp[p]=p;
  x[p]=p+2;
  
  
  }
  #pragma omp parallel for default(shared) private(i)\
      schedule(static,chunk) reduction(+:sum)
    for (i = 0; i < 10; i++) 
       sum=sum+(x[i]*temp[i]);
printf("final %f \n",sum);
  
 
}
