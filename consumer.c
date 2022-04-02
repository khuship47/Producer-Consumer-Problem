#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include <unistd.h>

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
   int shmid, num;
   struct shmseg *shmpt;

   shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
   if (shmid == -1) {
      perror("Shared memory");
      return 1;
   }

// Attach to the segment to get a pointer to it.
  
   shmpt = shmat(shmid, NULL, 0);
   if (shmpt == (void *) -1) {
      perror("Shared memory attach");
      return 1;
   }
   
   struct item consumed_next;
   
   for (num = 0; num < 20; num++) {
       while (shmpt->in == shmpt->out) {
            printf("Waiting products to be produced\n");
            sleep(1);
            continue;
       }

       consumed_next = shmpt->buffer[shmpt->out];
       shmpt->out = (shmpt->out + 1) % BUF_SIZE;
       sleep(1);
       printf("Consumed product id: %d\n", consumed_next.id_num);
   }

   if (shmdt(shmpt) == -1) {
      perror("shmdt");
      return 1;
   }
   return 0;
}
