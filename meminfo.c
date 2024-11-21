#include <stdio.h>
#include <stdlib.h>
#include<sys/sysinfo.h>

int main() {
    FILE *fp;
    char buffer[256];
    int status = 0 ;
    struct sysinfo un;
	status = sysinfo(&un);

    if(status == 0)
    {
        printf("\nMemTotal : %ld", (un.totalram));
		printf("\nMemFree:: %ld", (un.freeram));
		printf("\nMemAvail: %ld\n", (un.totalram-un.freeram));
    }

    printf("------------------------\n");

/* or you can read from /proc/meminfo*/

    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) 
    {
        perror("Error opening /proc/meminfo");
        return 1;
    }

    printf("Memory Information:\n");
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL) 
    {
        
        if (strncmp(buffer, "MemTotal:", 9) == 0 ||
            strncmp(buffer, "MemFree:", 8) == 0 ||
            strncmp(buffer, "MemAvailable:", 13) == 0) 
        {
            printf("%s", buffer);
        }
    }
    

    fclose(fp);

    return 0;
}
