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


---------------------------------------------------------------------------
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

int main()
{
    pid_t child_id1;
    int status;
    int inipipe[4];
    char hasil[1024];

    child_id1 = fork();

    if(child_id1 == 0){
      execl("/usr/bin/unzip","unzip", "campur2.zip", NULL);
    }else{



     pid_t child_id2;
        int p2;
        
 while(wait(&status)>0);

        pipe(inipipe); //membuat pipe1
        pipe(inipipe+2);//membuat pipe2

        child_id2 = fork();
        if(child_id2==0){

          close(inipipe[0]);
          close(inipipe[2]);
          close(inipipe[3]);

          dup2(inipipe[1], STDOUT_FILENO); // menyimpan hasil ls 
          close(inipipe[1]);
      execlp("ls","ls","/home/zahrul/praktikum2/baru/campur2",(char*) NULL); //
      
        }
  else{


      pid_t child_id3;
             child_id3 = fork();
        
     if(child_id3==0){


               close(inipipe[1]);
               dup2(inipipe[0],STDIN_FILENO); // membaca hasil ls  
               close(inipipe[0]);

               close(inipipe[2]);
               dup2(inipipe[3],STDOUT_FILENO); // untuk menyimpan hasil grep
               close(inipipe[3]);
   execlp("grep", "grep",".txt$",(char*) NULL); 
             
            }else{

              close(inipipe[1]);
  //            close(inipipe[0]);
//              close(inipipe[3]);
 
              int cetak = read(inipipe[2],hasil,sizeof(hasil)); //mengambil hasil grep

              close(inipipe[2]);
              FILE* file;
              file = fopen("daftar.txt","w+");
             fprintf(file," Berikut Berupa File berformat .txt :\n%.*s\n",cetak,hasil);//memasukan hasil ls grep ke file
             printf("Berikut Berupa File berformat .txt :\n%.*s\n",cetak,hasil); // untuk mencetak hasil ls grep

              fclose(file);
            }
            
        }
    }
}