#include <iostream>
#include <cstdio>
#include <omp.h>

#include <hdf5.h>
#include <hdf5_hl.h>
#define ARMA_USE_HDF5 0
#include <armadillo>
#define FILE        "Data.h5"
#define DATASETNAME "floatArray" 
#define NX     235000                      /* dataset dimensions */
#define NY     150
#define RANK   2
#define ARR {if( status!=1){std::cout<<" can not read data!"<<std::endl;}}
int main (int argc, char **argv)
{
     hid_t       file_id, dset_id;         /* file and dataset identifiers */
    hid_t       filespace, memspace;      /* file and memory dataspace identifiers */
    hsize_t     dimsf[2];                 /* dataset dimensions */
    double        *data;                    /* pointer to data buffer to write */
    hsize_t	count[2];	          /* hyperslab selection parameters */
    hsize_t	offset[2];
    hid_t	plist_id;                 /* property list identifier */
    int         i;
    herr_t	stat;

    int status ;
    arma::Mat<double> MT;
    data = (double *) malloc(sizeof(double)*count[0]*count[1]);
    status = MT.load("volaty.arma",arma::arma_binary);ARR
    for (int i=0;i<150;i++){
      for(int j=0;j<235000;j++){

      }
    }
    /*
     * MPI variables
     */
    int mpi_size, mpi_rank;
    MPI_Comm comm  = MPI_COMM_WORLD;
    MPI_Info info  = MPI_INFO_NULL;

    /*
     * Initialize MPI
     */
    MPI_Init(&argc, &argv);
    MPI_Comm_size(comm, &mpi_size);
    MPI_Comm_rank(comm, &mpi_rank);  
 
    /* 
     * Set up file access property list with parallel I/O access
     */
     plist_id = H5Pcreate(H5P_FILE_ACCESS);
     H5Pset_fapl_mpio(plist_id, comm, info);

    /*
     * Create a new file collectively and release property list identifier.
     */
    file_id = H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, plist_id);
    H5Pclose(plist_id);
   

    /*
     * Create the dataspace for the dataset.
     */
    dimsf[0] = NX;
    dimsf[1] = NY;
    filespace = H5Screate_simple(RANK, dimsf, NULL); 

    /*
     * Create the dataset with default properties and close filespace.
     */
    dset_id = H5Dcreate(file_id, DATASETNAME, H5T_NATIVE_INT, filespace,
			H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    H5Sclose(filespace);

    /* 
     * Each process defines dataset in memory and writes it to the hyperslab
     * in the file.
     */
    count[0] = dimsf[0]/mpi_size;
    count[1] = dimsf[1];
    offset[0] = mpi_rank * count[0];
    offset[1] = 0;
    memspace = H5Screate_simple(RANK, count, NULL);

    /*
     * Select hyperslab in the file.
     */
    filespace = H5Dget_space(dset_id);
    H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset, NULL, count, NULL);

    /*
     * Initialize data buffer 
     */
    
    for (i=0; i < NX; i++) {
        data[i] = MT.;
    }

    /*
     * Create property list for collective dataset write.
     */
    plist_id = H5Pcreate(H5P_DATASET_XFER);
    H5Pset_dxpl_mpio(plist_id, H5FD_MPIO_COLLECTIVE);
    
    stat = H5Dwrite(dset_id, H5T_IEEE_F64LE, memspace, filespace,plist_id, data);
    free(data);

    /*
     * Close/release resources.
     */
    H5Dclose(dset_id);
    H5Sclose(filespace);
    H5Sclose(memspace);
    H5Pclose(plist_id);
    H5Fclose(file_id);
 
    MPI_Finalize();

    return 0;
}     



#include "tbb/tbb.h"
#include <vector>
#include <iostream>
using namespace tbb;
using namespace std;
vector<double> record;
struct compute {
 void operator()( const blocked_range<int>& r ) const {
 for( int i=r.begin(); i!=r.end(); ++i )
    record.at(i) += 1;
     }
  };
int main() {
   record.resize(1000);
 try {
 parallel_for( blocked_range<int>(0, 2000), compute());
 } catch( captured_exception& ex ) {
 cout << "captured_exception: " << ex.what() << endl;
 } catch( out_of_range& ex ) {
 cout << "out_of_range: " << ex.what() << endl;
 }
 return 0; 


}

std::vector<std::array<int,2>> Data;
int main() {
 

 try {
   parallel_for( 0, 10, 1, []( int i ) {
      printf("i am %d \n",i);
     task_group_context root(task_group_context::isolated);
      parallel_for(i+1, 10, 1,[&]( int j ) {
        printf("the i inside %d and j %d \n",i,j);
        Data.push_back({i,j});
      },root);
 throw "oops";
 });
 } catch(...) {
 }
 return 0;
} 