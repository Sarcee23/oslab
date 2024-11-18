/*
*Name : Subhayan Roy Chowdhury
 *Roll : 002211001096
 *Class :IT UG3 A2
 * Assignment 5
 * Compilation: 
 * gcc 096_5.c
 * Execution
 * ./a.out
 *
 * Sample output:
*Starting threads..
*Threads created. Waiting for them to finish..(they won't)..
*Thread 1 : attempt to lock mutex1
*Thread 2 attempting to lock mutex2
*Thread 2 locked mutex2
*Thread 1 locked mutex1
*Thread 2 attempting to lock mutex1
*Thread 1: attempting to lock mutex2
*Thread 1: couldn't get lock on mutex2. Still attempting...
*Thread 1: couldn't get lock on mutex2. Still attempting...
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>

#define MAX_AMOUNT 50
#define DEADLOCK_CHECK_INTERVAL 5 //seconds


//Global variables
int Total_1 = 1000;
int Total_2 = 1000;

//Mutexes

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

//function to get current timestamp
long long current_timestamp(){
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC,&ts);
        return(long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;

        }
//function for thread 1

void* thread_function_1(void* arg){
        while(1){
        int amount = rand() % (MAX_AMOUNT +1);
        printf("Thread 1 : attempt to lock mutex1\n");
        pthread_mutex_lock(&mutex1);
        printf("Thread 1 locked mutex1 \n");

        //simulate some processing time
        usleep(100000);//100ms

        printf("Thread 1: attempting to lock mutex2\n");
        long long start_time = current_timestamp();
        while(pthread_mutex_trylock(&mutex2)!=0){
                long long current_time = current_timestamp();
                if((current_time - start_time)/1000000000LL >= DEADLOCK_CHECK_INTERVAL){
        printf("Thread 1: couldn't get lock on mutex2. Still attempting...\n");
        start_time = current_time;
        }
        usleep(10000); //10ms
                }
        pthread_mutex_lock(&mutex2);
        printf("Thread 1 locked mutex2 \n");

        //Manipulate locks
        Total_1 -= amount;
        Total_2 += amount;

        printf("Thread 1 : Subtracted %d from Total_1, Added to Total_2 \n",amount);
        printf("Current totals : Total_1 = %d , Total_2 = %d \n",Total_1,Total_2);

pthread_mutex_unlock(&mutex2);
pthread_mutex_unlock(&mutex1);

        pthread_mutex_unlock(&mutex2);
        printf("Thread 1: unlocked mutex2\n");
        pthread_mutex_unlock(&mutex1);
        printf("Thread 1 : unlocked mutex1\n");

//sleep to allow context switch
usleep(1000);
        }
return NULL;

        }


//function for thread 2
void* thread_function_2(void* arg){
        while(1){
        int amount = rand() % (MAX_AMOUNT + 1);
        printf("Thread 2 attempting to lock mutex2\n");
        pthread_mutex_lock(&mutex2);
        printf("Thread 2 locked mutex2\n");

        //simulate some processing time
        usleep(1000);

        printf("Thread 2 attempting to lock mutex1\n");
        pthread_mutex_lock(&mutex1);
        printf("Thread 2 locked mutex1\n");

        //Manipulate totals
        Total_2 -= amount;
        Total_1 += amount;

        printf("Thread 2 : Subtracted %d from Total_2, Added to Total_1 \n",amount);
        printf("Current totals : Total_1 = %d, Total_2 = %d\n",Total_1,Total_2);

pthread_mutex_unlock(&mutex1);
printf("Thread 2 : Unlocked mutex1\n");
pthread_mutex_unlock(&mutex2);
printf("Thread 2 : Unlocked mutex2\n");

        //sleep to allow context switch
        usleep(1000);

        }
return NULL;

}

int main(){
srand(time(NULL)); //seed for random number generation
pthread_t thread1,thread2;

printf("Starting threads..\n");
//create threads
pthread_create(&thread1,NULL,thread_function_1,NULL);
pthread_create(&thread2,NULL,thread_function_2,NULL);

printf("Threads created. Waiting for them to finish..(they won't)..\n");
//wait for threads to finish (they won't in this particular case)
pthread_join(thread1,NULL);
pthread_join(thread2,NULL);

printf("This line will never be reached due to deadlock\n");
return 0;

        }