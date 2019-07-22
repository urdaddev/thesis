#include <cstdlib>
#include <ctime>
#include <iostream>
#include <mpi.h>
#include <hdf5.h>
#include "AGSA.h"

#define FILE "test.nc"
#define DATASETNAME "As"
#define RANK 1
int ProcRank;

void GroupComm(int gid, int mygroup, MPI_Comm com);
void initial(void) {}

void Master(void) {}

int main(int argc, char *argv[]);
void timestamp();

int main(int argc, char *argv[])
{

    int jid;
    int jid_sum;
    int jp;
    int *jrank;
    int i;
    int id;
    int ierr;
    int j;
    MPI_Comm icomm_id;
    MPI_Group igroup_id;
    MPI_Comm jcomm_id;
    MPI_Group jgroup_id;
    int iid;
    int iid_sum;
    int ip;
    int *irank;
    int p;
    MPI_Group world_group_id;

    ierr = MPI_Init(&argc, &argv);

    if (ierr != 0){
        exit(1);
    }

    ierr = MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (p < 3)
    {
        std::cout << "need 3" << std::endl;
        exit(1);
    }
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &id);

    if (id == 0){
       

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
        GroupComm(jid, 1, jcomm_id);
        MPI_Reduce(&id, &jid_sum, 1, MPI_INT, MPI_SUM, 0, jcomm_id);

        if (jid == 0)
        {
            std::cout << "  Number of processes in j = " << jp << "\n";
            std::cout << "  Sum of global ID's in j  = " << jid_sum << "\n";
        }
    }

    if (iid != -1)
    {
        printf("activate %d in group i \n", id);
        GroupComm(iid, 0);
        MPI_Reduce(&id, &iid_sum, 1, MPI_INT, MPI_SUM, 0, icomm_id);
    }
    if (iid == 0)
    {
        std::cout << "  Number of processes in i  = " << ip << "\n";
        std::cout << "  Sum of global ID's in i   = " << iid_sum << "\n";
    }

    ierr = MPI_Finalize();

    if (id == 0)
    {

        timestamp();
    }
    return 0;
}


void GroupComm(int gid, int mygroup)
{
    int myid;
    myid = mygroup * gid;
    AGSA::testRead();

    printf("hello form group %d \n", gid);

    if (gid == 0)
    {
        printf("group %d leader", mygroup);
    }
}



