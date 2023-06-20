
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024
#define SHM_KEY 1234

int shm_id;
char *shm_ptr;

void* process1(void*) {
  printf("Process 1 writing to shared memory...\n");
  shm_ptr[0] = '1';
  while (shm_ptr[0] == '1') {
    usleep(100);
  }
  printf("Process 1 read from shared memory: %s\n", shm_ptr);
  return NULL;
}

void* process2(void*) {
  printf("Process 2 writing to shared memory...\n");
  shm_ptr[0] = '2';
  sprintf(shm_ptr + 1, "hello");
  while (shm_ptr[0] == '2') {
    usleep(100);
  }
  return NULL;
}

void* process3(void*) {
  printf("Process 3 writing to shared memory...\n");
  shm_ptr[0] = '3';
  sprintf(shm_ptr + 1, "memory");
  return NULL;
}

int main(int argc, char** argv) {
  shm_id = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
  if (shm_id == -1) {
    perror("shmget");
    exit(1);
  }
  shm_ptr = (char*) shmat(shm_id, NULL, 0);
  if (shm_ptr == (char*) -1) {
    perror("shmat");
    exit(1);
  }
  memset(shm_ptr, 0, SHM_SIZE);
  pthread_t thread1, thread2, thread3;
  pthread_create(&thread1, NULL, process1, NULL);
  pthread_create(&thread2, NULL, process2, NULL);
  pthread_create(&thread3, NULL, process3, NULL);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
  shmdt(shm_ptr);
  shmctl(shm_id, IPC_RMID, NULL);

  return 0;
}


 
