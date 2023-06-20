
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
int bridges,count1=0,count2=0,MAX_CAR=3,MAX_BOAT=2;
void* carThread(void* arg) {
   int id = *(int*)arg;
    if(count1<MAX_CAR){
    cout << "Car " << id << " is waiting to cross the bridge." << endl;
    sem_wait(&carQueue); 
    count1++;
    sem_wait(&bridge); 
    cout << "Car " << id << " is crossing the bridge." << endl;
    sleep(carTime);
    cout << "Car " << id << " has crossed the bridge." << endl;
    sem_post(&bridge);
    sem_post(&carQueue);
   
    }
     pthread_exit(NULL);
}


void* boatThread(void* arg) {
    int id = *(int*)arg;
    if(count2<MAX_BOAT){
    cout << "Boat " << id << " is waiting to cross the bridge." << endl;
    sem_wait(&boatQueue); 
    count2++;
    sem_wait(&bridge); 
    cout << "Boat " << id << " is crossing the bridge." << endl;
    sleep(boatTime);
    cout << "Boat " << id << " has crossed the bridge." << endl;
    sem_post(&bridge); 
    sem_post(&boatQueue); 
    }
    pthread_exit(NULL);
}

int main() {
    int max=2;
    cout<<"Enter the Number of the Cars To Pass Through The Bridge:"<<endl;
    cin>>numCars;
    cout<<"Enter the Number of the Boats To Pass Through The Bridge:"<<endl;
    cin>>numBoats;
    cout << "Enter the time (in seconds) needed for a car to cross the bridge: "<<endl;
    cin >> carTime;
    cout << "Enter the time (in seconds) needed for a boat to cross the bridge: "<<endl;
    cin >> boatTime;
    
    sem_init(&bridge, 0, max); 
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

