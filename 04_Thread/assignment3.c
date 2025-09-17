//LESSON 4 - ASSIGNMENT 3
 
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define MAIN_THREAD         "[MAIN]"
#define PRODUCER_THREAD     "[PRODUCER]"
#define CONSUMER_THREAD     "[CONSUMER]"

#define PRODUCER_ID  1
#define CONSUMER_ID  2
 
#define LOOP_TIMES  10

pthread_mutex_t mMx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mCv = PTHREAD_COND_INITIALIZER;
int shared_data = 0;
int shared_data_ready = 0;

void* producer_function() {
    char* threads_label = PRODUCER_THREAD;

    srand(time(NULL));

    printf("%s Start thread... TID: %ld\n", threads_label, (unsigned long)pthread_self());
    
    int i = 0;
    while (i < LOOP_TIMES) {
        pthread_mutex_lock(&mMx);
        shared_data = rand();
        shared_data_ready = 1;
        printf("%s Produced data: %d\n", threads_label, shared_data);
        pthread_cond_signal(&mCv);
        pthread_mutex_unlock(&mMx);
        sleep(1);
        i++;
    }
    
    printf("%s End thread. TID: %ld\n", threads_label, (unsigned long)pthread_self());
}

void* consumer_function() {
    char* threads_label = CONSUMER_THREAD;
    
    printf("%s Start thread... TID: %ld\n", threads_label, (unsigned long)pthread_self());

    int i = 0;
    while (i < LOOP_TIMES) {
        pthread_mutex_lock(&mMx);
        while (!shared_data_ready) {
            printf("%s Waiting for productions...\n", threads_label);
            pthread_cond_wait(&mCv, &mMx);
        }
        printf("%s Production is ready: %d\n", threads_label, shared_data);
        shared_data_ready = 0;
        pthread_mutex_unlock(&mMx);
        i++;
    }
    printf("%s End thread. TID: %ld\n", threads_label, (unsigned long)pthread_self());
}
 
int main() {;
    char* threads_label;
    threads_label = MAIN_THREAD;
   
    pthread_t producerId;
    pthread_t consumerId;
 
    printf("%s Create produder thread.\n", threads_label);
    pthread_create(&producerId, NULL, producer_function, NULL); 
    
    printf("%s Create consumer thread.\n", threads_label);
    pthread_create(&consumerId, NULL, consumer_function, NULL); 
    
    pthread_join(producerId, NULL);
    pthread_join(consumerId, NULL);
 
    return 0;
}