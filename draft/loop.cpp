#include <iostream>
#include <omp.h>
#include <armadillo>

int main(){

  arma::mat X(5, 5, arma::fill::randu);
  std::cout<<X<<std::endl;
  double sum;
  
  #pragma omp parallel for collapse(2) shared(X) reduction(+:sum)
    for (arma::uword i=0; i<5; i++ ){
      for (arma::uword j=0; j<5; j++ ){
           std::cout<<"hello";   
           sum+=arma::dot(X.row(j),X.row(j))+arma::dot(X.row(i),X.row(i))+2*arma::dot(X.row(j),X.row(i));
      }
    }

   std::cout<<sum<<std::endl;
  
             
   return 0;
      
} 
