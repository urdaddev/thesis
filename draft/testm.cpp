


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <string>
#include <mpi.h>
#include <netcdf.h>
#include <netcdf_par.h>
#include <assert.h>
#define FAIL -1
const char *columnames[] = {"As", "Bs", "Cs", "Alphas_1"};
void testPread(MPI_Comm , int,int );

void idosth(MPI_Comm, int *, int *);
void jdosth(MPI_Comm, int *, int *);

int main(int, char **);

void timestamp();



int main(int argc,char *argv[]){
  const char *columnames[] = {"As", "Bs", "Cs", "Alphas_1"};
  int jid;
  int jid_sum;
  int jp;
  int *jrank;
  MPI_Group jgroup_id;
  MPI_Comm jcomm_id;
  MPI_Comm icomm_id;
  int i;
  int id;
  int ierr;
  int j;

  MPI_Group igroup_id;
  int iid;
  int iid_sum;
  int ip;
  int *irank;
  int p;
  MPI_Group world_group_id;

  ierr = MPI_Init(&argc, &argv);

  if (ierr != 0)
  {
    exit(1);
  }

  ierr = MPI_Comm_size(MPI_COMM_WORLD, &p);

  ierr = MPI_Comm_rank(MPI_COMM_WORLD, &id);

  if (id == 0)
  {
    timestamp();
    std::cout << "begin master process" << std::endl;
  }

  //  Get a group identifier for MPI_COMM_WORLD.
  MPI_Comm_group(MPI_COMM_WORLD, &world_group_id);

  //  List the even processes, and create their group.
  jp = (p + 1) / 2;
  jrank = new int[jp];
  j = 0;
  for (i = 0; i < p; i = i + 2)
  {
    jrank[j] = i;
    j = j + 1;
  }
  MPI_Group_incl(world_group_id, jp, jrank, &jgroup_id);
  MPI_Comm_create(MPI_COMM_WORLD, jgroup_id, &jcomm_id);

  //  List the odd processes, and create their group.
  ip = p / 2;
  irank = new int[ip];
  j = 0;
  for (i = 1; i < p; i = i + 2)
  {
    irank[j] = i;
    j = j + 1;
  }
  MPI_Group_incl(world_group_id, ip, irank, &igroup_id);
  MPI_Comm_create(MPI_COMM_WORLD, igroup_id, &icomm_id);

  if (id % 2 == 0)
  {
    ierr = MPI_Comm_rank(jcomm_id, &jid);
    iid = -1;
  }
  else
  {
    ierr = MPI_Comm_rank(icomm_id, &iid);
    jid = -1;
  }

  if (jid != -1)
  {

    printf("activate %d in group j \n", id);
  
    testPread(jcomm_id, id, jid);
  }
  if (jid == 0)
  {
    std::cout << "  group j exit with total " << jp << " process \n";
  }

  if (iid != -1)
  {
    printf("activate %d in group i \n", id);

    idosth(icomm_id, &id, &iid);
  }
  if (iid == 0)
  {

    std::cout << " group i exit with total process of  " << ip << "\n";
  }

  if (id == 0)
  {

    timestamp();
  }
  MPI_Barrier(MPI_COMM_WORLD);
  ierr = MPI_Finalize();
  return 0;
}

void timestamp()
{
#define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct std::tm *tm_ptr;
  std::time_t now;

  now = std::time(NULL);
  tm_ptr = std::localtime(&now);

  std::strftime(time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr);

  std::cout << time_buffer << "\n";

  return;
#undef TIME_SIZE
}

void idosth(MPI_Comm leader, int *myid, int *mygroupid)
{

  printf("process %p in group %p says hello \n", myid, mygroupid);
}

void testPread(MPI_Comm leader, int myid, int mygroupid)
{
  
#ifndef filename
#define filename "test.nc"
#endif
#ifndef NROW
#define NROW 10000
#endif
#ifndef NCOL
#define NCOL 2
#endif
#define RANK 1
  int i, j, rank, nprocs, ret;
  int ncid, ndims, ngatts, unlimited, var_ndims, var_natts;
  MPI_Offset *dim_sizes, var_size;
  int *requests, *statuses, *dimids = NULL;
  float **data;
  nc_type type;
  float *buff;
  int *reqs;

  float *buf[NROW][NCOL];
  MPI_Offset len, global_ny, global_nx, local_ny, local_nx;
  MPI_Offset start[2], count[2];
  int omode = NC_NOWRITE;
  ret = nc_open_par(filename, omode, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
  
 

  int myvar;

  if (myid == 0)
  {
    int myvar;
    ret = ncmpi_inq_varid(ncid, "As", &myvar);

    assert(ret != FAIL);
    printf("variable attribute : %s by %d  has id of %d \n", columnames[i], myid, myvar);
    }

    if(myid==1){
      int myvar;
      ret = ncmpi_inq_varid(ncid, "Bs", &myvar);
      assert(ret != FAIL);
      printf("variable attribute : %s by %d  has id of %d \n", columnames[i], myid, myvar);
    }
    
    
    
   
    //   ret = ncmpi_iget_vara_float(ncid, varid, start, count, buf[i][*myid], reqs++);
    //   assert(ret != FAIL);
  
 
    ret = ncmpi_close(ncid);
    assert(ret != FAIL);
  
}