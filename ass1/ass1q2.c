/*********************************************************************************************************************************************************************/
//Name : Subhayan Roy Chowdhury
////Roll No : 002211001096
////Assignment 1b: to get system environment variables and set custom environment variables using getenv() and setenv()
////IT UG3 A2
//
////input requied: NA
//
////output generated : system variables and custom env variables
//
////compilation : gcc ass1b.c ; execution : ./a.out
//
////sample input: NA
//
//// sample output: Displaying environment variables
////USER = be2296
////HOME = /home/usr/student/ug/yr22/be2296
////HOST is not set
////ARCH is not set
////DISPLAY is not set
////PRINTER is not set
////PATH = /usr/lib64/qt-3.3/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/usr/student/ug/yr22/be2296/.local/bin:/home/usr/student/ug/yr22/be2296/bin
////
//// Setting new environment variables:
//// MY_VAR1 is set succesfully
//// MY_VAR2 is set succesfully
//// Display the new set variables:
//// MY_VAR1 = Hello
//// MY_VAR2 = World
///*****************************************************************************************************************************************************************/

#include <stdio.h>
#include<stdlib.h>

int main(){
//array of env variables to display
        const char* env_vars[]={"USER","HOME","HOST","ARCH","DISPLAY","PRINTER","PATH"};
int num_vars = sizeof(env_vars)/sizeof(env_vars[0]);

int i;
//displaying environment variables using getenv
printf("Displaying environment variables \n");
for( i=0;i<num_vars;i++){
        char *value = getenv(env_vars[i]);
        if(value!=NULL){
                printf("%s = %s\n",env_vars[i],value);
                }
        else{
        printf("%s is not set\n",env_vars[i]);
                }
        }

//setting environment variables using setenv
printf("\n Setting new environment vaiables:\n");
if(setenv("MY_VAR1","Hello",1)==0){
        printf("MY_VAR1 is set succesfully\n");
        }
else{
        printf("Failed to set MY_VAR1\n");
        }
if(setenv("MY_VAR2","World",1)==0){
        printf("MY_VAR2 is set succesfully\n");
        }
else{
        printf("Failed to set MY_VAR2\n");
        }

//Display the new set variables
printf("Display the new set variables:\n");
printf("MY_VAR1 = %s\n",getenv("MY_VAR1"));
printf("MY_VAR2 = %s\n",getenv("MY_VAR2"));

return 0;
}

