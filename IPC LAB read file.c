#include<iostream>
#include<cstring>
#include<unistd.h>
#include<fcntl.h>
#define MAX_BUF 1024
using namespace std;
int main(){
int fd;
char buf[MAX_BUF];
fd = open("myfifo", O_RDONLY);
read(fd, buf, MAX_BUF);
cout<<buf;
close(fd);
return 0;
}
