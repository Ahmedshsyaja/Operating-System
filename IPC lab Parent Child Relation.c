
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
using namespace std;
int main() {
int num1, num2;
int p1[2], p2[2], p3[2];
pid_t pid1, pid2, pid3;
if (pipe(p1) < 0 || pipe(p2) < 0 || pipe(p3) < 0) {
perror("pipe error");
return 1;
}
pid1 = fork();
if (pid1 < 0) {
perror("fork error");
return 1;
} else if (pid1 == 0) {
close(p1[1]);
int num1, num2;
char op;
read(p1[0], &num1, sizeof(num1));
read(p1[0], &op, sizeof(op));
read(p1[0], &num2, sizeof(num2));
int result;
if (op == '+') {
result = num1 + num2;
} else {
result = num1 - num2;
}
close(p3[0]);
write(p3[1], &result, sizeof(result));
close(p1[0]);

close(p3[1]);
exit(0);
} else {
pid2 = fork();
if (pid2 < 0) {
perror("fork error");
return 1;
} else if (pid2 == 0) {
close(p2[1]);
int num1, num2;
char op;
read(p2[0], &num1, sizeof(num1));
read(p2[0], &op, sizeof(op));
read(p2[0], &num2, sizeof(num2));
int result;
if (op == '*') {
result = num1 * num2;
} else {
result = num1 / num2;
}
close(p3[0]);
write(p3[1], &result, sizeof(result));
close(p2[0]);
close(p3[1]);
exit(0);
} else {
pid3 = fork();
if (pid3 < 0) {
perror("fork error");
return 1;
} else if (pid3 == 0) {
close(p1[0]);
close(p1[1]);
close(p2[0]);
close(p2[1]);
int result1;
read(p3[0], &result1, sizeof(result1));
int result2;
read(p3[0], &result2, sizeof(result2));
cout << "Addition/Subtraction result: " << result1 << endl;
cout << "Multiplication/Division result: " << result2 << endl;
close(p3[0]);
exit(0);
} else {
close(p1[0]);
close(p2[0]);
close(p3[1]);
cout << "Enter two numbers: ";
cin >> num1 >> num2;
char op;
cout << "Enter '+' for addition, '-' for subtraction: ";
cin >> op;
write(p1[1], &num1, sizeof(num1));
write(p1[1], &op, sizeof(op));
write(p1[1], &num2, sizeof(num2));
wait(NULL);
cout << "Enter '*' for multiplication, '/' for division: ";

cin >> op;
write(p2[1], &num1, sizeof(num1));
write(p2[1], &op, sizeof(op));
write(p2[1], &num2, sizeof(num2));
wait(NULL);
close(p1[1]);
close(p2[1]);
wait(NULL);
close(p3[0]);
exit(0);
}
}
}
return 0;
}