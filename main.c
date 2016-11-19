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
void speakaction(int order);

int main() { 

    time_t now;
    struct tm *now_tm;
    int hour;
    int min;

    
    // raed configuration file

    // find the current time
    now = time(NULL);
    now_tm = localtime(&now);
    hour = now_tm->tm_hour;
    min = now_tm->tm_min;


    
    /*unsigned char hour;
    unsigned char min;

    const char data[] = "17:59";
    char *ep;

    hour = (unsigned char)strtol(data, &ep, 10);
    min = (unsigned char)strtol(ep+1, &ep, 10);
    */


    // matching the time and command

    // call the mpg321 to speak sound file
    /* spawn a child to run the mpg321 */

    pid_t pid = fork();

    // speak leader
    if (pid == 0 ) { // child process success fork 
        static char *argv[] = {"mpg321","leading.mp3" ,"-q", NULL};
        execv("/usr/bin/mpg321",argv);
        exit(127);
    } else {  // parent process 
        waitpid(pid,0,0);  //wait for child to exit 

        pid_t qid = fork();  

        if (qid == 0) {         // speak hour number
            talknumber(hour); 
            exit(127);
        } else {
            waitpid(qid,0,0);   //wait for child to exit 
            pid_t rid = fork();

            if (rid == 0 ) {    //speak nalika
                static char *argv[] = {"mpg321","hour.mp3","-q", NULL};
                execv("/usr/bin/mpg321",argv);
                exit(127);

            } else {
                waitpid(rid,0,0);  //wait for child to exit 
                pid_t sid = fork();
                
                if(sid == 0 ) {       //speak natee
                    talknumber(min);  
                } else {
                    waitpid(sid,0,0);  //wait for child to exit 
                    
                    pid_t tid = fork();

                    if (tid == 0) {  //speak action
                        static char *argv[] = {"mpg321","min.mp3" ,"-q", NULL};
                        execv("/usr/bin/mpg321",argv);
                    } else {
                        waitpid(tid,0,0);
                        speakaction(2); 

                    }
                }

            } 

        }
    }
    

    return 0;
}

// get the number from interger and translate to voice corsepond sound
void talknumber(int number) {

    // order of number
    int firstdigit;
    int seconddigit; 
    char firstdigitvoice[30];
    char seconddigitvoice[30];

    seconddigit = number/10;
    if (seconddigit == 1) {
        sprintf(seconddigitvoice,"10.mp3");
    } 

    if (seconddigit == 2) {
        sprintf(seconddigitvoice,"20.mp3");
    } 

    if (seconddigit == 3) {
        sprintf(seconddigitvoice,"30.mp3");
    } 

    if (seconddigit == 4) {
        sprintf(seconddigitvoice,"40.mp3");
    } 

    if (seconddigit == 5) {
        sprintf(seconddigitvoice,"50.mp3");
    } 

    if (seconddigit == 6) {
        sprintf(seconddigitvoice,"60.mp3");
    } 

    // find first digit
    firstdigit  = number%10;

    //if first digit is 1 call ed 
    if (number > 10 && firstdigit == 1 ) {
        sprintf(firstdigitvoice,"1.1.mp3");
    } else {
        sprintf(firstdigitvoice,"%d.mp3",firstdigit);
    }

    

    pid_t pid = fork();

    if (pid == 0 ) { // child process success fork 
        // speak secondigit
        char *ndargv[] = {"mpg321",seconddigitvoice ,"-q", NULL};
        execv("/usr/bin/mpg321",ndargv);
    } else {
        waitpid(pid,0,0);  //wait for child to exit 
        
        // speak firstdigit
        // if firstdigit is 0 dont speak
        if (number%10 != 0) {
            char *stargv[] = {"mpg321",firstdigitvoice ,"-q", NULL};
            execv("/usr/bin/mpg321",stargv);
        }
    }

}

/****************************
 * talk action 
 * speak specfic acition by order number
 */
void speakaction(int order) {
    char actionvoice[10];

    //pid_t pid = fork();

    sprintf(actionvoice,"action%d.mp3",order);
    

    //if (pid == 0 ) { // child process success fork 
        // speak secondigit
        char *argv[] = {"mpg321",actionvoice , NULL};
        execv("/usr/bin/mpg321",argv);
   // } else {
    //        waitpid(pid,0,0);  //wait for child to exit 

    //}
}

