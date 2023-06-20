#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMSZ 4
int main() {
int shmid;
key_t key;
int *shm, count;
key = 5678;
if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
perror("shmget");
exit(1);
}
if ((shm = shmat(shmid, NULL, 0)) == (int *) -1) {
perror("shmat");
exit(1);

}
while (1) {
if (*shm > 0) {
(*shm)--;
printf("Removed 1 item. Current count is %d.\n", *shm);
} else {
printf("Blasted!! I knew I should have gone to T---t.\n");
}
sleep(1);
}
return 0;
}