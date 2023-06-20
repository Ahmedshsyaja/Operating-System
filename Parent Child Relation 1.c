
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;
int main() {
pid_t p1, p2;
int status;
p1 = fork();
if (p1 == 0) {
cout << "I am P1 (PID " << getpid() << ") and my parent is P (PID " << getppid() << ")." << endl;
p2 = fork();
if (p2 == 0) {
cout << "I am P2 (PID " << getpid() << ") and my parent is P1 (PID " << getppid() << ")." <<
endl;

}
else {
wait(&status);
cout << "P1 (PID " << getpid() << ") waited for P2 (PID " << p2 << ") to finish." << endl;
}
}
else {
wait(&status);
cout << "P (PID " << getpid() << ") waited for P1 (PID " << p1 << ") to finish." << endl;
}
return 0;
}
OUTPUT

