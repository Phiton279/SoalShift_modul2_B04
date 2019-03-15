#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <syslog.h>


void make_directory(const char* name,int angka) 
{   char location[]="/home/phiton2/log/";
    char dirname[sizeof "mkdir /home/phiton2/log/dd:mm:yyyy-hh:mm"];
    char filesname[sizeof "/home/phiton2/log/dd:mm:yyyy-hh:mm"];
    sprintf(dirname, "mkdir %s%s/", location,name);
    sprintf(filesname, "%s%s/", location,name);
    printf("%s\n",dirname);
    printf("%s\n",filesname);

    system(dirname);

  while(angka<=30){

    FILE *fptr1, *fptr2; 
    
    char source[] = "/var/log/syslog";
    char c; 

  
    fptr1 = fopen(source, "r"); 
    if (fptr1 == NULL) 
    { 
        printf("Cannot open file --%s \n",source); 
        exit(0); 
    } 
    printf("%s\n",source);
    
    char filename[sizeof "log10000.log"];
    sprintf(filename, "%slog%d.log",filesname,angka);
    FILE* file_ptr = fopen(filename, "w");
    fclose(file_ptr);

    fptr2 = fopen(filename, "w"); 
    if (fptr2 == NULL) 
    { 
        printf("Cannot open file xx%s \n",filename); 
        exit(0); 
    } 
  

    c = fgetc(fptr1); 
    while (c != EOF) 
    { 
        fputc(c, fptr2); 
        c = fgetc(fptr1); 
    } 
  
  
    fclose(fptr1); 
    fclose(fptr2);
    
    angka+=1;
    sleep(60);
  }
} 



void makefolder(int hour,int minutes,int day,int month,int years,int angka){

    char filename[sizeof "dd:MM:yyyy-hh:mm"];
    sprintf(filename, "%02d:%02d:20%02d-%02d:%02d", day,month,years,hour,minutes);
    make_directory(filename,angka);

}


int main() {
  pid_t pid, sid;
  int renwaktu=0;

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
    time_t now;
    struct tm *now_tm;
    int hour,seconds,minutes,day,month,years;


    now = time(NULL);
    now_tm = localtime(&now);
    seconds = now_tm->tm_sec;
    minutes = now_tm->tm_min;
    hour = now_tm->tm_hour;
    day = now_tm->tm_mday;
    month = now_tm->tm_mon;
    years = now_tm->tm_year;

    makefolder(hour,minutes,day,month+1,years-100,renwaktu+1);
    sleep(1);
  }
  
  exit(EXIT_SUCCESS);
}