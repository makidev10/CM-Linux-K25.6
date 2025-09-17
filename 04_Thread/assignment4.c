//LESSON 4 - ASSIGNMENT 4
 
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define MAIN_THREAD         "[MAIN]"
#define WRITE_THREAD        "[WRITE]"
#define READ1_THREAD        "[READ1]"
#define READ2_THREAD        "[READ2]"
#define READ3_THREAD        "[READ3]"
#define READ4_THREAD        "[READ4]"
#define READ5_THREAD        "[READ5]"

#define WRITE_ID  0
#define READ1_ID  1
#define READ2_ID  2
#define READ3_ID  3
#define READ4_ID  4
#define READ5_ID  5

void* write_function() {
    char* threads_label = WRITE_THREAD;
    printf("%s Start thread... TID: %ld\n", threads_label, (unsigned long)pthread_self());
    
    
    
    printf("%s End thread. TID: %ld\n", threads_label, (unsigned long)pthread_self());
}

void* read_function(void* arg) {
    int id = *(int*)(arg);
    char* threads_label = "";
    switch(id) {
        case 1: threads_label = READ1_THREAD; break;
        case 2: threads_label = READ2_THREAD; break;
        case 3: threads_label = READ3_THREAD; break;
        case 4: threads_label = READ4_THREAD; break;
        case 5: threads_label = READ5_THREAD; break;
    }
    
    printf("%s Start thread... TID: %ld\n", threads_label, (unsigned long)pthread_self());

    printf("%s End thread. TID: %ld\n", threads_label, (unsigned long)pthread_self());
}
 
int main() {;
    char* threads_label;
    threads_label = MAIN_THREAD;
   
    pthread_t writeId;
    pthread_t readId;
 
    printf("%s Create write thread.\n", threads_label);
    pthread_create(&writeId, NULL, write_function, NULL); 

    printf("%s Create read threads.\n", threads_label);

    for (int i = 0; i < 5; i++) {
        int arg = i + 1;
        pthread_create(&readId, NULL, read_function, (void*)&arg); 
        pthread_join(readId, NULL);
    }

    pthread_join(writeId, NULL);

    return 0;
}