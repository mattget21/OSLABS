#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

// Global variables for timer, background flag, and command lookup
int timer_set = 0; // flag to indicate whether a timer is set
bool background = false; // flag to indicate whether a command should be executed in the background
char *custom_builtins[] = {"cd", "pwd", "echo", "export", NULL}; // Custom shell built-ins

// Function to set a timer
void set_timer(int seconds) {
    timer_set = 1;
    alarm(seconds); // send a SIGALRM signal to the process after the specified number of seconds
}

// Function to cancel the timer
void cancel_timer() {
    timer_set = 0;
    alarm(0); // cancel any pending alarms
}

// Function to handle SIGINT (Ctrl+C)
void handle_SIGINT(int signum) {
    if (!background) { // if the command is not executed in the background
        printf("\n"); // print a newline character
        char current_dir[MAX_COMMAND_LINE_LEN];
        if (getcwd(current_dir, sizeof(current_dir)) != NULL) { // get the current working directory
            printf("%s> ", current_dir); // print the current working directory
        } else {
            perror("getcwd"); // print an error message if getcwd fails
        }
        fflush(stdout); // flush the output buffer
    }
}

// Function to handle SIGALARM (timer)
void handle_SIGALARM(int signum) {
    if (timer_set) { // if a timer is set
        printf("\nTimer has expired. Terminating process.\n"); // print a message indicating that the timer has expired
        kill(0, SIGINT); // send a SIGINT signal to the process group
    }
}

// Function to execute a command
void execute_command(char **args) {
    pid_t pid = fork(); // create a child process
    if (pid == 0) {
        // Child process
        signal(SIGINT, SIG_DFL); // set the SIGINT signal handler to the default handler
        execvp(args[0], args); // execute the command
        perror("execvp"); // print an error message if execvp fails
        exit(EXIT_FAILURE); // exit the child process with a failure status
    } else if (pid > 0) {
        // Parent process
        if (!background) { // if the command is not executed in the background
            set_timer(10); // set a timer for 10 seconds
            int status;
            if (waitpid(pid, &status, 0) == -1) { // wait for the child process to terminate
                perror("waitpid"); // print an error message if waitpid fails
                exit(EXIT_FAILURE); // exit the parent process with a failure status
            }
            cancel_timer(); // cancel the timer
        }
    } else {
        // Fork failed
        perror("fork"); // print an error message if fork fails
        exit(EXIT_FAILURE); // exit the parent process with a failure status
    }
}

// Function to handle custom shell built-ins
bool handle_builtins(char **args) {
    for (int i = 0; custom_builtins[i] != NULL; i++) {
        if (strcmp(args[0], custom_builtins[i]) == 0) { // if the command is a custom shell built-in
            // Handle the custom built-in command
            // Example: Implement cd, pwd, echo, export here
            if (strcmp(args[0], "cd") == 0) { // if the command is cd
                if (args[1] == NULL) { // if no argument is provided
                    chdir(getenv("HOME")); // change the current working directory to the home directory
                } else {
                    if (chdir(args[1]) == -1) { // change the current working directory to the specified directory
                        perror("chdir"); // print an error message if chdir fails
                    }
                }
            } else if (strcmp(args[0], "pwd") == 0) { // if the command is pwd
                char current_dir[MAX_COMMAND_LINE_LEN];
                if (getcwd(current_dir, sizeof(current_dir)) != NULL) { // get the current working directory
                    printf("%s\n", current_dir); // print the current working directory
                } else {
                    perror("getcwd"); // print an error message if getcwd fails
                }
            } else if (strcmp(args[0], "echo") == 0) { // if the command is echo
                for (int j = 1; args[j] != NULL; j++) {
                    printf("%s ", args[j]); // print the arguments
                }
                printf("\n"); // print a newline character
            } else if (strcmp(args[0], "export") == 0) { // if the command is export
                // Implement environment variable handling here
                // Example: export NAME=VALUE
                if (args[1] != NULL) { // if an argument is provided
                    if (putenv(args[1]) != 0) { // set the environment variable
                        perror("putenv"); // print an error message if putenv fails
                    }
                }
            }
            return true; // return true to indicate that the command is a built-in command
        }
    }
    return false; // return false to indicate that the command is not a built-in command
}

