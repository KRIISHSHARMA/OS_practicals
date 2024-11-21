#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>

void print_perm(mode_t mode) 
{

    printf("Permissions: ");
    printf( (S_ISDIR(mode)) ? "d" : "-");  // Check if it is a directory
    printf( (mode & S_IRUSR) ? "r" : "-");  // Owner read permission
    printf( (mode & S_IWUSR) ? "w" : "-");  // Owner write permission
    printf( (mode & S_IXUSR) ? "x" : "-");  // Owner execute permission
    printf( (mode & S_IRGRP) ? "r" : "-");  // Group read permission
    printf( (mode & S_IWGRP) ? "w" : "-");  // Group write permission
    printf( (mode & S_IXGRP) ? "x" : "-");  // Group execute permission
    printf( (mode & S_IROTH) ? "r" : "-");  // Others read permission
    printf( (mode & S_IWOTH) ? "w" : "-");  // Others write permission
    printf( (mode & S_IXOTH) ? "x" : "-");  // Others execute permission
    printf("\n");
}

int main(int argc, char *argv[]) 
{

    if (argc != 2) 
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

   
    const char *filename = argv[1];

    
    struct stat file_stat;
    if (stat(filename, &file_stat) == -1) 
    {
        perror("Error getting file details");
        return 1;
    }

    // Get the file owner details using getpwuid()
    struct passwd *pw = getpwuid(file_stat.st_uid);
    if (pw == NULL) 
    {
        perror("Error getting owner details");
        return 1;
    }

    
    printf("File: %s\n", filename);
    printf("Owner: %s\n", pw->pw_name); 
    print_perm(file_stat.st_mode);  
    printf("Size: %ld bytes\n", file_stat.st_size);  
    printf("Last access: %s", ctime(&file_stat.st_atime)); 
    printf("Last modified: %s", ctime(&file_stat.st_mtime)); 
    printf("Last status change: %s", ctime(&file_stat.st_ctime)); 

    return 0;
}
