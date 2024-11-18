/*
 *Name : Subhayan Roy Chowdhury
 *Roll : 002211001096
 *Class :IT UG3 A2
 * Assignment 6
 * Compilation:
 * gcc 096_6.c
 * Execution
 * ./a.out
 *
 * Sample output: [be2296@localhost ass6]$ ./a.out
 * Processor Information:
 * vendor_id       : GenuineIntel
 * model name      : Intel(R) Xeon(R) CPU E5-2609 v4 @ 1.70GHz
 * cache size      : 20480 KB
 *
 * Kernel Information:
 * Kernel Name: 3.10.0-514.21.1.el7.x86_64
 * Kernel Release: mockbuild@sl7-uefisign.fnal.gov
 * OS Name: Red Hat 4.8.5-11
 *
 * Memory Information:
 * Total Memory: 64013.00 MB
 * Free Memory: 60897.58 MB
 *
 * System Uptime: 557 hours, 52 minutes, 36 seconds
 * */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
void print_processor_info() {
    FILE *fp;
    char buffer[256];
    char vendor_id[256] = {0};
    char model_name[256] = {0};
    char cache_size[256] = {0};

    // Read CPU information
    fp = fopen("/proc/cpuinfo", "r");
    if (!fp) {
        perror("Failed to open /proc/cpuinfo");
        return;
    }    // Read the CPU information and store it in variables
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strncmp(buffer, "vendor_id", 9) == 0) {
            strncpy(vendor_id, buffer, sizeof(vendor_id) - 1);
        } else if (strncmp(buffer, "model name", 10) == 0) {
            strncpy(model_name, buffer, sizeof(model_name) - 1);
        } else if (strncmp(buffer, "cache size", 10) == 0) {
            strncpy(cache_size, buffer, sizeof(cache_size) - 1);
        }
    }
    fclose(fp);

    // Print the stored values
    printf("Processor Information:\n");
    if (strlen(vendor_id) > 0) {
        printf("%s", vendor_id);
    }
    if (strlen(model_name) > 0) {
        printf("%s", model_name);
    }
    if (strlen(cache_size) > 0) {
        printf("%s", cache_size);
    }
    printf("\n");
}

void print_kernel_info() {
    FILE *fp;
    char buffer[256];
    char kernel_name[256] = {0};
    char kernel_release[256] = {0};
    char os_name[256] = {0};

    // Read kernel version information
    fp = fopen("/proc/version", "r");
    if (!fp) {
        perror("Failed to open /proc/version");
        return;
    }

    // Read the version information
    if (fgets(buffer, sizeof(buffer), fp)) {
        // Extract kernel name
        sscanf(buffer, "Linux version %s", kernel_name);
        // Find the kernel release
        char *start_release = strchr(buffer, '(');
        char *end_release = strchr(buffer, ')');

        if (start_release && end_release && start_release < end_release) {
            strncpy(kernel_release, start_release + 1, end_release - start_release - 1);
            kernel_release[end_release - start_release - 1] = '\0'; // Null-terminate
        }
    const char *start = NULL;
    const char *end = NULL;
    int open_count = 0, close_count = 0;

    // Traverse the string to find the positions of parentheses
        const  char*p;
    for (p = buffer; *p; p++) {
        if (*p == '(') {
            open_count++;
            if (open_count == 3) {
                start = p; // Mark the position of the 3rd '('
            }
        }
        if (*p == ')') {
            close_count++;
            if (close_count == 2) {
                end = p; // Mark the position of the 3rd ')' from the end
                break; // Exit the loop after finding the 3rd ')'
            }
        }
    }

    // If both positions were found, extract the substring
    if (start && end && start < end) {
        strncpy(os_name, start + 1, end - start - 1);
        os_name[end - start - 1] = '\0'; // Null-terminate
    }
    }
    fclose(fp);

    // Print the stored values
    printf("Kernel Information:\n");
    printf("Kernel Name: %s\n", kernel_name);
    printf("Kernel Release: %s\n", kernel_release);
    printf("OS Name: %s\n\n", os_name);
}void print_memory_info() {
    FILE *fp;
    char buffer[256];
    long total_memory = 0, free_memory = 0;
    // Read memory information
    fp = fopen("/proc/meminfo", "r");
    if (!fp) {
        perror("Failed to open /proc/meminfo");
        return;
    }
    printf("Memory Information:\n");
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (sscanf(buffer, "MemTotal: %ld kB", &total_memory) == 1 ||
            sscanf(buffer, "MemFree: %ld kB", &free_memory) == 1) {
            // Successfully scanned total and free memory
        }
    }
    fclose(fp);

    printf("Total Memory: %.2f MB\n", total_memory / 1024.0);
    printf("Free Memory: %.2f MB\n\n", free_memory / 1024.0);
}
void print_uptime() {
    FILE *fp;
    long uptime;
    // Read uptime information
    fp = fopen("/proc/uptime", "r");
    if (!fp) {
        perror("Failed to open /proc/uptime");
        return;
    }
    fscanf(fp, "%ld", &uptime);
    fclose(fp);

    long hours = uptime / 3600;
    long minutes = (uptime % 3600) / 60;
    long seconds = uptime % 60;
    printf("System Uptime: %ld hours, %ld minutes, %ld seconds\n", hours, minutes, seconds);
}
int main() {
    print_processor_info();
    print_kernel_info();
    print_memory_info();
    print_uptime();

    return 0;
}

