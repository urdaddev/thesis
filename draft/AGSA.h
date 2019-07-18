#include <iostream>
#include <cstdlib>
#include <ctime>
#include <hdf5.h>
#include <hdf5_hl.h>
#include <vector>
#include <omp.h>
#include <netcdf.h>
#include <mpi.h>
#include <pnetcdf.h>
#include <assert.h>
#ifndef AGSA_H
#define AGSA_H



namespace AGSA {
	void testRead(void);
	void testPread(int*);
    
}




#endif