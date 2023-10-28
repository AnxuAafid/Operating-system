 // Race condition //

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
int shared= 1;

void *func1();
void *func2();

int main(){
pthread_t thread_1, thread_2;
pthread_create(&thread_1,NULL, func1, NULL);

pthread_create(&thread_2,NULL, func2,NULL);

pthread_join(thread_1,NULL);
pthread_join(thread_2,NULL);
printf("MAIN FUNCTIONS > The value of shared variable is %d",shared);
}
void *func1(){
int x;
x=shared;
printf("IN THREAD 1: the value of shared variable in thread 1 is %d\n",x);
x++;
printf("IN THREAD 1: locally updated value is thread1 is %d\n ", x);
sleep(2);
shared=x;
printf("IN THREAD 1: value of shared variable in thread 1 is now %d\n", shared);

}
void *func2(){
int y;
y = shared;
printf("IN THREAD 2: the value of shared variable in thread 2 is %d\n",y);
y--;

printf("IN THREAD 2: local updation by thread 2 is %d\n", y);
sleep(2);
shared=y;
printf("IN THREAD 2: the value of shared variable in thread 2 now is %d\n",shared);
}
