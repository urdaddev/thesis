#include <armadillo>
#include <iostream>
#include <omp.h>

double caltotal(const arma::mat &X) {

  double sum;
  const int N = X.n_rows;

  #pragma omp parallel for shared(X) reduction(+:sum) num_threads(3)
  for (arma::uword i = 0; i < N; i++) {
    for (arma::uword j = i+1; j < N; j++) {
       
      sum += arma::dot(X.row(j), X.row(j)) + arma::dot(X.row(i), X.row(i)) +
             2 * arma::dot(X.row(j), X.row(i));
    }
  }
  return sum;
}

int main() {
  int t;
  omp_set_num_threads(t);
  arma::arma_rng::set_seed(1);
  arma::mat X(5, 5, arma::fill::randu);
  std::cout << X << std::endl;
  double sum = caltotal(X);
  std::cout << sum << std::endl;
  return 0;
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
    for(auto i = 0;  i < 5;  ++i) {
        auto const d = firstp[i] - secondp[i];
        dist += d * d;
    }
    return std::sqrt(dist);
}
}
