#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int seconds = 0;

void alarm_handler(int signum) {
    seconds++;
    alarm(1); // Reset the alarm
}

void sigint_handler(int signum) {
    printf("Total execution time: %d seconds\n", seconds);
    exit(0);
}

int main(int argc, char * argv[]) {
    signal(SIGALRM, alarm_handler);
    signal(SIGINT, sigint_handler);
    alarm(1);
    while(1) {
        pause(); // Wait for a signal
    }
    return 0;
}
