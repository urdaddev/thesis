#include <iostream>
#include <cmath>
#include <stdio.h>
#include <omp.h>
#include <float.h>
#include <armadillo>
typedef float ycords[100];
struct record{
  arma::rowvec x[10];
  arma::rowvec y[100];
  int index;

};



static void calc_distance_array(const arma::Mat<double> &bigvec, arma::colvec *box)
{
   const int N=bigvec.n_rows;
  const int K=bigvec.n_cols;

  int i,j;
  double dx[K]={0};
  int index=N*(N-1)/2;
#pragma omp parallel for reduction(-:index) shared(i,box,bigvec) default(none) 
  for (i=0;i<N;i++){
    for (int j=i+1; j<N; j++) {
      int id = omp_get_thread_num(); 
      printf("index : %d \n",id);
      int locali=index--;
       box[locali]=arma::dot(bigvec.row(i)-bigvec.row(j),bigvec.row(i)-bigvec.row(j));
        
    }
  }
}

float euclDist(const arma::mat& first, const arma::mat& second)
{
    float dist = 0;
    const double *const firstp = first.mem;
    const double *const secondp = second.mem;
#pragma omp parallel for reduction(+:dist)
    for(auto i = 0;  i < first.n_rows;  ++i) {
        auto const d = firstp[i] - secondp[i];
        dist += d * d;
    }
    return std::sqrt(dist);
}



int main(){



const arma::mat matrix=  { 
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
const int N=matrix.n_rows;
double box[45]={0};
int k=0;
#pragma omg distribute parallel for collapse(2) shared(k,box)
for (int i=0;i<matrix.n_rows;i++){
  for (int j=i+1;j<matrix.n_rows;j++){
    printf("(i %d , j %d k,%d)\n",i,j,k);
    int ip=k;
    box[ip]=arma::dot(matrix.row(i)-matrix.row(j),matrix.row(i)-matrix.row(j));
    printf("box %f \n",box[ip]);
    k++;
  }
}

std::cout<<box[0]<<std::endl;

return 0;
}

