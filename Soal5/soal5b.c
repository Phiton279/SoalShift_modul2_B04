#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int main (){
    char pid[500];
    FILE *process;
    process = popen("pidof soal5a","r");
    fgets(pid,500,process);
    
    kill(atoi(pid), SIGKILL);

    return 0;

}