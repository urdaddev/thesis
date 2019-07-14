#include <omp.h>
#include <iostream>

float sum(float* table)
  {
    float result=0;
    #pragma omp parallel for simd reduction(+:result)
    for(int n=0; n<10; ++n) 
      result += table[n];
    return result;
  }

int main(){
  double total=0.0;
  double isum[10]={0,0,0,0,0,0,0,0,0,0};
  const double matrix[10][5] =  { 
    {0.1339, 0.9114, 0.0895, 0.2498, 0.2860},
    {0.1364, 0.4708, 0.5562, 0.2919, 0.7490}, 
    {0.4512, 0.0744, 0.7897, 0.8032, 0.4581},
    {0.0210, 0.5698, 0.2216, 0.4746, 0.3062},
    {0.3509, 0.6352, 0.4187, 0.2699, 0.3218},
    {0.1339, 0.9114, 0.0895, 0.2498, 0.2860},
    {0.1364, 0.4708, 0.5562, 0.2919, 0.7490}, 
    {0.4512, 0.0744, 0.7897, 0.8032, 0.4581},
    {0.0210, 0.5698, 0.2216, 0.4746, 0.3062},
    {0.3509, 0.6352, 0.4187, 0.2699, 0.3218}
};
double teamin=0;
double teamout;
#pragma omp target teams distribute parallel for simd map(from:teamin) map(to:teamout)
  for (int i=0; i<100;i++){
   int name=omp_get_thread_num();
   printf("name : %d with i=%d \n",name,i);
   #pragma omp ordered simd 
   #pragma target enter data(matrix[i])
   for(int j=i+1;j<100;j++){
      #pragma omp parallel sections shared(i,j)
     {
        
        #pragma omp section
       {
         if(matrix){
          printf("found matrix copy %d \n",1);
         }
        int tid=omp_get_team_num(); 
        int name=omp_get_thread_num();
        printf("inner at (%d,%d) named %d in team %d \n",i,j,name,tid);
       }
     }
   }
  
 }


 return 0;


}

