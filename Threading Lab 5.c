#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 2
#define ARRAY_SIZE 10
struct ThreadArgs {
int* array;
int size;
int result;
};
void* multiply_array(void* arg) {
	struct ThreadArgs* args = (struct ThreadArgs*)arg;
	int* array = args->array;
	int size = args->size;
	int result = 1;
	for (int i = 0; i < size; i++) {
    	result *= array[i];
	}
	args->result = result;
	pthread_exit(NULL);
}
void* sum_array(void* arg) {
	struct ThreadArgs* args = (struct ThreadArgs*)arg;
	int* array = args->array;
	int size = args->size;
	int result = 0;
	for (int i = 0; i < size; i++) {
    	result += array[i];
	}
	args->result = result;
	pthread_exit(NULL);
}
int main() {
	int array[ARRAY_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	pthread_t threads[NUM_THREADS];
	struct ThreadArgs thread_args[NUM_THREADS];
	int results[NUM_THREADS];
	for (int i = 0; i < NUM_THREADS; i++) {
    	if (i == 0) {
        	thread_args[i].array = array;
        	thread_args[i].size = ARRAY_SIZE;
        	pthread_create(&threads[i], NULL, multiply_array, (void*)&thread_args[i]);
    	}
    	else {
        	thread_args[i].array = array;
        	thread_args[i].size = ARRAY_SIZE;
        	pthread_create(&threads[i], NULL, sum_array, (void*)&thread_args[i]);
    	}
	}
	for (int i = 0; i < NUM_THREADS; i++) {
    	pthread_join(threads[i], NULL);
    	results[i] = thread_args[i].result;
	}
	printf("Multiplication result: %d\n", results[0]);
	printf("Summation result: %d\n", results[1]);
	return 0;
}


