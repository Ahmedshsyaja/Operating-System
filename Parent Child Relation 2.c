#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
pid_t pid = fork();
if (pid == -1) {
exit(1);
} else if (pid == 0) {
printf("Child is having ID %d\n", getpid());
printf("My Parent ID is %d\n", getppid());
} else {
printf("Parent (P) is having ID %d\n", getpid());
int status;
wait(&status);
printf("ID of P's Child is %d\n", pid);
}
return 0;
}
