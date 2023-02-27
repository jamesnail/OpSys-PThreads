#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int shared_resource = 0;
int x = 4; // threads
int y = 10000; // iterations
bool lock = 0; // TAS lock

bool TestAndSet(bool target){
    bool rv = target;
    target = true;
    return rv;
}

void *print_hello_world(void *tid){
    int counter;
    while (TestAndSet(lock));
    for(counter = 0; counter < y; counter++){
        shared_resource++;
    }
    lock = false;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    // Get X threads for Y iterations
    if(argc > 1){
        // if we have at least 1 argument...
        if(argc > 3){
            // if we have at least 2 arguments...
            // compare & assign
            if(strcmp(argv[1], "-x") == 0){
                x = atoi(argv[2]);
                y = atoi(argv[4]);
            } else {
                x = atoi(argv[4]);
                y = atoi(argv[2]);
            }
        } else {
            // check for X or Y and assign appropriately
            if(strcmp(argv[1], "-x") == 0){
                x = atoi(argv[2]);
            } else {
                y = atoi(argv[2]);
            }
        }
    }
    pthread_t threads[x];
    int status, i;
    printf("Threads: %d, Iterations: %d\n", x, y);
    for(i=0;i<x;i++){
        status = pthread_create(&threads[i], NULL, print_hello_world, (void *)i);
        //sleep(1); // This ensures we can actually see everything successfully run
        if(status != 0){
            printf("Oops, error is %d\n", status);
            exit(-1);
        }
    }
    for(i=0;i<x;i++){
        pthread_join(threads[i], NULL);
    }
    printf("Final computed value is: %d\n", shared_resource);
    exit(NULL);
}