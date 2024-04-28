/*
Write a program using pthread to find the length of string, where strings are passed
to thread function.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void *find_string_length(void *arg) {
    char *str = (char *)arg;
    size_t len = strlen(str);
    printf("Length of '%s': %zu\n", str, len);
    return NULL;
}

int main() {
    pthread_t thread;
    char *myString = "Hello, world!";

    pthread_create(&thread, NULL, find_string_length, (void *)myString);
    pthread_join(thread, NULL);

    return 0;
}
