#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> 
using namespace std;
int count=0;
const int NUM_PHILOSOPHERS = 5;  
pthread_t philosophers[NUM_PHILOSOPHERS];  
sem_t forks[NUM_PHILOSOPHERS];  
void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;
    while (true) {
        cout << "Philosopher " << id << " is thinking.\n";
        sleep(rand() % 3 + 1); 
        cout << "Philosopher " << id << " is hungry and wants to eat.\n";
        sem_wait(&forks[left_fork]);
        cout << "Philosopher " << id << " acquired left fork " << left_fork << ".\n";
        sem_wait(&forks[right_fork]);
        cout << "Philosopher " << id << " acquired right fork " << right_fork << ".\n";
        cout << "Philosopher " << id << " is eating.\n";
        count++;
        sleep(rand() % 3 + 1);  
        sem_post(&forks[right_fork]);
        cout << "Philosopher " << id << " released right fork " << right_fork << ".\n";
        sem_post(&forks[left_fork]);
        cout << "Philosopher " << id << " released left fork " << left_fork << ".\n";
    }
    return NULL;
}

int main() {
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }
    int ids[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}

 