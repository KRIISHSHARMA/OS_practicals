#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/utsname.h>
 
void get_cpu_info() { 
    FILE *file = fopen("/proc/cpuinfo", "r"); 
    if (file == NULL) { 
        perror("Failed to open /proc/cpuinfo"); 
        return; 
    } 
    char buffer[256]; 
    char *cpu_model = NULL; 
 
    while (fgets(buffer, sizeof(buffer), file)) { 
        if (strncmp(buffer, "model name", 10) == 0) { 
            cpu_model = strchr(buffer, ':') + 2;  // Skip ": " 
            break; 
        } 
    } 
 
    if (cpu_model != NULL) { 
        printf("CPU Model: %s", cpu_model); 
    } else { 
        printf("CPU Model information not found.\n"); 
    } 
 
    fclose(file); 
} 


 
int main() { 
    printf("Linux Kernel and CPU Information\n"); 
    printf("--------------------------------\n"); 
 
    // Get kernel version 
    struct utsname sysinfo;

    // Call uname syscall
    if (uname(&sysinfo) == -1) {
        perror("uname");
        exit(EXIT_FAILURE);
    }

    // Print kernel information
    printf("Kernel Information:\n");
    printf("  System Name: %s\n", sysinfo.sysname);
    printf("  Node Name: %s\n", sysinfo.nodename);
    printf("  Release: %s\n", sysinfo.release);
    printf("  Version: %s\n", sysinfo.version);
    printf("  Machine: %s\n", sysinfo.machine);
 
    // Get CPU information 
    get_cpu_info(); 
    printf("--------------------------------\n"); 
 
    return 0; 
}

