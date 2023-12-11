#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd1[2];  // Used to store two ends of first pipe
    int fd2[2];  // Used to store two ends of second pipe

    char fixed_str[] = "howard.edu";
    char input_str[100];
    pid_t p;

    if (pipe(fd1) == -1) {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }
    if (pipe(fd2) == -1) {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    printf("Enter a string to concatenate: ");
    scanf("%s", input_str);
    p = fork();

    if (p < 0) {
        fprintf(stderr, "fork Failed");
        return 1;
    }

    // Parent process
    else if (p > 0) {
        close(fd1[0]);  // Close reading end of first pipe
        write(fd1[1], input_str, strlen(input_str) + 1);
        close(fd1[1]);  // Close writing end of first pipe

        // Wait for child to send a string
        wait(NULL);

        close(fd2[1]); // Close writing end of second pipe
        char concat_str[200];
        read(fd2[0], concat_str, 200);
        printf("Output from child: %s\n", concat_str);

        char second_input[100];
        printf("Enter second string to concatenate: ");
        scanf("%s", second_input);
        strcat(concat_str, second_input);
        printf("Final Output: %s\n", concat_str);

        close(fd2[0]); // Close reading end of second pipe
    }

    // Child process
    else {
        close(fd1[1]);  // Close writing end of first pipe
        char concat_str[100];
        read(fd1[0], concat_str, 100);
        close(fd1[0]);  // Close reading end of first pipe

        // Concatenate a fixed string with it
        strcat(concat_str, fixed_str);

        close(fd2[0]); // Close reading end of second pipe
        write(fd2[1], concat_str, strlen(concat_str) + 1);
        close(fd2[1]); // Close writing end of second pipe

        exit(0);
    }
    return 0;
}
