
#include <iostream>
#include <pthread.h>

using namespace std;

struct str {
string data;
string substring;
};

void* c(void* arg) {
str* r = (str*)arg;
int M = r->substring.length();
int N = r->data.length();
int res = 0;
for (int i = 0; i <= N - M; i++) {
int j;
for (j = 0; j < M; j++)
if (r->data[i + j] != r->substring[j])
break;
if (j == M) {
res++;
}
}
cout<<"Frequency is :: "<<res<<endl;
pthread_exit(NULL);
}
int main() {
str s;
cout << "Enter The String : ";
cin >> s.data ;
cout<<"Enter Substring : ";
cin>> s.substring;
pthread_t threads[1];
pthread_create(&threads[0], NULL, c, (void*)&s);
pthread_join(threads[0], NULL);
return 0;
}

