#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum) {
    printf("Hello World!\n");
    alarm(1); // Reset the alarm
}

int main(int argc, char * argv[]) {
    signal(SIGALRM, handler); // Register handler to handle SIGALRM
    alarm(1); // Schedule a SIGALRM for 1 second
    while(1) {
        pause(); // Wait for the signal
        printf("Turing was right!\n");
    }
    return 0;
}
