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
#include <pwd.h>
#include <grp.h>

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

    if ((chdir("/home/aeris/modul2/nomor2/hatiku/")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    while(1) {
        char elennn[] = "elen.ku";
        struct stat avail;
        
        if(!stat(elennn, &avail)) 
        {
            struct passwd *sandi = getpwuid(avail.st_uid);
            struct group *grup = getgrgid(avail.st_gid);

            if(strcmp(sandi->pw_name, "www-data") == 0 && strcmp(grup->gr_name, "www-data") == 0)
            {
                chmod (elennn, 0777);
                remove(elennn);
            }
        }    
        sleep(3);
    }
    exit(EXIT_SUCCESS);
}
