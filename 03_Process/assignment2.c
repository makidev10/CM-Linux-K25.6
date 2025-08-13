//LESSON 3 - ASSIGNMENT 2
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
 
#define PARENT_LABEL    "[PARENT]"
#define CHILD_LABEL     "[CHILD]"
 
int main() {
    pid_t pid;
    char* process_label;
    char command[100];
    char *args[100];
 
    process_label = PARENT_LABEL;
 
    printf("%s Start process...\n", process_label);
 
    printf("%s Enter command: ", process_label);
    fflush(stdin);
    fgets(command, sizeof(command), stdin);
    size_t len = strlen(command);
    if (len > 0 && command[len - 1] == '\n') {
        command[len - 1] = '\0';
    }
 
 
    printf("%s Set environment MY_COMMAND = %s\n", process_label, command);
    if (setenv("MY_COMMAND", command, 1) != 0) {
        printf("%s setenv error!", process_label);
        exit(1);
    }
 
    pid = fork();
 
    if (pid < 0) {
        printf("%s fork error!", process_label);
        exit(1);
    }
 
    if (pid == 0) {
        process_label = CHILD_LABEL;
        printf("%s Start process...\n", process_label);
 
        const char* my_command_value = getenv("MY_COMMAND");
 
        if (my_command_value == NULL) {
            printf("%s Environment variable MY_COMMAND do not exist.\n", process_label);
            exit(1);
        }
 
        char command_str[100];
        strncpy(command_str, my_command_value, sizeof(command_str) - 1);
        command_str[sizeof(command_str) - 1] = '\0';
 
        char* token = strtok(command_str, " ");
        int i = 0;
        while (token != NULL && i < 99) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // Null-terminate the args array
 
        printf("%s Executing command: ", process_label);
        i = 0;
        while (args[i] != NULL) {
            printf("%s ", args[i]);
            i++;
        }
        printf("\n");
 
        fflush(stdout); //Force flush the output before execvp
        execvp(args[0], args);  //After exec() call, current process image (CHILD process) will be replaced with a new called process
 
        return 0;
    } else {
        int status;
 
        wait(&status);
 
        printf("%s Child returned with code: %d\n", process_label, status);
    }
 
    return 0;
}