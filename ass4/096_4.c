/*
 * Name : Subhayan Roy Chowdhury
 * Roll No : 002211001096
 * Date : 09/09/2024
 * IT UG3 A2
 * Assignment 4:Use mmap() call and observe page-fault using the ‘sar’ command.
 *
 * Compilation: gcc -o mmap_test 096_4.c
 *
 * Execution:
 * ./mmap_test
 *
 * Input:
 * NA. the file is created inside the program itself. simple execution will work.
 *
 * Output:
 * We observed two sets of outputs. Firstly, we ran the program and saw this in the current terminal running in an infinite loop
 *
 * Verification success: X = 74 at offset 0x7cdc16
 * Verification success: X = a6 at offset 0x116f41
 * Verification success: X = 5b at offset 0x7ac625
 * Verification success: X = 3e at offset 0x38d3e3
 * Verification success: X = f4 at offset 0x52b0d7
 * Verification success: X = 88 at offset 0x2c57ed
 * Verification success: X = 00 at offset 0x52c6f3
 * Verification success: X = e5 at offset 0x5fb464
 * Verification success: X = 19 at offset 0x21c41a
 * Verification success: X = 27 at offset 0x516e33
 * ^C
 *
 * Next, we used the sar(system activity report) to see the system activity information. We opened another terminal and gave the following command:
 * sar -B 1
 * -B: This option specifies that `sar` should report information related to paging and swapping statistics, such as page faults and memory paging.
 * -1 : This is the interval in seconds between reports. So `sar -B 1` means that `sar` will report paging statistics every second.
 *  The following output was observed:
 *  [be2296@localhost ass4]$ sar -B 1
 *  Linux 3.10.0-514.21.1.el7.x86_64 (localhost.localdomain)    Monday 09 September 2024        _x86_64_        (16 CPU)
 *
 *  12:57:19  IST  pgpgin/s pgpgout/s   fault/s  majflt/s  pgfree/s pgscank/s pgscand/s pgsteal/s    %vmeff
 *  12:57:20  IST      0.00    264.00    540.00      0.00    242.00      0.00      0.00      0.00      0.00
 *  12:57:21  IST      0.00      0.00    540.00      0.00    212.00      0.00      0.00      0.00      0.00
 *  12:57:22  IST      0.00      4.00    531.00      0.00    225.00      0.00      0.00      0.00      0.00
 *  12:57:23  IST      0.00      4.00    750.00      0.00    264.00      0.00      0.00      0.00      0.00
 *  12:57:24  IST      0.00      4.00  14084.00      0.00   8708.00      0.00      0.00      0.00      0.00
 *  12:57:25  IST      0.00      4.00   6222.00      0.00  23634.00      0.00      0.00      0.00      0.00
 *  12:57:26  IST      0.00      0.00    545.00      0.00    229.00      0.00      0.00      0.00      0.00
 *  12:57:27  IST      0.00    124.00    560.00      0.00    336.00      0.00      0.00      0.00      0.00
 *  12:57:28  IST      0.00      0.00    550.00      0.00    232.00      0.00      0.00      0.00      0.00
 *  12:57:29  IST      0.00      0.00    561.00      0.00    245.00      0.00      0.00      0.00      0.00
 *  12:57:30  IST      0.00      0.00    542.00      0.00    236.00      0.00      0.00      0.00      0.00
 *  12:57:31  IST      0.00      0.00    557.00      0.00    236.00      0.00      0.00      0.00      0.00
 *  12:57:32  IST      0.00      0.00    559.00      0.00    247.00      0.00      0.00      0.00      0.00
 *  12:57:33  IST      0.00      0.00    552.00      0.00    250.00      0.00      0.00      0.00      0.00
 *  12:57:34  IST      0.00    272.00    551.00      0.00    242.00      0.00      0.00      0.00      0.00
 *  12:57:35  IST      0.00      0.00    533.00      0.00    201.00      0.00      0.00      0.00      0.00
 *  12:57:36  IST      0.00      0.00    545.00      0.00    253.00      0.00      0.00      0.00      0.00
 *  12:57:37  IST      0.00      0.00   1783.00      0.00   1202.00      0.00      0.00      0.00      0.00
 *  12:57:38  IST      0.00      0.00    552.00      0.00    234.00      0.00      0.00      0.00      0.00
 *  12:57:39  IST      0.00    438.00    552.00      0.00    248.00      0.00      0.00      0.00      0.00
 *  12:57:40  IST      0.00    264.00    574.00      0.00    281.00      0.00      0.00      0.00      0.00
 *  12:57:41  IST      0.00      0.00    559.00      0.00    242.00      0.00      0.00      0.00      0.00
 *  12:57:42  IST      0.00      8.00    587.00      0.00    276.00      0.00      0.00      0.00      0.00
 *  12:57:43  IST      0.00   1820.00    568.00      0.00    276.00      0.00      0.00      0.00      0.00
 *  12:57:44  IST      0.00      0.00    560.00      0.00    238.00      0.00      0.00      0.00      0.00
 *  12:57:45  IST      0.00      0.00    553.00      0.00    259.00      0.00      0.00      0.00      0.00
 *  12:57:46  IST      0.00      0.00    531.00      0.00    218.00      0.00      0.00      0.00      0.00
 *  12:57:47  IST      0.00    544.00    588.00      0.00    362.00      0.00      0.00      0.00      0.00
 *  12:57:48  IST      0.00      0.00    554.00      0.00    238.00      0.00      0.00      0.00      0.00
 *  12:57:49  IST      0.00      0.00    587.00      0.00    285.00      0.00      0.00      0.00      0.00
 *  12:57:50  IST      0.00      0.00    568.00      0.00    248.00      0.00      0.00      0.00      0.00
 *  12:57:51  IST      0.00    268.00    594.00      0.00    278.00      0.00      0.00      0.00      0.00
 *  12:57:52  IST      0.00      0.00    551.00      0.00    249.00      0.00      0.00      0.00      0.00
 *  12:57:53  IST      0.00      0.00    531.00      0.00    228.00      0.00      0.00      0.00      0.00
 *  ^C
 *
 *  12:57:54  IST      0.00      0.00   3763.22      0.00   1778.16      0.00      0.00      0.00      0.00
 *  Average:         0.00    115.23   1227.07      0.00   1230.31      0.00      0.00      0.00      0.00
 *
                 */





