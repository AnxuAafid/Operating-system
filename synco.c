#include<semaphore.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void *func();
void *fun();
int shared=1;  //shared variable
sem_t s; // semaphore variable
int main(){
sem_init(&s,0,1); // ist par address of semaphore variable, shared between threads 0 means shared, initial value os semaphore

pthread_t thread1,thread2;
pthread_create(&thread1, NULL, func, NULL);
pthread_create(&thread2, NULL, fun, NULL);

pthread_join(thread1,NULL);
pthread_join(thread2, NULL);

return 0;
}
void *func(){
int x;
sem_wait(&s);
x=shared;
printf("thread1 reads %d",x);
x++;
printf("local update %d",x);
sleep(2);
shared=x;
printf("thread1 updated %d", shared);
sem_post(&s);
}
void *fun(){
int y;
sem_wait(&s);
y = shared;
printf("thread2 reads %d\n",y);
y--;
printf("local update %d\n",y);
sleep(2);
shared=y;
printf("updated is %d\n", shared);
sem_post(&s);
}
