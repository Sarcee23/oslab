#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

/* Structure to store pair values (X, Y) and computed results (A, B, C, D, E) */
typedef struct {
    int X, Y;
    int A, B, C, D, E;
} Computation;

/* Shared memory and synchronization objects */
Computation *shared_memory; 
HANDLE hMapFile;
HANDLE barrier_mutex; // Synchronization mutex
int num_pairs; // Number of (X, Y) pairs

/* Function to synchronize threads */
void barrier_wait(HANDLE barrier_mutex) {
    WaitForSingleObject(barrier_mutex, INFINITE); 
    ReleaseMutex(barrier_mutex);
}

/* Thread function to compute values A and E for each pair */
DWORD WINAPI calculate_A_and_E(LPVOID arg) {
    for (int i = 0; i < num_pairs; i++) {
        barrier_wait(barrier_mutex); // Synchronize before calculation

        shared_memory[i].A = shared_memory[i].X * shared_memory[i].Y;
        shared_memory[i].E = (shared_memory[i].X + shared_memory[i].Y) *
                             (shared_memory[i].X - shared_memory[i].Y);

        barrier_wait(barrier_mutex); // Synchronize after calculation
    }
    return 0;
}

/* Thread function to compute values B and D for each pair */
DWORD WINAPI calculate_B_and_D(LPVOID arg) {
    for (int i = 0; i < num_pairs; i++) {
        barrier_wait(barrier_mutex); // Synchronize before calculation

        shared_memory[i].B = (shared_memory[i].X * shared_memory[i].Y) / 2;

        // Avoid division by zero in calculation of D
        if (shared_memory[i].X + shared_memory[i].Y != 0) {
            shared_memory[i].D = (shared_memory[i].X * shared_memory[i].Y) /
                                 (shared_memory[i].X + shared_memory[i].Y);
        } else {
            shared_memory[i].D = 0;
        }

        barrier_wait(barrier_mutex); // Synchronize after calculation
    }
    return 0;
}

/* Thread function to compute value C for each pair */
DWORD WINAPI calculate_C(LPVOID arg) {
    for (int i = 0; i < num_pairs; i++) {
        barrier_wait(barrier_mutex); // Synchronize before calculation

        shared_memory[i].C = shared_memory[i].X + shared_memory[i].Y;

        barrier_wait(barrier_mutex); // Synchronize after calculation
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_pairs>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Parse number of (X, Y) pairs
    num_pairs = atoi(argv[1]);
    if (num_pairs <= 0) {
        fprintf(stderr, "Please provide a positive integer for the number of pairs.\n");
        return EXIT_FAILURE;
    }

    // Create shared memory
    hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE,
                                  0, sizeof(Computation) * num_pairs, "SharedMemory");
    if (hMapFile == NULL) {
        fprintf(stderr, "Could not create file mapping object (%lu).\n", GetLastError());
        return EXIT_FAILURE;
    }
    shared_memory = (Computation*) MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0,
                                                 sizeof(Computation) * num_pairs);
    if (shared_memory == NULL) {
        fprintf(stderr, "Could not map view of file (%lu).\n", GetLastError());
        CloseHandle(hMapFile);
        return EXIT_FAILURE;
    }

    // Initialize random values for pairs (X, Y)
    srand((unsigned) time(NULL));
    for (int i = 0; i < num_pairs; i++) {
        shared_memory[i].X = rand() % 10;
        shared_memory[i].Y = rand() % 10;
    }

    // Create synchronization mutex
    barrier_mutex = CreateMutex(NULL, FALSE, NULL);
    if (barrier_mutex == NULL) {
        fprintf(stderr, "Could not create mutex (%lu).\n", GetLastError());
        UnmapViewOfFile(shared_memory);
        CloseHandle(hMapFile);
        return EXIT_FAILURE;
    }

    // Create threads
    HANDLE threads[3];
    threads[0] = CreateThread(NULL, 0, calculate_A_and_E, NULL, 0, NULL);
    threads[1] = CreateThread(NULL, 0, calculate_B_and_D, NULL, 0, NULL);
    threads[2] = CreateThread(NULL, 0, calculate_C, NULL, 0, NULL);

    // Wait for threads to finish
    WaitForMultipleObjects(3, threads, TRUE, INFINITE);

    // Display the results
    printf("X\tY\tA\tB\tC\tD\tE\n");
    for (int i = 0; i < num_pairs; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", shared_memory[i].X, shared_memory[i].Y,
               shared_memory[i].A, shared_memory[i].B, shared_memory[i].C,
               shared_memory[i].D, shared_memory[i].E);
    }

    // Clean up resources
    CloseHandle(barrier_mutex);
    UnmapViewOfFile(shared_memory);
    CloseHandle(hMapFile);
    for (int i = 0; i < 3; i++) {
        CloseHandle(threads[i]);
    }

    return 0;
}
