#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    struct utsname sysinfo;

    if (fork() == 0) {
        // Child process
        if (uname(&sysinfo) == 0) {
            printf("Kernel Information (from Child Process):\n");
            printf("  System Name: %s\n", sysinfo.sysname);
            printf("  Node Name: %s\n", sysinfo.nodename);
            printf("  Release: %s\n", sysinfo.release);
            printf("  Version: %s\n", sysinfo.version);
            printf("  Machine: %s\n", sysinfo.machine);
        } else {
            perror("Error fetching kernel information");
        }
    } else {
        // Parent process
        wait(NULL); // Parent waits for child to finish
        printf("Parent waited for child to finish execution.\n");
    }

    return 0;
}