#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> //file control operations including posix_fallocate
#include <unistd.h>//sleep,close, write functions etc
#include <sys/mman.h>//memory management operations like mmap  and munmap functions
#include <time.h>//time related functions
#include <stdint.h>//uint8_t type for unsigned 8 bit integers
#include <errno.h>//for reporting errors
#include <string.h> // string operations as well as stderror

#define FILE_SIZE 8388608  // 8 MB File size

int main() {
    // seeding the random number generator
    srand(time(NULL));

    // Create a file of 8 MB named bigfile.dat
    int fd = open("bigfile.dat", O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Allocating the file size using posix_fallocate as asked
    int result = posix_fallocate(fd, 0, FILE_SIZE);
    if (result != 0) {
        fprintf(stderr, "Error allocating file size: %s\n", strerror(result));
        close(fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Generate random values for X and F
        uint8_t X = rand() % 256;
        off_t F = rand() % FILE_SIZE;

        // Write the byte X at offset F
        if (lseek(fd, F, SEEK_SET) < 0) {
            perror("Error seeking in file");
            close(fd);
            exit(EXIT_FAILURE);
        }
        if (write(fd, &X, 1) < 0) {
            perror("Error writing to file");
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Map the file into memory
        uint8_t *mapped = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (mapped == MAP_FAILED) {
            perror("Error mapping file");
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Read the byte at offset F from the mapped region
        uint8_t X_prime = mapped[F];

        // Verify if the written and read values match
        if (X != X_prime) {
            fprintf(stderr, "Verification failed: X = %02x, X' = %02x at offset 0x%lx\n", X, X_prime, F);
            munmap(mapped, FILE_SIZE);
            close(fd);
            exit(EXIT_FAILURE);
        } else {
            printf("Verification success: X = %02x at offset 0x%lx\n", X, F);
        }

        // Unmap the memory
        if (munmap(mapped, FILE_SIZE) != 0) {
            perror("Error unmapping memory");
            close(fd);
            exit(EXIT_FAILURE);
        }

        // 1 sec sleep to observe the page faults more clearly
        sleep(1);
    }

    close(fd);
    return 0;
}