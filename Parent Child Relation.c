#include <stdio.h>
#include <unistd.h>
int main() {
pid_t child_pid1, child_pid2;
child_pid1 = fork();
if (child_pid1 == 0) {
printf("Child process 1 (P1) is running, parent PID = %d\n", getppid());
} else {
child_pid2 = fork();
if (child_pid2 == 0) {
printf("Child process 2 (P2) is running, parent PID = %d\n", getppid());
} else {
printf("Parent process (P) is running, child P1 PID = %d, child P2 PID = %d\n", child_pid1,
child_pid2);
}
}
return 0;
}
