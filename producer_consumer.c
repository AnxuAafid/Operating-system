//This program is simple program witout  using thread and this program may also get into deadlock if consumer code is executed first

//  this is the simple code to understand the things

#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
pthread_mutex_t mutex;
sem_t full; 
sem_t empty;
int x;


void consumer();
void producer();

int main(){

pthread_mutex_init(&mutex,NULL);
sem_init(&full, 0, 0);
sem_init(&empty, 0, 4);
while(1){
int choice;
printf("enter");
scanf("%d", &choice);
if(choice==1){
	producer();
	}
else if(choice==2 ){
	consumer();
	}

else{
	printf("Something went wrong");
	return 1;
	}
}
pthread_mutex_destroy(&mutex);
sem_destroy(&empty);
sem_destroy(&full);
}
void producer(){
pthread_mutex_lock(&mutex);
sem_post(&full);
sem_wait(&empty);
x++;
printf("The item produced is %d\n", x);
pthread_mutex_unlock(&mutex);
}
void consumer(){

pthread_mutex_lock(&mutex);
sem_post(&empty);
sem_wait(&full);
x--;
printf("the item produced is %d\n ",x);
pthread_mutex_unlock(&mutex);

}
