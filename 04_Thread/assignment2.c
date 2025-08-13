//LESSON 4 - ASSIGNMENT 2
 
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
 
#define MAIN_THREAD     "[MAIN]"
#define CHILD_THREAD_1  "[CHILD_1]"
#define CHILD_THREAD_2  "[CHILD_2]"
#define CHILD_THREAD_3  "[CHILD_3]"
 
#define THREAD1_ID  1
#define THREAD2_ID  2
#define THREAD3_ID  3
 
#define LOOP_TIMES  100000
 
long long counter = 0;
// pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER; //Init mutex statically
pthread_mutex_t mx;
 
void* child_function(void *arg) {
    char* threads_label;
 
    int* id = 0;
    if (arg != NULL) {
        id = (int*)arg;
    }
 
    switch(*id) {
        case 1: threads_label = CHILD_THREAD_1; break;
        case 2: threads_label = CHILD_THREAD_2; break;
        case 3: threads_label = CHILD_THREAD_3; break;
        default: threads_label = "[CHILD]"; break;
    }
 
    printf("%s Start thread... TID: %ld\n", threads_label, (unsigned long)pthread_self());
   
    while (counter < LOOP_TIMES) {
        pthread_mutex_lock(&mx);
        counter++;
        printf("%s Processing thread: Increase counter to %lld\n", threads_label, counter);
        pthread_mutex_unlock(&mx);
    }
 
    printf("%s End thread... TID: %ld\n", threads_label, (unsigned long)pthread_self());
}
 
int main() {
    pthread_t mainId = pthread_self();  //Start of main thread
    char* threads_label;
    threads_label = MAIN_THREAD;
   
    pthread_mutex_init(&mx, NULL);  // Init mutex dynamically
   
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
 
    printf("%s Start thread... TID: %ld\n", threads_label, (unsigned long)mainId);
 
    printf("%s Create new threads.\n", threads_label);
 
    int arg1 = THREAD1_ID;
    int arg2 = THREAD2_ID;
    int arg3 = THREAD3_ID;
 
    pthread_create(&thread1, NULL, child_function, (void*)&arg1);
    pthread_create(&thread2, NULL, child_function, (void*)&arg2);
    pthread_create(&thread3, NULL, child_function, (void*)&arg3);    
 
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
 
    printf("%s End thread... \n", threads_label);
   
    pthread_mutex_destroy(&mx);
 
    return 0;
}