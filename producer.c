include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include <time.h>
#include<string.h>

#define BUF_SIZE 2
#define SHM_KEY 0x1234

struct item {
    int id_num;
};

struct shmseg {
   int in;
   int out;
   struct item buffer[BUF_SIZE];
};


int main(int argc, char *argv[]) {
   time_t t;
   srand((unsigned) time(&t));
   int shmid, num;
   struct shmseg *shmpt;

   shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
   if (shmid == -1) {
      perror("Shared memory");
      return 1;
   }
   
 //Transfer blocks of data from buffer to shared memory 
 
   struct item produced_next;
   printf("\n");
  
   for (num = 0; num < 20; num++) {
        while (((shmpt->in + 1) % BUF_SIZE) == shmpt->out) {
            printf("Waiting products to be consumed\n");
            sleep(1);
            continue;
        }

        produced_next.id_num = shmpt->in;
        shmpt->buffer[shmpt->in] = produced_next;
        shmpt->in = (shmpt->in + 1) % BUF_SIZE;

        printf("Produced product id: %d\n", produced_next.id_num);
   }

   if (shmdt(shmpt) == -1) {
      perror("shmdt");
      return 1;
   }

   if (shmctl(shmid, IPC_RMID, 0) == -1) {
      perror("shmctl");
      return 1;
   }
   return 0;
}

