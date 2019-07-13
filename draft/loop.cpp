#include <armadillo>
#include <iostream>
#include <omp.h>

double caltotal(const arma::mat &X) {

  double sum;
  const int N = X.n_rows;

  #pragma omp parallel for collapse(2) shared(X) reduction(+:sum) num_threads(3)
  for (arma::uword i = 0; i < N; i++) {
    for (arma::uword j = 0; j < N; j++) {
       printf("i is %llu and j is %llu\n",i,j);
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
}