void execute_commands_with_pipes(char **args1, char **args2) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }

    pid_t pid1 = fork();

    if (pid1 == 0){
        // child process for the first command
        close(pipefd[0]); // close the read end of the pipe
        dup2(pipefd[1], STDOUT_FILENO); // redirect stdout to the write end of the pipe
        close(pipefd[1]); // close the write end of the pipe

        execvp(args1[0], args1); // execute the first command
        perror("execvp (command 1)"); // print an error message if execvp fails
        exit(EXIT_FAILURE); // exit the child process with a failure status
    }

    pid_t pid2 = fork();

    if(pid2 == 0){
        //child process for the second command
        close(pipefd[1]); // close the write end of the pipe
        dup2(pipefd[0], STDIN_FILENO); // redirect stdin to the read end of the pipe
        close(pipefd[0]); // close the read end of the pipe

        execvp(args2[0], args2); // execute the second command
        perror("execvp (command 2)"); // print an error message if execvp fails
        exit(EXIT_FAILURE); // exit the child process with a failure status
    }

    //Execution of the parent process
    close(pipefd[0]); // close the read end of the pipe
    close(pipefd[1]); // close the write end of the pipe
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}


//Function to handle pipe commands
bool handle_pipe(char **args){
    char *token;
    char *args1[MAX_COMMAND_LINE_ARGS];
    char *args2[MAX_COMMAND_LINE_ARGS];
    int i = 0;
    int mode = 0; //Collecting args for the first command, 1: collecting args for the second command

    //Parse the command line into args1 and args2
    for (token = strtok(args, "|"); token != NULL; token = strtok(NULL, "|")) {
        if (mode == 0) {
            args1[i] = strdup(token);
            mode = 1;
        } else {
            args2[i] = strdup(token);
            mode = 0;
        }
        i++;
    }
    args1[i] = NULL;
    args2[i] = NULL;

    if (args1[0] != NULL && args2[0] != NULL) {
        //TODO(brandon): implement pipe execution command
        return true;
    }

    return false;
}

int main() {
    char command_line[MAX_COMMAND_LINE_LEN];
    char *args[MAX_COMMAND_LINE_ARGS];
    signal(SIGINT, handle_SIGINT); // set the SIGINT signal handler to the handle_SIGINT function
    signal(SIGALRM, handle_SIGALARM); // set the SIGALRM signal handler to the handle_SIGALARM function

    while (true) {
        // Read input using getline for dynamic memory allocation
        size_t line_size = 0;
        ssize_t read_size = getline(&command_line, &line_size, stdin); // read a line of input from stdin
        if (read_size == -1) {
            perror("getline"); // print an error message if getline fails
            break; // break out of the loop
        }
        if (read_size <= 1) {
            // Empty line
            continue; // continue to the next iteration of the loop
        }

        // Tokenize input and execute command, handle built-ins, or pipe commands
        char *token = strtok(command_line, " \t\r\n"); // tokenize the input
        int i = 0;
        while (token != NULL) {
            args[i] = strdup(token); // allocate memory for the argument and copy the token
            token = strtok(NULL, " \t\r\n"); // get the next token
            i++;
        }
        args[i] = NULL; // set the last argument to NULL

        if (strcmp(args[0], "exit") == 0) {
            // Exit the shell
            break; // break out of the loop
        } else if (handle_pipe(args)) {
            // Pipe command detected
        } else if (handle_builtins(args)) {
            // Command was a built-in, no need to execute it
        } else {
            // Execute the command
            execute_command(args);
        }

        // Free allocated memory for arguments
        for (int j = 0; j < i; j++) {
            free(args[j]); // free the memory allocated for the argument
        }
    }

    // Free memory for getline
    free(command_line); // free the memory allocated for the command line
    return 0; // exit the program with a success status
}