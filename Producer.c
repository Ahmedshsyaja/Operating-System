#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMSZ 4
int main() {
int shmid;
key_t key;
int *shm, count = 5;
key = 5678;
if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
perror("shmget");
exit(1);
}
if ((shm = shmat(shmid, NULL, 0)) == (int *) -1) {
perror("shmat");
exit(1);
}
*shm = count;
while (1) {
if (*shm < 5) {
(*shm)++;
printf("Added 1 item. Current count is %d.\n", *shm);
sleep(1);
}
}
return 0;
}
