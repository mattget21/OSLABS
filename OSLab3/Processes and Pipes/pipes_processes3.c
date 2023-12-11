#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int pipe1[2], pipe2[2];

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <grep argument>\n", argv[0]);
        return 1;
    }

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    pid_t pid1 = fork();

    if (pid1 < 0) {
        fprintf(stderr, "fork Failed");
        return 1;
    }

    if (pid1 == 0) { // Child P2
        pid_t pid2 = fork();
        if (pid2 == 0) { // Child’s Child P3
            dup2(pipe1[0], STDIN_FILENO);
            dup2(pipe2[1], STDOUT_FILENO);
            close(pipe1[1]);
            close(pipe2[0]);
            execlp("grep", "grep", argv[1], NULL);
        } else {
            dup2(pipe2[0], STDIN_FILENO);
            close(pipe2[1]);
            execlp("sort", "sort", NULL);
        }
    } else { // Parent P1
        dup2(pipe1[1], STDOUT_FILENO);
        close(pipe1[0]);
        execlp("cat", "cat", "scores", NULL);
    }
    return 0;
}
