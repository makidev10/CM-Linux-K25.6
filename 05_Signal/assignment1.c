//LESSON 5 - ASSIGNMENT 1
 
#include <stdio.h>
#include <signal.h>
 
volatile int count = 0;
 
void sigint_handler() {
    count++;
    printf("\nSIGINT received\n");
}
 
int main() {
    signal(SIGINT, sigint_handler);
 
    while (count < 3) {
        printf("Running...\n");
        sleep(1);
    }
 
    return 0;
}