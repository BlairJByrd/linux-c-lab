#include <pthread.h>
#include <sched.h>
#include <stdio.h>

void *helper(void *arg) {
    printf("HELPER\n");
    return NULL;
}

int main(void) {
    pthread_t thread;
    pthread_create(&thread, NULL, &helper, NULL);
    sched_yield();   /* same as pthread_yield(), which newer glibc deprecates */
    printf("MAIN\n");
    return 0;
}
