#include <iostream>
#include <cstdio>
#include <armadillo>
#include <netcdf.h>
#include <netcdf_par.h>

int main() {
  arma::Mat<float> dh;
  dh.load("test.nc",arma::file_type::hdf5_binary);

  std::cout<<dh.head_rows(2)<<std::endl;
  std::cout<<dh.head_rows(0)<<std::endl;
  std::cout<<dh.size()<<std::endl;
  return 0;


  
 
}
