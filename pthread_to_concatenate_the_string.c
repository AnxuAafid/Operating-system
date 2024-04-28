// Question: Write a program using pthread to concatenate the strings, where multiple strings are passed to thread function.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *concatenate_strings(void *arg) {
    char *str = (char *)arg;
    printf("Thread received: %s\n", str);
    // Perform string concatenation logic here
    // ...
    return NULL;
}

int main() {
    pthread_t threads[3];
    char *strings[] = {"Hello, ", "world!", " How are you?"};

    for (int i = 0; i < 3; ++i) {
        pthread_create(&threads[i], NULL, concatenate_strings, (void *)strings[i]);
    }

    for (int i = 0; i < 3; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Combine the concatenated strings
    // ...

    return 0;
}
