//LESSON 5 - ASSIGNMENT 2
 
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
 
volatile int timer_count = 0;
 
void sigalrm_handler(int sig) {
    timer_count++;
    printf("Timer: %d seconds\n", timer_count);
    if (timer_count < 10) {
        alarm(1);
    } else {
        printf("Stop counting!\n");
        exit(0);
    }
}
 
int main() {
    signal(SIGALRM, sigalrm_handler);
 
    printf("Start counting!\n");
    alarm(1);
 
    while(1) {
        pause();
    }
 
    return 0;
}