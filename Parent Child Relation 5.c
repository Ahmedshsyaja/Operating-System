
#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/wait.h>
int main() {
pid_t pid1, pid2;
int status1, status2;
pid1 = fork();
if (pid1 == 0) {
printf("Child process 1 started and parent is %d\n",getppid());
execl("./exampl","./exampl","-1",NULL);
return 0;
}else {
printf("Parent Executed and my id From Q6.cpp is %d\n",getpid());
return 0;
}
return 0;
}
example from example .c
#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/wait.h>
int main() {
printf("Hellow form example.c \n");
}