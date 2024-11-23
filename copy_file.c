#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#define MAX_BUFFER_SIZE 4096

void file_copy(char *source_file , char *destination_file)
{
    int source_fd, dest_fd, bytes_read, bytes_written;
    char buffer[MAX_BUFFER_SIZE];


    source_fd = open(source_file, O_RDONLY); //read only
    if (source_fd == -1) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    dest_fd = open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); // if file doesnt exist make one , and if does delete it 
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(source_fd);
        exit(EXIT_FAILURE);
    }

   
    while ((bytes_read = read(source_fd, buffer, MAX_BUFFER_SIZE)) > 0) 
    {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) 
        {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read == -1)
    {
        perror("Error reading source file");
    }

    // Close both the source and destination files
    close(source_fd);
    close(dest_fd);

    printf("File copied successfully from %s to %s\n", source_file, destination_file);
}


int main(int argc , char *argv[])
{
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    file_copy(argv[1],argv[2]);
    return 0;
}