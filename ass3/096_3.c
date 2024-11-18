/*
 * Name : Subhayan Roy Chowdhury
 * Roll No : 002211001096
 * Date : 02/09/2024
 * IT UG3 A2
 * Assignment 3 : Transfer 1 GB File between parent and child processes using socket and compare files. (I have done 1MB file transfer due  to * server capacity constraints)
 *
 * Compilation: gcc -o file_transfer socket.c -Wall -Wextra -Werror
 *
 * Execution:
 * ./file_transfer test_file.dat
 *
 * Input:
 *<test_file>: can be created with the following command
 * dd if=/dev/zero of=test_file.dat bs=1M count=1
 *
 * Output:
 * The program prints whether the sent and received files are identical or not
 * The program prints the time required for the double transfer
 *

 */

//standard input output operations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//fork,read,write,close functions
#include <unistd.h>

//socket operations
#include <sys/socket.h>
#include <sys/types.h>

//file control operations like opening files
#include <fcntl.h>

//for calculating time elapsed
#include <sys/time.h>
//transferring 1 MB file so setting its size
#define FILE_SIZE 1048576  // 1 MB


//function to transfer file
void transfer_file(int socket_fd, int fd) {

    char buffer[FILE_SIZE];
    ssize_t bytes_read;
    ssize_t bytes_written;
    ssize_t total_bytes_written = 0;

        //read the entire file
       bytes_read = read(fd, buffer, FILE_SIZE);
    if (bytes_read < 0) {
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }


        //Write data to the socket in a loop
        while (total_bytes_written < bytes_read) {
        bytes_written = write(socket_fd, buffer + total_bytes_written, bytes_read - total_bytes_written);
        if (bytes_written < 0) {
            perror("Error writing to socket");
            exit(EXIT_FAILURE);
        }
        total_bytes_written += bytes_written;
    }
}


//function to receive file
void receive_file(int socket_fd, const char *file_name) {
    char buffer[FILE_SIZE];
    ssize_t bytes_read;
    ssize_t total_bytes_read = 0;

        //read data from the socket in a loop
        while (total_bytes_read < FILE_SIZE) {
        bytes_read = read(socket_fd, buffer + total_bytes_read, FILE_SIZE - total_bytes_read);
      if (bytes_read < 0) {
            perror("Error reading from socket");
            exit(EXIT_FAILURE);
        }
        if (bytes_read == 0) {
            break; // End of transmission
        }
        total_bytes_read += bytes_read;
    }

//open the file
    int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

//write the file
    ssize_t bytes_written = write(fd, buffer, total_bytes_read);
    if (bytes_written < 0) {
        perror("Error writing to file");
        exit(EXIT_FAILURE);
    }

    close(fd);
}


//function to compare sent and received files
int compare_files(const char *file1, const char *file2) {

        //open both files
    char buffer1[FILE_SIZE], buffer2[FILE_SIZE];
    int fd1 = open(file1, O_RDONLY);
    int fd2 = open(file2, O_RDONLY);

    if (fd1 < 0 || fd2 < 0) {
        perror("Error opening files for comparison");
        exit(EXIT_FAILURE);
    }

   //read both files into buffers
    ssize_t bytes_read1 = read(fd1, buffer1, FILE_SIZE);
    ssize_t bytes_read2 = read(fd2, buffer2, FILE_SIZE);

    close(fd1);
    close(fd2);
        //compare the bytes read in buffers as well as using memcmp
    return (bytes_read1 == bytes_read2) && (memcmp(buffer1, buffer2, bytes_read1) == 0);
}

int main(int argc, char *argv[]) {

   //check for argument containing file to transfer.    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_to_transfer>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

//create socket pair between parent and child process
    int socket_fds[2];
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, socket_fds) < 0) {
        perror("Error creating socket pair");
        exit(EXIT_FAILURE);
    }

//create child process using fork
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error forking");
        exit(EXIT_FAILURE);
    }

    struct timeval start, end;
//Parent process
//
//Closes the child's end of the socket.
//Opens the file to transfer.
//Sends the file to the child and receives it back.
//Compares the original and received files to check for data integrity.
//Calculates and prints the time taken for the entire process.

    if (pid > 0) { // Parent process
        close(socket_fds[1]);

        int fd = open(argv[1], O_RDONLY);
        if (fd < 0) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        //get the time to calculate time of transfer
        gettimeofday(&start, NULL);
        transfer_file(socket_fds[0], fd);
        receive_file(socket_fds[0], "received_from_child.dat");
        gettimeofday(&end, NULL);

        //close the file and socket
        close(fd);
        close(socket_fds[0]);

        //check if the sent and received files match
        if (compare_files(argv[1], "received_from_child.dat")) {
            printf("Files match.\n");
        } else {
            printf("Files do not match.\n");
        }

        //calculate time of transfer
        long seconds = end.tv_sec - start.tv_sec;
        long microseconds = end.tv_usec - start.tv_usec;
        double elapsed = seconds + microseconds * 1e-6;
        printf("Time required for double transfer: %.6f seconds\n", elapsed);

 }



//Child process:
//Closes the parent's end of the socket.
//Receives the file from the parent and saves it.
//Sends the file back to the parent.
//Exits successfully.

 else { // Child process
        close(socket_fds[0]);

        receive_file(socket_fds[1], "received_from_parent.dat");
        int fd = open("received_from_parent.dat", O_RDONLY);
        if (fd < 0) {
            perror("Error opening received file");
            exit(EXIT_FAILURE);
        }

        //transfer the file
        transfer_file(socket_fds[1], fd);

        //close the file and socket
         close(fd);
        close(socket_fds[1]);

        exit(EXIT_SUCCESS);
    }

    return 0;
}

