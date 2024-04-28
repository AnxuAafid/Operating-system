#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#include <semaphore.h>
#define STACKSIZE 10000
#define NUMPROCS 5
#define ROUNDS 10

sem_t dt,c1,c2,c3,c4,c5;

int child (void * philNum) {
    int* phil1 = (int *)philNum;
    int phil = *phil1;
    int i = 0 ;

    for ( ; i < ROUNDS ; i ++ ) {
        switch(phil){

            case 1:
                sem_wait(&dt);
                sem_wait(&c1);
                sem_wait(&c5);
            case 2:
                sem_wait(&dt);
                sem_wait(&c1);
                sem_wait(&c2);
            case 3:
                sem_wait(&dt);
                sem_wait(&c3);
                sem_wait(&c2);
            case 4:
                sem_wait(&dt);
                sem_wait(&c4);
                sem_wait(&c3);
            case 5:
                sem_wait(&dt);
                sem_wait(&c4);
                sem_wait(&c5);
            default:
                perror(NULL);
                exit(1);
        }

        // Start of critical section -- 
        int sleeptime = rand()%20000 ;
        if ( sleeptime > 10000 ) usleep(sleeptime) ;

        // exit protocol here
        switch(phil){

            case 1:
                sem_post(&dt);
                sem_post(&c1);
                sem_post(&c5);
            case 2:
                sem_post(&dt);
                sem_post(&c1);
                sem_post(&c2);
            case 3:
                sem_post(&dt);
                sem_post(&c3);
                sem_post(&c2);
            case 4:
                sem_post(&dt);
                sem_post(&c4);
                sem_post(&c3);
            case 5:
                sem_post(&dt);
                sem_post(&c4);
                sem_post(&c5);
            default:
                perror(NULL);
                exit(1);
        }

    }
    return 0 ;
}

int main ( int argc, char ** argv ) {
    int i, num ;
    int *pt= (int *)malloc(sizeof(int));
    void * p ;
    srand(time(NULL));
    sem_init(&c1,1,1);
    sem_init(&c2,1,1);
    sem_init(&c3,1,1);
    sem_init(&c4,1,1);
    sem_init(&c5,1,1);
    sem_init(&dt,1,4); //only 4 chopsticks can be picked up at a time. 5th one has to wait anyways as he cant eat with one chopstick
    for ( i = 0 ; i < NUMPROCS ; i ++ ) {
        p = malloc(STACKSIZE) ;
        if ( p == NULL ) {
            printf("Error allocating memory\n") ;
            exit(1) ;
        }
        *pt = i+1;

        int c = clone(child,p+STACKSIZE-1,CLONE_VM|SIGCHLD,(void *)pt,NULL) ;
        if ( c < 0 ) {
            perror(NULL) ;
            exit(1) ;
        }
    }
    for ( ; i > 0 ; i -- ) wait(NULL) ;

    return 0 ;
}
