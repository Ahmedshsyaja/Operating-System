#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;
pthread_mutex_t lock;
int Time_C,Time_B;
void *car(void *arg) {
int *id = (int *)arg;
cout<<"Car is waiting "<< *id<<endl;
pthread_mutex_lock(&lock);
sleep(Time_C);
pthread_mutex_unlock(&lock);
cout<<"Car is passing "<< *id<<endl;
cout<<"Car has passed "<< *id<<endl;
pthread_exit(NULL);
}
void *boat(void *arg) {
int *id = (int *)arg;
cout<<"Boat is waiting "<< *id<<endl;
pthread_mutex_lock(&lock);
sleep(Time_B);
cout<<"Boat is passing "<< *id<<endl;
pthread_mutex_unlock(&lock);
cout<<"Boat has passed "<< *id<<endl;
pthread_exit(NULL);
}
int main(){
int N_C,N_B;
cout<<"Enter The Number of The Cars \n";
cin>>N_C;
cout<<"Enter the Number of the Boats \n";
cin>>N_B;
cout<<"Enter the Time of the Cars \n";
cin>>Time_C;
cout<<"Enter The Time of The Boats\n";
cin>>Time_B;
pthread_t threads[N_C+N_B];
int *id = new int;
int i=0;
pthread_mutex_init(&lock, NULL);
for(int i=0;i<N_C;i++){
*id=i+1;
pthread_create(&threads[i], NULL, car, (void *)id);
}
for (i = 0; i < N_B; i++) {
*id = i+1;
pthread_create(&threads[i+N_C], NULL, boat, (void *)id);
}
for (i = 0; i < N_B + N_C; i++) {
pthread_join(threads[i], NULL);
}
};

