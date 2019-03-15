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

int main() {
    pid_t pid, sid;

    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();

    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while(1) {
        DIR *imdir;
        struct dirent *imp;
        imdir = opendir ("/home/aeris/Pictures/");
        if (imdir != NULL){
            while ((imp = readdir (imdir)) != NULL){
                int len = strlen(imp->d_name)-4;
                char name_d[234];
                
                strcpy(name_d, imp->d_name);
                if(strcmp(name_d+len, ".png") == 0){
                    char source[234]="/home/aeris/Pictures/";
                    char destination[234]="/home/aeris/modul2/gambar/";
                    for(int i = 0; i < 4; i++, len++)
                    {
                        name_d[len] = '\0';
                    }
                    strcat(name_d, "_grey.png");
                    strcat(source, imp->d_name);
                    strcat(destination, name_d);
                    pid_t child_id;
                    int status;
                    
                    child_id = fork();

                    if (child_id == 0) {
                        char *argv[4] = {"mv", source, destination, NULL};
                        execv("/bin/mv", argv);
                    }
                    else{
                        while ((wait(&status)) > 0);
                    }
                
                }
        
            }
        }
        closedir(imdir);
        sleep(1);
    }
    exit(EXIT_SUCCESS);
}