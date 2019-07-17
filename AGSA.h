#ifndef AGSA_H
#define AGSA_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <hdf5.h>
#include <hdf5_hl.h>
#include <vector>
#include <omp.h>
#include <netcdf.h>
#include <pnetcdf.h>
#include <mpi.h>
#include <assert.h>


namespace AGSA {
	void testRead(void);
	void testPread(MPI_Comm , int*);
    
}




#endif