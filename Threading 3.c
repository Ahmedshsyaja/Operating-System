



#include <iostream>
#include <pthread.h>

using namespace std;

struct Rectangle {
double length;
double width;
};

void* computeArea(void* arg) {
Rectangle* rect = (Rectangle*)arg;
double area = rect->length * rect->width;
cout << "Area: " << area << endl;
pthread_exit(NULL);
}

void* computePerimeter(void* arg) {
Rectangle* rect = (Rectangle*)arg;
double perimeter = 2 * (rect->length + rect->width);
cout << "Perimeter: " << perimeter << endl;
pthread_exit(NULL);
}

int main() {
Rectangle rect;
cout << "Enter length and width of rectangle: ";
cin >> rect.length >> rect.width;

pthread_t threads[2];

pthread_create(&threads[0], NULL, computeArea, (void*)&rect);
pthread_create(&threads[1], NULL, computePerimeter, (void*)&rect);

pthread_join(threads[0], NULL);
pthread_join(threads[1], NULL);

return 0;
}

