#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid < 0) 
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) 
    {
        // Child process
        printf("Child: Process ID: %d\n", getpid());

        // a) Same program, same code
        printf("Child: Executing same code as parent.\n");

        // b) Same program, different code
        printf("Child: Executing different code (using exec).\n");
        execl("/bin/echo", "echo", "Child says hello via exec!", NULL);

        // If execl() fails
        perror("execl failed");
        exit(EXIT_FAILURE);
    } else 
    {
        // Parent process
        printf("Parent: Process ID: %d, Waiting for child...\n", getpid());

        // c) Wait for child to complete
        wait(NULL);
        printf("Parent: Child process has finished.\n");
    }

    return 0;
}