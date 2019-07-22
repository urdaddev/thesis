#include "tbb/task_scheduler_init.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "tbb/scalable_allocator.h"
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <omp.h>
#include <float.h>
#include <malloc.h>
#include <tbb/scalable_allocator.h>
#include <tbb/memory_pool.h>
#include <tbb/scalable_allocator.h>
#include <armadillo>
#include <tuple>
#define NROW 235000
#define NCOL 150
#define SUCCESS {if( status==1){std::cout<<"success"<<std::endl;}}




void Foo(float things){


}

class ApplyFoo {
 float *const my_a;
public:
 void operator()( const tbb::blocked_range<size_t>& r ) const {
 float *a = my_a;
 for( size_t i=r.begin(); i!=r.end(); ++i )
 Foo(a[i]);

 }
 ApplyFoo( float a[] ) :
 my_a(a)
 {}
}; 


#pragma omp declare target

#pragma omp end declare target


void count1(const arma::mat &M , float(* Box)[3]){
   int k;
  #pragma omp distribute parallel for shared(k,Box,M)
      for (int i=0;i<10;i++){
         for (int j=i+1;j<10;j++){
            int ip=k;
            Box[ip][0]=i;
            Box[ip][1]=j;
            Box[ip][2]=rowdis(M.row(i),M.row(j));
            ++k;
       }
    }
}

void count2(int N){
#pragma omp distribute parallel for simd static(1)
for (int i = 0; i < N; i++) {
    for (int j=i+1; j<N;j++){
        
        printf("hello from %d with (%d ,%d) \n",omp_get_thread_num(),i,j);
       // #pragma omp parallel sections
       // {
         


       // }
       

    }
  }
}

struct Coordinate
{
  int x;
  int y;
 
  Coordinate(int x,int y): 
    x(x),y(y)
    {
    }
  bool operator<(const Coordinate &p2) const
  {
     
        return x<p2.x||x==p2.x&&y<p2.y;
  }
  bool operator==(const Coordinate &p2) const
  {
      if((x==p2.x&&y==p2.y)||(y==p2.x&&x==p2.y))
      {
        return true;
      }
      else
      {
         return false;
      }
      
  }
};


float rowdis(const arma::rowvec &M1,const arma::rowvec &M2){
  float sum;
  for (int i=0 ;i<M1.n_elem;i++){
           sum +=  (M1[i]-M2[i])*(M1[i]-M2[i]);

  }
  return std::sqrt(sum);



};




int main(){
  
std::ofstream outfile ("test.txt");
const int K=N*(N-1)/2;
double **outp;
std::map<Coordinate,int> mymap;

std::map<Coordinate,int,int>::iterator it;
int i;
int j;
int m;
#pragma omp parallel for schedule(static) ordered private(j) shared(i) reduction(+:m)  
for(i = 0; i < N; i++) 
  for(j=i+1;j<N;j++)
  #pragma omp atomic
    m++;
    mymap.insert(std::pair<Coordinate,int>({i,j},m));

return 0;
}


  
    
  
    

      
         
        


         
       
         


       // }
       

    }
  }

  
}

int main(){
  


 
arma::arma_rng::set_seed(1);
const arma::mat X(100,15,arma::fill::randu);
arma::mat box(100,2,arma::fill::randu); 
#define N 10
#define P 10

test2(X,box);

}