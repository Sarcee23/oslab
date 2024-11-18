/********************************************************************************************************************
 * Name: Subhayan Roy Chowdhury
 * Roll no : 002211001096
 * Date: 12/08/2024
 * IT UG3 A2
 *
 * Assignment no: 2a
 * Assignment details: Catch the signal SIGINT and display "HAHA not stopping". Use signal system call. Always use perror to check the retrun status of library/system call.
 * Input Description: Ctrl+c
 * Output Description: Ha ha, Not Stopping
 *
 * Compilation command: gcc 1096_2a.c -o 2a
 * Execution command: ./2a
 *
 * Sample input: Ctrl+c Ctrl+c Ctrl+c Ctrl+z
 * Sample output:
 * Press Ctrl+C to trigger SIGINT.
 * ^CHa ha, Not Stopping!
 * ^CHa ha, Not Stopping!
 * ^CHa ha, Not Stopping!
 * ^Z
 * [2]+  Stopped                 ./2a
 *
 * *****************************************************************************************************************/


//import the necessary libraries
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>//for handling signals
#include<unistd.h>//for sleep function

//create the function to override the usual function of ctrl+c handling the signal
void sigint_handler(int sig){
        printf("Ha ha, Not Stopping!\n");

        }


int main(){

//error condition
if(signal(SIGINT,sigint_handler)== SIG_ERR){
        perror("Signal");
        exit(1);
        }

//display the msg to user
printf("Press Ctrl+C to trigger SIGINT.(Ctrl+Z to stop)\n");
while(1){
        sleep(1);//sleep 1 second
        }

return 0;}
