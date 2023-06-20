
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // for sleep()

using namespace std;


sem_t bridge; 
sem_t carQueue; 
sem_t boatQueue;

int numCars, numBoats;
int carTime, boatTime; 


void* carThread(void* arg) {
    int id = *(int*)arg;
    cout << "Car " << id << " is waiting to cross the bridge." << endl;
    sem_wait(&carQueue); 
    sem_wait(&bridge); 
    cout << "Car " << id << " is crossing the bridge." << endl;
    sleep(carTime); 
    cout << "Car " << id << " has crossed the bridge." << endl;
    sem_post(&bridge);
    sem_post(&carQueue);
    pthread_exit(NULL);
}


void* boatThread(void* arg) {
    int id = *(int*)arg;
    cout << "Boat " << id << " is waiting to cross the bridge." << endl;
    sem_wait(&boatQueue); 
    sem_wait(&bridge); 
    cout << "Boat " << id << " is crossing the bridge." << endl;
    sleep(boatTime); 
    cout << "Boat " << id << " has crossed the bridge." << endl;
    sem_post(&bridge); 
    sem_post(&boatQueue); 
    pthread_exit(NULL);
}

int main() {
    
    cout << "Enter the number of cars: "<<endl;
    cin >> numCars;
    cout << "Enter the number of boats: "<<endl;
    cin >> numBoats;
    cout << "Enter the time (in seconds) needed for a car to cross the bridge: "<<endl;
    cin >> carTime;
    cout << "Enter the time (in seconds) needed for a boat to cross the bridge: "<<endl;
    cin >> boatTime;

    
    sem_init(&bridge, 0, 1); 
    sem_init(&carQueue, 0, numCars); 
    sem_init(&boatQueue, 0, numBoats); 

    pthread_t carThreads[numCars];
    int carIds[numCars];
    for (int i = 0; i < numCars; i++) {
        carIds[i] = i + 1;
        pthread_create(&carThreads[i], NULL, carThread, &carIds[i]);
    }
    pthread_t boatThreads[numBoats];
    int boatIds[numBoats];
    for (int i = 0; i < numBoats; i++) {
        boatIds[i] = i + 1;
        pthread_create(&boatThreads[i], NULL, boatThread, &boatIds[i]);
    }
    for (int i = 0; i < numCars; i++) {
        pthread_join(carThreads[i],NULL);
}
for(int i=0;i<numBoats;i++){
pthread_join(boatThreads[i],NULL);
}
}


 

