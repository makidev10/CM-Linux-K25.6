//LESSON 3 - ASSIGNMENT 3_1
 
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
 
#define PARENT_LABEL    "[PARENT]"
#define CHILD_LABEL     "[CHILD]"
 
int main() {
    pid_t pid;
    char* process_label;
 
    process_label = PARENT_LABEL;
    printf("%s Start process... PID: %d\n", process_label, getpid());
 
    pid = fork();
 
    if (pid == 0) {
        process_label = CHILD_LABEL;
        printf("%s Start process... PID: %d\n", process_label, getpid());
        for (int i = 0; i < 5; i++) {
            printf("%s Processing. My Parent PID: %d\n", process_label, getppid());
            sleep(1);
        }
        printf("%s End process.\n", process_label);
        return 0;   //Child process turn to Zombie process after this
    } else {
        printf("%s Create child process successfully. PID: %d\n", process_label, pid);
        // int status = 0;
        // wait(&status);
        for (int i = 0; i < 10; i++) {
            printf("%s Processing. My Child PID: %d\n", process_label, getppid());
            sleep(1);
        }
        printf("%s End process.\n", process_label);
    }
 
    return 0;
}