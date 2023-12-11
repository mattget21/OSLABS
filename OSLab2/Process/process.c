#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    int status;

    // Fork first child process
    pid1 = fork();

    if (pid1 == 0) {
        // This is the first child process
        srandom(getpid());
        int iterations = random() % 30;
        for (int i = 0; i < iterations; i++) {
            printf("Child Pid: %d is going to sleep!\n", getpid());
            sleep(random() % 10);
            printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
        }
        exit(0);
    }

    // Fork second child process
    pid2 = fork();

    if (pid2 == 0) {
        // This is the second child process
        srandom(getpid());
        int iterations = random() % 30;
        for (int i = 0; i < iterations; i++) {
            printf("Child Pid: %d is going to sleep!\n", getpid());
            sleep(random() % 10);
            printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
        }
        exit(0);
    }

    // Parent process
    waitpid(pid1, &status, 0);
    printf("Child Pid: %d has completed\n", pid1);

    waitpid(pid2, &status, 0);
    printf("Child Pid: %d has completed\n", pid2);

    return 0;
}
