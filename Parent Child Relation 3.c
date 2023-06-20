
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
pid_t pid1, pid2;
int status1, status2;
pid1 = fork();
if (pid1 == 0) {
printf("Child process 1 started\n");
printf("Child process 1 finished\n");
return 0;
}else {
pid2=fork();
if(pid2==0){
printf("Child process 2 started\n");
printf("Child process 2 finished\n");
}
else{
for(int i=0;i<1;i++){
wait(NULL);
}
printf("Parent Executed\n");
}
return 0;
}
return 0;
}


