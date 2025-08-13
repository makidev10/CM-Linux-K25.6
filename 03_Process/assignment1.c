//LESSON 3 - ASSIGNMENT 1
 
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
 
#define PARENT_LABEL    "[PARENT]"
#define CHILD_LABEL     "[CHILD]"
 
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
    } else {
        process_label = PARENT_LABEL;
 
        printf("%s Parent PID: %d\n", process_label, getpid());
        printf("%s Child PID: %d\n", process_label, pid);
 
        int status;
 
        wait(&status);
 
        if (WIFEXITED(status)) {
            printf("%s Child process exited with code: %d\n", process_label, WEXITSTATUS(status));
        } else {
            printf("%s Child process did not exited normally!\n", process_label);
        }
    }
 
    return 0;
}