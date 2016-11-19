/********************************************
 *  program to talk depond on time
 *   it use mpg321 to read the mp3 files. 
 *   you call this program by Cron
 ********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "delay.h"

// declare function
void talknumber(int number);

int main() { 

    
    // raed configuration file

    // find the current time
    //time_t seconds = time(NULL);

    //printf("%ld\n",seconds);

    // matching the time and command

    // call the mpg321 to speak sound file
    /* spawn a child to run the mpg321 */

    pid_t pid = fork();

    // speak leader
    if (pid == 0 ) { // child process success fork 
        static char *argv[] = {"mpg321","leading.mp3" , NULL};
        execv("/usr/bin/mpg321",argv);
        exit(127);
    } else {  // parent process 
        waitpid(pid,0,0);  //wait for child to exit 

        pid_t qid = fork();  

        if (qid == 0) {         // speak hour number
            talknumber(11); 
            exit(127);
        } else {
            waitpid(qid,0,0);   //wait for child to exit 
            pid_t rid = fork();

            if (rid == 0 ) {    //speak nalika
                static char *argv[] = {"mpg321","hour.mp3" , NULL};
                execv("/usr/bin/mpg321",argv);
                exit(127);

            } else {
                waitpid(rid,0,0);  //wait for child to exit 
                pid_t sid = fork();
                
                if(sid == 0 ) {    
                    talknumber(31);  //speak  natee
                } else {
                    waitpid(sid,0,0);  //wait for child to exit 
                    static char *argv[] = {"mpg321","min.mp3" , NULL};
                    execv("/usr/bin/mpg321",argv);
                }

            } 

        }
    }
    

    return 0;
}

void timetalk() {
}

// get the number from interger and translate to voice corsepond sound
void talknumber(int number) {

    // order of number
    int firstdigit;
    int seconddigit; 
    char firstdigitvoice[30];
    char seconddigitvoice[30];

    //const char *strnumber[] = {"zero","one","two","three","four","five","six","seven","eight","nine","ten"}; 
    seconddigit = number/10;
    if (seconddigit == 1) {
        sprintf(seconddigitvoice,"10.mp3");
    } 

    if (seconddigit == 2) {
        sprintf(seconddigitvoice,"20.mp3");
    } 

    firstdigit  = number%10;
    sprintf(firstdigitvoice,"%d.mp3",firstdigit);

    pid_t pid = fork();

    if (pid == 0 ) { // child process success fork 
        // speak secondigit
        char *ndargv[] = {"mpg321",seconddigitvoice , NULL};
        execv("/usr/bin/mpg321",ndargv);
    } else {
        waitpid(pid,0,0);  //wait for child to exit 

        // speak firstdigit
        char *stargv[] = {"mpg321",firstdigitvoice , NULL};
        execv("/usr/bin/mpg321",stargv);
    }
    
    

}

