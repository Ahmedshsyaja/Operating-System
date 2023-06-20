
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
pid_t pid1, pid2;
int status1, status2;
pid1 = fork();
if (pid1 == 0) {
printf("Child process 1 started and parent is %d\n",getppid());
printf("Child process 1 finished\n");
return 0;
}else {
pid2=fork();
if(pid2==0){
printf("Child process 2 started\n");
for(int i=0;i<2;i++){
sleep(2);
}
printf("Child process 2 finished and parent is %d\n",getppid());
printf("i am now orphan\n");
}

else{
while(pid1!=wait(NULL)){
}
printf("Parent Executed and my id is %d\n",getpid());
}
return 0;
}
return 0;
}

