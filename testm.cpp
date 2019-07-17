


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <mpi.h>
#include <hdf5.h>
#include <vector>
#include <netcdf.h>
#include <assert.h>
#include "AGSA.h"

MPI_Comm jcomm_id;
MPI_Comm icomm_id;

void GroupComm(int gid,int mygroup);
void initial(void);

void Master(void);

int main ( int argc, char *argv[] );
void timestamp ( );


int main ( int argc, char *argv[] ){
  
  int jid;
  int jid_sum;
  int jp;
  int *jrank;
  MPI_Group jgroup_id;
  
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

  ierr = MPI_Init ( &argc, &argv );

  if ( ierr != 0 ){
    exit ( 1 );
  }

  
  ierr = MPI_Comm_size ( MPI_COMM_WORLD, &p );

  if(p<3){
    std::cout<<"need 3"<<std::endl;
    exit(1);
  }
  ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &id );

  if ( id == 0 ) 
  {
    timestamp ();
    std::cout<<"begin master process"<<std::endl;
  }

  //  Get a group identifier for MPI_COMM_WORLD.
  MPI_Comm_group ( MPI_COMM_WORLD, &world_group_id );

  //  List the even processes, and create their group.
  jp = ( p + 1 ) / 2;
  jrank = new int[jp];
  j = 0;
  for ( i = 0; i < p; i = i + 2 )
  {
    jrank[j] = i;
    j = j + 1;
  }
  MPI_Group_incl ( world_group_id, jp, jrank, &jgroup_id );
  MPI_Comm_create ( MPI_COMM_WORLD, jgroup_id, &jcomm_id );

   //  List the odd processes, and create their group.
  ip = p / 2;
  irank = new int[ip];
  j = 0;
  for ( i = 1; i < p; i = i + 2 ){
    irank[j] = i;
    j = j + 1;
  }
  MPI_Group_incl( world_group_id, ip, irank, &igroup_id );
  MPI_Comm_create(MPI_COMM_WORLD, igroup_id,&icomm_id );

  if ( id % 2 == 0 ){
    ierr = MPI_Comm_rank ( jcomm_id, &jid );
    iid = -1;
    }else{
    ierr = MPI_Comm_rank ( icomm_id,  &iid );
    jid = -1;
  }


  if ( jid != -1 ){

    printf("activate %d in group j \n",id);

    AGSA::testPread(jcomm_id,&id);

    MPI_Reduce( &id, &jid_sum, 1, MPI_INT, MPI_SUM, 0, jcomm_id );

       if ( jid == 0 ){
       std::cout << "  group j exit with total " << jp << " process \n";
       }

  }
 


  if ( iid != -1 ){
    printf("activate %d in group i \n",id);
    GroupComm(iid,0);
    MPI_Reduce ( &id, &iid_sum,  1, MPI_INT, MPI_SUM, 0, icomm_id );
  }
  if ( iid == 0 ){
    std::cout << " group i exit with total process of  " << ip  << "\n";
   
  }

  


  if ( id == 0 ){
   
    
    timestamp ();
    }
  ierr = MPI_Finalize ();
  return 0;
}

void timestamp ( ){
  #define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct std::tm *tm_ptr;
  std::time_t now;

  now = std::time ( NULL );
  tm_ptr = std::localtime ( &now );

  std::strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr );

  std::cout << time_buffer << "\n";

  return;
  #undef TIME_SIZE
}


void GroupComm(int gid, int mygroup){
  int myid;
  
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  printf("hello form %d in group %d \n",myid,gid);
  if(mygroup==1){
    if(myid==0) {
      #ifdef jcomm_id
      printf("found j by %d \n",myid);
      #endif
      printf("group %d leader with private id %d \n",mygroup,myid);

    }else{
       printf("group %d member with private id %d \n",mygroup,myid);

    }
    
      



  }


  

}


