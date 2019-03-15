#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

struct stat filestat;
time_t now;
struct tm *now_tm;
struct tm *now_tm2;
int hour,seconds,minutes,seconds1,minutes1,hour1;


void makefile(int angka){

    char filename[sizeof "makan_sehat10000.txt"];
    sprintf(filename, "makan_sehat%03d.txt", angka);
    FILE* file_ptr = fopen(filename, "w");
    fclose(file_ptr);

}

/*
int timelapse(int angka){
  
    now = time(NULL);
    now_tm = localtime(&now);
    seconds = now_tm->tm_sec;
    minutes = now_tm->tm_min;
    hour = now_tm->tm_hours;

    stat("makan_enak.txt",&filestat);
    
    printf(" File access time %s",
            ctime(&filestat.st_atim.tv_sec)
          );
    printf(" File modify time %s",
            ctime(&filestat.st_mtime)
          );
    printf("File changed time %s",
            ctime(&filestat.st_ctime)
          );
    
    now_tm2 = localtime(&filestat.st_atim.tv_sec);
    seconds1 = now_tm2->tm_sec;
    minutes1 = now_tm2->tm_min;
    hour1    = now_tm2->tm_hour;

    if(hour1==hour){
        if(minutes==minutes1){
            if((seconds-seconds1)<=30){
                
                makefile(angka);
                angka++;
            };
        }
        else{
            if((((minutes-minutes1)*60)-seconds1)<=30){
                makefile(angka);
                angka++;
            }
        }
    }


    printf("jangka waktu sec %d\n",seconds1);
    printf("jangka waktu sec %d\n",seconds);
    printf("jangka waktu min %d\n",minutes);
    return angka;
}

*/

int main() {
  int angka=1;

  while(1) {
    now = time(NULL);
    now_tm = localtime(&now);
    seconds = now_tm->tm_sec;
    minutes = now_tm->tm_min;
    hour = now_tm->tm_hours;

    stat("makan_enak.txt",&filestat);
    /* newline included in ctime() output */
    printf(" File access time %s",
            ctime(&filestat.st_atim.tv_sec)
          );
    printf(" File modify time %s",
            ctime(&filestat.st_mtime)
          );
    printf("File changed time %s",
            ctime(&filestat.st_ctime)
          );
    
    now_tm2 = localtime(&filestat.st_atim.tv_sec);
    seconds1 = now_tm2->tm_sec;
    minutes1 = now_tm2->tm_min;
    hour1    = now_tm2->tm_hour;

    if(hour1==hour){
        if(minutes==minutes1){
            if((seconds-seconds1)<=30){
                
                makefile(angka);
                angka++;
            };
        }
        else{
            if((((minutes-minutes1)*60)-seconds1)<=30){
                makefile(angka);
                angka++;
            }
        }
    }


    printf("jangka waktu sec %d\n",seconds1);
    printf("jangka waktu sec %d\n",seconds);
    printf("jangka waktu min %d\n",minutes);
    sleep(5);
  }
  
}
