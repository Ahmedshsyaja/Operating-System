

#include <iostream>
#include <pthread.h>
#include <string>
#include <unistd.h>
using namespace std;
string message;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;
void* sender(void* arg) {
string message_to_send = "Hello, receiver!";
pthread_mutex_lock(&mutex);
message = message_to_send;
cout << "Sender: " << message_to_send << endl;
pthread_cond_signal(&cond_var);
pthread_mutex_unlock(&mutex);
return NULL;

}
void* receiver(void* arg) {
pthread_mutex_lock(&mutex);
while (message == "") {
pthread_cond_wait(&cond_var, &mutex);
}
string received_message = message;
cout << "Receiver: " << received_message << endl;
pthread_mutex_unlock(&mutex);
return NULL;
}
int main() {
pthread_t sender_thread, receiver_thread;
pthread_create(&sender_thread, NULL, sender, NULL);
pthread_create(&receiver_thread, NULL, receiver, NULL);
pthread_join(sender_thread, NULL);
pthread_join(receiver_thread, NULL);
return 0;
}