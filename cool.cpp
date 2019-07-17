#include "pvm3.h"
#include <stdio.h>
#include <armadillo>
#define SIZE 100
#define NPROCS 5

main()
{
   int mytid, task_ids[NPROCS];
   int a[SIZE], results[NPROCS], sum = 0;
   int i, msgtype, num_data = SIZE/NPROCS;

   /* enroll in PVM */
   mytid = pvm_mytid();
   arma::vec test(2);
   test={1,1};


   for (i = 0; i < SIZE; i++)
      a[i] = i % 25;

   /* spawn worker tasks */
   pvm_spawn("worker", (char **)0, PvmTaskDefault, "", NPROCS, task_ids);

   /* send data to worker tasks */
   for (i = 0; i < NPROCS; i++) {
      pvm_initsend(PvmDataDefault);
      pvm_pkint(&num_data, 1, 1);
      pvm_pkint(&a[num_data*i], num_data, 1);
      pvm_send(task_ids[i], 4);
   }

   /* wait and gather results */
   msgtype = 7;
   for (i = 0; i < NPROCS; i++) {
      pvm_recv(task_ids[i], msgtype);
      pvm_upkint(&results[i], 1, 1);
      sum += results[i];
      printf("exit process %d \n",i);
   }

   printf("The sum is %d \n",sum);

   pvm_exit();
}