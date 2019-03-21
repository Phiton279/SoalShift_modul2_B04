#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/dir.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main(){
    int status, pipa[2];
    pid_t child1, child2, child3;
    pipe(pipa);

    child1 = fork();
    if(child1 == 0){
        execlp("unzip", "unzip", "campur2.zip", NULL);
    }else{
        while((wait(&status))>0);
        child2 = fork();
        if(child2 == 0){
            execlp("touch", "touch", "daftar.txt", NULL);
        }else {
            while((wait(&status))>0);
            child3 = fork();
            if(child3 == 0){
                close(pipa[0]);
                dup2(pipa[1], 1);
                close(pipa[1]);
                execlp("ls", "ls", "campur2", NULL);
            }else{
                while((wait(&status))>0);
                int daFile = open("daftar.txt", O_WRONLY);
                close(pipa[1]); 
                dup2(pipa[0], 0);
                close(pipa[0]);
                dup2(daFile, 1);
                close(daFile);
                execlp("grep", "grep", ".txt$", NULL);
            }
        }
    }
    return 0;
}