//LESSON 4 - ASSIGNMENT 1
 
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
 
#define MAIN_THREAD     "[MAIN]"
#define CHILD_THREAD_1  "[CHILD_1]"
#define CHILD_THREAD_2  "[CHILD_2]"
void* child1_function(void* arg) {
    char* threads_label;
    threads_label = CHILD_THREAD_1;
 
    printf("%s Start thread... TID: %ld\n", threads_label, (unsigned long)pthread_self());
 
    for (int i = 0; i < 5; i++) {
        printf("%s Processing.\n", threads_label);
        sleep(1);
    }
 
    int* childReturn = (int*)malloc(sizeof(int));
    *childReturn = 10;
 
    printf("%s End thread. Return: %d\n", threads_label, *childReturn);
    return (void*)childReturn;    //End of child1 thread
}
 
void* child2_function(void* arg) {
    char* threads_label;
    threads_label = CHILD_THREAD_2;
 
    printf("%s Start thread... TID: %ld\n", threads_label, (unsigned long)pthread_self());
 
    for (int i = 0; i < 5; i++) {
        printf("%s Processing.\n", threads_label);
        sleep(1);
    }
 
    int* childReturn = (int*)malloc(sizeof(int));
    *childReturn = 20;
 
    printf("%s End thread. Return: %d\n", threads_label, *childReturn);
    return (void*)childReturn;    //End of child2 thread
}
 
 
int main() {
    pthread_t mainId = pthread_self();  //Start of main thread
    pthread_t childId1;
    pthread_t childId2;
    char* threads_label;
 
    threads_label = MAIN_THREAD;
    printf("%s Start thread... TID: %ld\n", threads_label, (unsigned long)mainId);
 
    printf("%s Create new threads.\n", threads_label);
   
    /*pthread_create (pthread_t *__restrict __newthread,
               const pthread_attr_t *__restrict __attr,
               void *(*__start_routine) (void *),
               void *__restrict __arg) __THROWNL __nonnull ((1, 3));
    ** pthread_t *__restrict __newthread    : Pointer that point to new pthread
    ** const pthread_attr_t *attr           : A pointer to a pthread_attr_t structure that specifies the attributes for the new thread
    ** void *(*start_routine)(void *)       : A pointer to the function that the new thread will begin executing.
    ** void *__restrict __arg               : A pointer to the argument that will be passed to the start_routine function when the new thread begins execution
    */
    pthread_create(&childId1, NULL, child1_function, NULL);   //Start of child1 thread
    pthread_create(&childId2, NULL, child2_function, NULL);   //Start of child2 thread
 
    printf("%s Waiting for the new thread to finish...\n", threads_label);
    void* childReturn1;
    void* childReturn2;
 
    /*pthread_join (pthread_t __th, void **__thread_return);
    ** pthread_t __th           : Thread ID of observed thread
    ** void **__thread_return   : Pointer that point to return value of thread
    */
    pthread_join(childId1, &childReturn1);  //Wait thread 1 return and save return value
    pthread_join(childId2, &childReturn2);  //Wait thread 2 return and save return value
 
    int* childReturnInt1 = (int*)childReturn1;
    int* childReturnInt2 = (int*)childReturn2;
 
    printf("%s Child1 has finished. Return value: %d\n", threads_label, *childReturnInt1);
    printf("%s Child2 has finished. Return value: %d\n", threads_label, *childReturnInt2);
 
    for (int i = 0; i < 5; i++) {
        printf("%s Processing.\n", threads_label);
        sleep(1);
    }
 
    printf("%s End thread... \n", threads_label);
 
    free(childReturnInt1);
    free(childReturnInt2);
 
    return 0;   //End of main thread
}