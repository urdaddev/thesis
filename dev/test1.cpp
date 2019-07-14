
#include <omp.h>
#include <iostream>

void fill_rand(const int N,double *A){
   int n=1;
   printf("i have no idea what should i do %d \n",n);

};

double Sum_array(const int N,double *A){
    double dummy=42.3;
    printf("i think a is a array %f \n",A[0]);
    return dummy;
}


int main(){ 
 
 double *A, sum, runtime;
 int numthreads;
 int flag = 0;
 int flg_tmp;
 const int N=10;

 A = (double *)malloc(N*sizeof(double));
 #pragma omp parallel sections default(none) shared(A,flag,flg_tmp) private(sum)
 {

   #pragma omp section
   { 
     fill_rand(N, A);
     #pragma omp flush
     #pragma atomic write
     flag = 1;
     #pragma omp flush (flag)
   }
   #pragma omp section
   { 
       while (1){
          #pragma omp flush(flag)
          #pragma omp atomic read
          flg_tmp= flag;
          if (flg_tmp==1) break;
        }
      #pragma omp flush
      sum = Sum_array(N, A);
   }
  
 }
}

