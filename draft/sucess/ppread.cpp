#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdio>
#include <netcdf.h>
#include <netcdf_par.h>
#include <armadillo>
#define NROW 10000
#define NCOL 10
#define NY 10
#define NX 4

#define filename "test.nc"
#define complete {if(status==1) {printf("complete transfer %d ",1); goto fn_exit;}}
#define ERR                                                               \
    {                                                                     \
        if (err != NC_NOERR)                                              \
            printf("Error at line=%d: %s\n", __LINE__, nc_strerror(err)); \
    }

int main(int argc, char * argv[])
{
    
    int *reqs, *sts;
    int status;
    
     size_t start[1], count[1];

    int i,j, rank, nprocs, err;
    int ncid, cmode, omode;
    int varid[2], dimid[2];
   // double  buf[NROW][NCOL]={{0}};
    size_t global_NROW, global_NCOL;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

     /* the global array is NY * (NX * nprocs) */
     int GlobalNCOL;
     GlobalNCOL  = NCOL;
     int localNCOL=GlobalNCOL%nprocs;

     int myOff = localNCOL * rank;
     int myCOL  = 1;
   
     /* First, fill the entire array with zeros, using a blocking I/O.
           Every process writes a subarray of size NY * myNX */
 
  
 arma::mat temp(NROW,NCOL);


  


     
 

    omode = NC_NOWRITE;
   

    err = nc_open_par(filename, omode, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
    ERR
     nc_var_par_access(ncid,NC_GLOBAL,NC_COLLECTIVE);
    start[0] = 0;   count[0] = NROW; 
   
    ptrdiff_t strip[1];
     strip[0]=1;
    int num_reqs = 0;

  
  
    for (int k=0;k<NCOL;k++){
   // nc_var_par_access(ncid,k+1,NC_COLLECTIVE);
    nc_get_vara_double(ncid,k+1,start, count, temp.colptr(k));    
         
    }

        /* set to use MPI collective I/O */
   
     /* close the file */
     err = nc_close(ncid);
       ERR
  
    if(rank==0){
      
     
       for(int i=0;i<NCOL;i++){
           for(int j=0;j<8;j++){
              printf("(%d,%d) = %f \n",i,j,temp.at(j,i));

              }
         }
     
       status=temp.save("test.arma",arma::arma_binary,true); complete

        
     }
  fn_exit:
    MPI_Finalize();
    return 0;
}


