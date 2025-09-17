//LESSON 5 - ASSIGNMENT 3
 
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
 
#define PARENT_LABEL    "[PARENT]"
#define CHILD_LABEL     "[CHILD]"
 
volatile int count = 0;
 
void signal_handler() {
    char* process_label = CHILD_LABEL;
    printf("%s Received signal from parent\n", process_label);
    count++;
}
 
int main() {
    pid_t pid;
    char* process_label;
 
    pid = fork();
 
    if (pid < 0) {
        printf("Fork error!\n");
        return 1;
    }
 
    if (pid == 0) {
        process_label = CHILD_LABEL;
        printf("%s Child PID: %d\n", process_label, getpid());
 
        signal(SIGUSR1, signal_handler);
 
        while (count < 5) {
            // sleep(1);
        }
 
        printf("%s End process!\n", process_label);
        return 0;
    } else {
        process_label = PARENT_LABEL;
 
        printf("%s Parent PID: %d\n", process_label, getpid());
        printf("%s Child PID: %d\n", process_label, pid);
 
        for (int i = 0; i < 5; i++) {
            printf("%s Notify SIGUSR1 number %d for child (PID: %d)...\n",process_label, i + 1, pid);
            kill(pid, SIGUSR1);
            sleep(2);
        }
 
        printf("%s End process!\n", process_label);
    }
 
    return 0;
}