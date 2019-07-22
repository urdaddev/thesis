#include <hdf5.h>
#include <mpi.h>
#define FILE "test.nc"
#define DATASETNAME "As"
#define RANK 1

#define DIM0     10000                          /* size of dataset */       
#define DIM1     1

int  main() {
   hsize_t     dims[1], dimsm[1]; 
   hid_t       file_id, dataset_id;  /* identifiers */
   herr_t      status;
   int         i, j;
   double      rdata[10000];          /* buffer for read */

   hid_t    dataspace_id, memspace_id;

    hsize_t     count[1];              /* size of subset in the file */
    hsize_t     offset[1];             /* subset offset in the file */
    hsize_t     stride[1];
    hsize_t     block[1];

    offset[0] = 1;
 

    count[0]  = 10;  
 
    int rank;
    stride[0] = 1;

    block[0] = 1;

   file_id = H5Fopen (FILE, H5F_ACC_RDWR, H5P_DEFAULT);
   dataset_id = H5Dopen2(file_id, DATASETNAME, H5P_DEFAULT);
    dataspace_id = H5Dget_space (dataset_id);    /* dataspace handle */
    rank      = H5Sget_simple_extent_ndims (dataspace_id);
   
    printf("\nRank: %d \n",rank);
    dimsm[0]=10000;
    memspace_id = H5Screate_simple (rank, dimsm, NULL); 
    status = H5Dread (dataset_id, H5T_IEEE_F64LE, memspace_id, dataspace_id,
                      H5P_DEFAULT, rdata);
    for (i=0;i<100;i++){

      std::cout<<rdata[i]<<std::endl;
    
    }


    status = H5Sclose (memspace_id);
    status = H5Sclose (dataspace_id);
    status = H5Dclose (dataset_id);
    status = H5Fclose (file_id);
    return 0;
}
