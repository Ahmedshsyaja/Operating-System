#include <iostream>
#include <pthread.h>
#include<unistd.h>
using namespace std;
pthread_mutex_t lock;
int balance = 0;
void *deposit(void *arg) {
while (true) {
pthread_mutex_lock(&lock);
balance += 100;
cout << "Deposited $100, balance is now $" << balance << std::endl;
pthread_mutex_unlock(&lock);
if (balance >= 500) {
break;
}
}
return NULL;
}
void *withdraw(void *arg) {
pthread_mutex_lock(&lock);
while (balance < 500) {
cout<<"Failed to Deposite";

balance =balance+ 100;
cout << "Deposited $100, balance is now $" << balance << std::endl;
}
balance -= 500;
cout << "Withdrawn $500, balance is now $" << balance << std::endl;
pthread_mutex_unlock(&lock);
return NULL;
}
int main() {
pthread_t t1, t2;
pthread_mutex_init(&lock, NULL);
pthread_create(&t1, NULL, deposit, NULL);
pthread_create(&t2, NULL, withdraw, NULL);
pthread_join(t1, NULL);
pthread_join(t2, NULL);
pthread_mutex_destroy(&lock);
return 0;
}

