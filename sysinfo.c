#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <sys/wait.h>

void get_cpu_info(){
    FILE *file = fopen("/proc/cpuinfo", "r");
    if (file) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file)) {
            if (strncmp(buffer, "model name", 10) == 0) {
                printf("CPU Model: %s", strchr(buffer, ':') + 2);
                break;
            }
        }
        fclose(file);
    }
}

int main() {
    struct utsname sysinfo;
    if (fork() == 0) {
        if (uname(&sysinfo) == 0){
            printf("Kernel Information:\n  System: %s,\n Node: %s,\n Release: %s,\n Version: %s,\n Machine: %s\n",
                   sysinfo.sysname, sysinfo.nodename, sysinfo.release, sysinfo.version, sysinfo.machine);
        }
        get_cpu_info();
    } else {
        wait(NULL); 
        printf("Parent: Child completed.\n");
    }
    return 0;
}
