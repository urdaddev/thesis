#include <iostream>
#include <string>
#include <mpi.h>
#include <netcdf.h>
#include <netcdf_par.h>
#define NROW 10000
#define NCOL 3

#define filename "test.nc"
#define ERR                                                               \
    {                                                                     \
        if (err != NC_NOERR)                                              \
            printf("Error at line=%d: %s\n", __LINE__, nc_strerror(err)); \
    }

int main(int argc, char **argv)
{
    const char *columnames[] = { "Alphas_1", "Alphas_2","As","Bs","Cs","MeanReversionRates","VolOfVols","MeanReversionLevels","Correlations"};

    int i,j, rank, nprocs, err;
    int ncid, cmode, omode;
    int varid[2], dimid[2];
    double  buf[NROW][NCOL]={{0}};
    size_t global_NROW, global_NCOL, start[0], count[0];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    /* get command-line arguments */
   
   
    /* the global array is NROW * (NCOL * nprocs) */
    global_NROW = NROW;
    global_NCOL = NCOL * nprocs;

   

    start[0] = 0;
    count[0] = NROW;

    omode = NC_NOWRITE;
    
    err = nc_open_par(filename, omode, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
    ERR
   
    /* obtain variable ID */

   
   for(int k =0; k<NCOL;k++){
    err = nc_inq_varid(ncid, columnames[k], &varid[k]);
      ERR
    err = nc_var_par_access(ncid, varid[k], NC_COLLECTIVE);
       ERR
    printf("var %s  and varid %d and my id %d \n",columnames[k],varid[k],rank);

    err = nc_get_vara_double(ncid, varid[k], start, count, &buf[0][0]);
       ERR 
    



   }
        /* set to use MPI collective I/O */
    
     /* close the file */
     err = nc_close(ncid);
       ERR
  
    MPI_Finalize();
    int ncol=sizeof(buf)/sizeof(buf[0][0]);
    printf("%d total \n",ncol);
  for(int i=0;i<8;i++){
      for(int j=0;j<NCOL;j++){
          printf("(%d,%d) = %f \n",i,j,buf[i][j]);

      }
  }
    

    return 0;
}
