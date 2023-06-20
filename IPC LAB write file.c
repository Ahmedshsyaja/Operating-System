#include<iostream>
#include<cstring>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
using namespace std;
#define MAX_BUF 1024
int main(void)
{
char s[300];
string f;
int num, fd;
mkfifo("myfifo" , 0666);
cout<<"waiting for readers...\n";
fd = open("myfifo", O_WRONLY); //blocked
cout<<"got a reader--type some stuff\n";
int i=0;
while(1){
cin>>f;
if(f=="exit"){
break;
}
else{
f=f+"\n";
int k=0;
while(k!=f.length()){
s[i]=f[k];
i=i+1;
k=k+1;
}
s[i]='\n';
}
}
write(fd, s, sizeof(s));
close(fd);
unlink("myfifo");

return 0;
}
