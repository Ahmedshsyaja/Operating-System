
#include<stdio.h>
#include<pthread.h>
#include <cstdlib>
#define NUM_THREADS 4

int NUM1;
int NUM2;
int NUM3;

void *Avg(void *threadid) {
int tid;
tid = (long)threadid;
printf("Hello World! It's me, thread :: %d\n", tid);
int AVG = NUM1 + NUM2 + NUM3 / 3;
printf("The Avg is :: %d\n", AVG);
pthread_exit(NULL);
}

void *Max(void *threadid) {
int tid;
tid = (long)threadid;
printf("Hello World! It's me, thread :: %d\n", tid);
if(NUM1 > NUM2 && NUM1 > NUM3) {
printf("NUM1 is Greatest\n");
}
else if(NUM2 > NUM1 && NUM2 > NUM3) {
printf("NUM 2 is Greatest\n");
}
else {
printf("NUM3 is Greates\n");
}
pthread_exit(NULL);
}

void *Min(void *threadid) {
int tid;
tid = (long)threadid;
printf("Hello World! It's me, thread :: %d\n", tid);
if(NUM1 < NUM2 && NUM1 < NUM3) {
printf("NUM1 is Smallest\n");
}
else if(NUM2 < NUM1 && NUM2 < NUM3) {
printf("NUM 2 is Smallest\n");
}
else {
printf("NUM3 is Smallest\n");
}
pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
pthread_t threads[NUM_THREADS];
int rc, t;
printf("Enter NUM1 ");
scanf("%d", &NUM1);
printf("Enter NUM2 ");
scanf("%d", &NUM2);
printf("Enter NUM3 ");
scanf("%d", &NUM3);
for (t = 0; t < NUM_THREADS; t++) {
if(t == 0) {
pthread_create(&threads[t], NULL, Avg, (void*)0);
}
if(t == 1) {
pthread_create(&threads[t], NULL, Max, (void*)1);
}
if(t == 2) {
pthread_create(&threads[t], NULL, Min, (void*)2);
}
if (rc) {
printf("ERROR code is %d\n", rc);
exit(1);
}
}
return 0;
}













