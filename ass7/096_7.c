/*
 *Name : Subhayan Roy Chowdhury
 *Roll : 002211001096
 *Class :IT UG3 A2
 * Assignment 7
 * Compilation:
 * gcc 096_7.c
 * Execution
 * ./a.out
 *
 * Sample output: [be2296@localhost ass6]$ ./a.out
* $ ./computation_program 5
*X    Y    A    B    C    D    E
*3    2    6    3    5    1    5
*4    1    4    2    5    0    3
*7    6   42   21   13    3    1
*2    8   16    8   10    1   -48
*5    3   15    7    8    1   16
*
 * */



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

/* 
 * Structure to store pair values (X, Y) and computed results (A, B, C, D, E)
 *   X, Y - Input values
 *   A, B, C, D, E - Computed values based on X and Y
 */
typedef struct {
    int X, Y;
    int A, B, C, D, E;
} Computation;

/* Shared memory pointer */
Computation *shared_memory; 

/* Synchronization barrier to coordinate threads */
pthread_barrier_t barrier; 
int num_pairs; // Number of (X, Y) pairs

/* Thread function to compute values A and E for each pair */
void* calculate_A_and_E(void *arg) {
    for (int i = 0; i < num_pairs; i++) {
        pthread_barrier_wait(&barrier); // Synchronize before calculation

        shared_memory[i].A = shared_memory[i].X * shared_memory[i].Y;
        shared_memory[i].E = (shared_memory[i].X + shared_memory[i].Y) * 
                             (shared_memory[i].X - shared_memory[i].Y);

        pthread_barrier_wait(&barrier); // Synchronize after calculation
    }
    return NULL;
}

/* Thread function to compute values B and D for each pair */
void* calculate_B_and_D(void *arg) {
    for (int i = 0; i < num_pairs; i++) {
        pthread_barrier_wait(&barrier); // Synchronize before calculation

        shared_memory[i].B = (shared_memory[i].X * shared_memory[i].Y) / 2;
        
        // Avoid division by zero in calculation of D
        if (shared_memory[i].X + shared_memory[i].Y != 0) {
            shared_memory[i].D = (shared_memory[i].X * shared_memory[i].Y) / 
                                 (shared_memory[i].X + shared_memory[i].Y);
        } else {
            shared_memory[i].D = 0;
        }

        pthread_barrier_wait(&barrier); // Synchronize after calculation
    }
    return NULL;
}

/* Thread function to compute value C for each pair */
void* calculate_C(void *arg) {
    for (int i = 0; i < num_pairs; i++) {
        pthread_barrier_wait(&barrier); // Synchronize before calculation

        shared_memory[i].C = shared_memory[i].X + shared_memory[i].Y;

        pthread_barrier_wait(&barrier); // Synchronize after calculation
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_pairs>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Parse number of (X, Y) pairs
    num_pairs = atoi(argv[1]);
    if (num_pairs <= 0) {
        fprintf(stderr, "Please provide a positive integer for the number of pairs.\n");
        exit(EXIT_FAILURE);
    }

    // Create and configure shared memory for storing pairs and results
    int shm_fd = shm_open("/shared_computation_memory", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(Computation) * num_pairs);
    shared_memory = mmap(0, sizeof(Computation) * num_pairs, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);

    // Initialize random values for pairs (X, Y)
    srand(time(NULL));
    for (int i = 0; i < num_pairs; i++) {
        shared_memory[i].X = rand() % 10;
        shared_memory[i].Y = rand() % 10;
    }

    // Initialize synchronization barrier for 3 threads
    pthread_barrier_init(&barrier, NULL, 3);

    // Create threads for each set of calculations
    pthread_t th1, th2, th3;
    pthread_create(&th1, NULL, calculate_A_and_E, NULL);
    pthread_create(&th2, NULL, calculate_B_and_D, NULL);
    pthread_create(&th3, NULL, calculate_C, NULL);

    // Wait for all threads to finish their tasks
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);

    // Display the results
    printf("X\tY\tA\tB\tC\tD\tE\n");
    for (int i = 0; i < num_pairs; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", shared_memory[i].X, shared_memory[i].Y,
               shared_memory[i].A, shared_memory[i].B, shared_memory[i].C,
               shared_memory[i].D, shared_memory[i].E);
    }

    // Clean up resources
    pthread_barrier_destroy(&barrier);
    shm_unlink("/shared_computation_memory");
    return 0;
}
