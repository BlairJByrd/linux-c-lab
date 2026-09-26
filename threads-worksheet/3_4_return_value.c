#include <pthread.h>
#include <stdint.h>
#include <stdio.h>

void *worker(void *arg) {
    int *data = (int *) arg;
    *data = *data + 1;
    printf("Data is %d\n", *data);
    return (void *) 42;
}

int main(void) {
    int data = 0;
    void *ret;
    pthread_t thread;
    pthread_create(&thread, NULL, &worker, &data);
    pthread_join(thread, &ret);                  /* 2nd arg receives the return value */
    printf("worker returned %d\n", (int)(intptr_t) ret);
    return 0;
}
