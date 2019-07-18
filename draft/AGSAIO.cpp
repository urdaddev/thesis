
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <mpi.h>
#include <hdf5.h>
#include <pnetcdf.h>
#include <assert.h>
#include "AGSA.h"
void  AGSA::testRead(void) {
  #define FILE "test.nc"
  #define DATASETNAME "As"
  #define RANK 1

  #define DIM0     10000                          /* size of dataset */       
  #define DIM1     1
   hsize_t     dims[1], dimsm[1]; 
   hid_t       file_id, dataset_id; /* identifiers */
   herr_t      status; 
   int         i, j; 
   double      rdata[10000]; /* buffer for read */

   hid_t    dataspace_id, memspace_id; 

    hsize_t     count[1]; /* size of subset in the file */
    hsize_t     offset[1]; /* subset offset in the file */
    hsize_t     stride[1]; 
    hsize_t     block[1]; 

    offset[0] = 1; 
 

    count[0] = 10; 
 
    int rank; 
    stride[0] = 1; 

    block[0] = 1; 

   file_id = H5Fopen(FILE, H5F_ACC_RDONLY, H5P_DEFAULT); 
   dataset_id = H5Dopen2(file_id, DATASETNAME, H5P_DEFAULT); 
    dataspace_id = H5Dget_space (dataset_id); /* dataspace handle */
    rank = H5Sget_simple_extent_ndims (dataspace_id); 
   
    printf("\nRank: %d \n", rank); 
    dimsm[0] = 10000; 
    memspace_id = H5Screate_simple (rank, dimsm, NULL); 
    status = H5Dread(dataset_id, H5T_IEEE_F64LE, memspace_id, dataspace_id, 
                      H5P_DEFAULT, rdata); 
    for (i = 0; i < 100; i++) {

      std::cout << rdata[i] << std::endl; 
    
    }


    status = H5Sclose (memspace_id); 
    status = H5Sclose (dataspace_id); 
    status = H5Dclose (dataset_id); 
    status = H5Fclose (file_id); 
 
}

void AGSA::testPread(int &myid,double &mygroup){
    #define filename "test.nc"
    #define FAIL -1

    #ifndef NROW
      #define NROW 10000
    #endif
    #ifndef NCOL
      #define NCOL 4
    #endif
  #define FILE "test.nc"
  #define DATASETNAME "As"
  #define RANK 1

  #define DIM0     10000                          /* size of dataset */       
  #define DIM1     1
   hsize_t     dims[1], dimsm[1]; 
   hid_t       file_id, dataset_id; /* identifiers */
   herr_t      status; 
   int         i, j; 
   double      rdata[10000]; /* buffer for read */

   hid_t    dataspace_id, memspace_id; 

    hsize_t     count[1]; /* size of subset in the file */
    hsize_t     offset[1]; /* subset offset in the file */
    hsize_t     stride[1]; 
    hsize_t     block[1]; 

    offset[0] = 1; 
 

    count[0] = 10; 
 
    int rank; 
    stride[0] = 1; 

    block[0] = 1; 

   file_id = H5Fopen(FILE, H5F_ACC_RDONLY, H5P_DEFAULT); 
   dataset_id = H5Dopen2(file_id, DATASETNAME, H5P_DEFAULT); 
    dataspace_id = H5Dget_space (dataset_id); /* dataspace handle */
    rank = H5Sget_simple_extent_ndims (dataspace_id); 
   
    printf("\nRank: %d \n", rank); 
    dimsm[0] = 10000; 
    memspace_id = H5Screate_simple (rank, dimsm, NULL); 
    status = H5Dread(dataset_id, H5T_IEEE_F64LE, memspace_id, dataspace_id, 
                      H5P_DEFAULT, rdata); 
    for (i = 0; i < 100; i++) {

      std::cout << rdata[i] << std::endl; 
    
    int i, j, rank, nprocs, ret;
    int ncid, ndims, ngatts, unlimited, var_ndims, var_natts;
    MPI_Offset *dim_sizes, var_size;
    int *requests, *statuses, *dimids=NULL;
    float **data;
    char varname[NC_MAX_NAME+1];
    nc_type type;
    float *buff;
    char * columnames[]={"As","Bs","Cs","Alphas_1"};

    float *buf[NROW][4];
    MPI_Offset len, global_ny, global_nx, local_ny, local_nx;
    MPI_Offset start[2], count[2];
   
    
    ret = ncmpi_open(comm, filename, NC_NOWRITE, MPI_INFO_NULL, &ncid); 
        assert(ret!=FAIL);
   
    printf("variable attribute : %s by %d \n",columnames[myid],myid);
    int varid;
    for (int n=0;n<4;n++){
        int varid;
        ret = ncmpi_inq_varid(ncid, columnames[myid], &varid); 
        assert(ret!=FAIL);
        printf("variable attribute : %s by %d  has id of %p \n",columnames[myid],myid,varid);
    
    }

    buff = (float*) malloc(len * sizeof(float));
    ret = ncmpi_get_att_float(ncid, varid, "buff_name", buff); 
    assert(ret!=FAIL);
    free(buff);


    local_ny = global_ny;
    local_nx = global_nx / nprocs;
   
    for (i=0; i<NROW; i++)
             buf[i][myid] = 0;

   
    int num_reqs=0;
    int reqs;
    for (i=0; i<NROW; i++) {
        ret = ncmpi_iget_vara_float(ncid, varid, start, count, buf[i][myid], &reqs++);
        ret
        start[1] += nprocs;
    }
    ret = ncmpi_wait_all(ncid, num_reqs, reqs, sts);
    ret

    /* check status of all requests */
    for (i=0; i<num_reqs; i++)
        if (sts[i] != NC_NOret)
            printf("retor at line %d in %s: nonblocking write fails on request %d (%s)\n",
                   __LINE__,__FILE__,i, ncmpi_strretor(sts[i]));

    for (i=0; i<myNX; i++) {
        for (j=0; j<NY; j++)
            if (buf[i][j] != rank)
                printf("retor at line %d in %s: expect buf[%d][%d]=%d but got %d\n",
                __LINE__,__FILE__,i,j,rank,buf[i][j]);
    }

    ret = ncmpi_close(ncid);
    ret

    free(sts);
    free(reqs);
    for (i=0; i<myNX; i++) free(buf[i]);
    free(buf);

 

    ret = ncmpi_wait_all(ncfile, nvars, requests, statuses);
    assert(ret!=FAIL);

    /* check status of each nonblocking call */
    for (i=0; i<nvars; i++)
     assert(ret!=FAIL);
    for (i=0; i<nvars; i++) {
        if (data[i] != NULL) free(data[i]);
    }
    free(data);
    free(dim_sizes);
    free(requests);
    free(statuses);

    ret = ncmpi_close(ncfile);
      assert(ret!=FAIL);

   

}