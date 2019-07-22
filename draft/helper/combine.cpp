#include <iostream>
#include <sstream>
#include <mpi.h>
#include <string>
#include <armadillo>
#include "coordinate.h"
#include <vector>

#define file1 "out12001800.txt"
#define file2 "out500700.txt"
#define file3 "out8001200.txt"
const char* filename[]={"out12001800.txt","out500700.txt","out8001200.txt"};
 
void master( void) ;
 void slave(int) ;

int main(int argc, char *argv[]){
  int rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0){
      master();

  }else{

      slave(rank);

  }
  MPI_Finalize();
  exit(EXIT_SUCCESS);
}

void master(void){
    

    int size;
    MPI_Status status;
    int i;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::map<Coordinate,double> buff;
    buff.insert({{0,0},0});
    double localbuff[300000][3];


    for (i = 0; i< 3; ++i){
        //distributing data
        MPI_Send(localbuff, i, MPI_DOUBLE,i,0,MPI_COMM_WORLD);

    }
    for (i = 1; i< size; ++i){
        //collecting results
        MPI_Recv(&localbuff,1,MPI_DOUBLE,i,1, MPI_COMM_WORLD,&status);
        for(int m=0;m<300000;m++){
        buff.insert(std::pair<Coordinate,double>({localbuff[m][0],localbuff[m][1]},localbuff[m][2]));

        }

    }
    // post-process
    



}

void slave(int something){

    

    const char* localfile = filename[something];
  
    MPI_Status status;
    int i,j,rank;
    std::double_t **localbuff;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Recv(&localbuff,i,MPI_CHAR,0,0,MPI_COMM_WORLD,&status);
    //target parameter
 
    printf("hello from rank %d \n",something);
    //begin to work 
    arma::mat X;
    X.load(localfile,arma::csv_ascii);
    arma::hdf5
    X.col(0);
    for(int k=0;k<X.n_rows;k++){
    localbuff[rank*100000+k][0]=X.at(k,0);
    localbuff[rank*100000+k][1]=X.at(k,1);
    localbuff[rank*100000+k][2]=X.at(k,2);
    }
    MPI_Send(&localbuff,1,MPI_DOUBLE,0,1,MPI_COMM_WORLD);

}

  