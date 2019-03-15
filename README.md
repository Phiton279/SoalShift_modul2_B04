# SoalShift_modul2_B04
Pengerjaan Soal Shift Modul 2 Sisop 2019

# Soal Shift Modul 2

## Kelompok B4
#### ***Ersad Ahmad Ishlahuddin***

#### ***05111740000016***

#### ***Philip Antoni Siahaan***

#### ***05111740000111***

### **Nomor 1**

#### Soal

```
Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

```

#### Pemahaman Soal 1
Inti pada soal nomor 1 adalah mengganti nama sekaligus memindah suatu file yang berekstensi .png dari direktori tertentu ke "/home/[user]/modul2/gambar"

#### Jawaban
#### Source code
```c

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
```

#### Penjelasan
```c
DIR *imdir;
struct dirent *imp;
imdir = opendir ("/home/aeris/Pictures/");
```
Membuka direktori file yang akan diproses
```c
if (imdir != NULL){
while ((imp = readdir (imdir)) != NULL){
```
Membaca apakah direktorinya ada, lalu membaca file sampai akhir
```c
int len = strlen(imp->d_name)-4;
char name_d[234];
strcpy(name_d, imp->d_name);
```
Variabel len untuk menyimpan panjang string file yang dibaca tanpa ".png". Kemudian variabel name_d untuk menyimpan nama file yang telah diubah, menggunakan strcpy untuk mendapatkan nama file yang dibaca.
```c
if(strcmp(name_d+len, ".png") == 0)
```
Membaca apakah ekstensi file yang dibaca adalah .png
```c
char source[234]="/home/aeris/Pictures/";
char destination[234]="/home/aeris/modul2/gambar/";
```
Varibel source dan destination untuk menyimpan directory asal dan tujuan file
```c
for(int i = 0; i < 4; i++, len++)
{
    name_d[len] = '\0';
}
```
Menghapus ".png" pada name_d karena akan diganti dengan _grey.png
```c
strcat(name_d, "_grey.png");
strcat(source, imp->d_name);
strcat(destination, name_d);
```
Menambahkan _grey.png pada variabel name_d
Menambahkan nama-nama file yang akan dipindah
```c
char *argv[4] = {"mv", source, destination, NULL};
execv("/bin/mv", argv);
```
Menggunakan perintah mv untuk memindah file dari source ke destination
Lalu melakukan execv



### **Nomor 2**

#### Soal 2

```
Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab

```
#### Pemahaman Soal 2
Inti pada soal nomor 2 adalah mengubah permission dan menghapus file, namun dengan owner dan groupnya adalah www-data.

#### Jawaban 2
#### Source Code
```c
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

```

#### Penjelasan
```c
if ((chdir("/home/aeris/modul2/nomor2/hatiku/")) < 0) {
```
Mengubah direktori kerja
```c
char elennn[] = "elen.ku";
struct stat avail;
```
Deklarasi file yang akan diproses.
```c
if(!stat(elennn, &avail)) {
Mengecek status file
```
```c
struct passwd *sandi = getpwuid(avail.st_uid);
struct group *grup = getgrgid(avail.st_gid);
```
Menyimpan user dan group dari file
```c
if(strcmp(sandi->pw_name, "www-data") == 0 && strcmp(grup->gr_name, "www-data") == 0)
```
Membandingkan jika user dan groupnya adalah "www-data"
```c
chmod (elennn, 0777);
remove(elennn);
```
Mengubah permission dan Menghapus file

### **Nomor 3**

### Soal

```
Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat :
i)  mengekstrak file zip tersebut.
ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 
Catatan:  
- Gunakan fork dan exec.
- Gunakan minimal 3 proses yang diakhiri dengan exec.
- Gunakan pipe
- Pastikan file daftar.txt dapat diakses dari text editor
```
### Pemahaman Soal 3

```


```

### Jawaban

```
code

```

### Penjelasan


### **Nomor 4**

### Soal

```

Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

Contoh:
File makan_enak.txt terakhir dibuka pada detik ke-1
Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

Catatan: 
dilarang menggunakan crontab
Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst

```
### Pemahaman Soal 4

Padah soal ini kita diminta untuk membuat sebuah daemon yang bekerja untuk membuat file makan_sehat#.txt , # adalah angka ,
file makan sehat dibuat ketika seseorang telah melakukan akses terhadap file makan_enak.txt.file itu akan terbuat setrusnya setiap 5 detik
selama tigapuluh detik kedepan. sehingga ketika dia dibuka dan tidak diakses selama 30 detik kedepan maka akan terbentuk 6 item.


```C
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


void makefile(int angka){

    char filename[sizeof "makan_sehat10000.txt"];
    sprintf(filename, "makan_sehat%d.txt", angka);
    FILE* file_ptr = fopen(filename, "w");
    fclose(file_ptr);

}

int main() {
  pid_t pid, sid;
  int angka=1;

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

  if ((chdir("/home/phiton2/Documents/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    
    struct stat filestat;
    time_t now;
    struct tm *now_tm;
    struct tm *now_tm2;
    int hour,seconds,minutes,seconds1,minutes1,hour1;

    now = time(NULL);
    now_tm = localtime(&now);
    seconds = now_tm->tm_sec;
    minutes = now_tm->tm_min;
    hour = now_tm->tm_hour;

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
                printf("make");
            };
        }
        else if((((minutes-minutes1)*60)-seconds1)<=30 && (((minutes-minutes1)*60)-seconds1)>=0 ){
                makefile(angka);
                angka++;
                printf("make");
            }
    }


    printf("jangka waktu sec %d\n",((minutes-minutes1)*60)-seconds1);
    printf("jangka waktu min %d\n",minutes-minutes1);

    sleep(5);
  }
  
  exit(EXIT_SUCCESS);
}

```

### Penjelasan

Soal ini memakai template daemon, yang diberi tambahan adalah 
```C
if ((chdir("/home/phiton2/Documents/")) < 0) {
    exit(EXIT_FAILURE);
  }

```
sebagai directory yang lengkap dan menambahkan include time.h agar dapat mengakses time() , localtime() kemudian deklarasi int angka
yang dibutuhkan oleh program.

kemudian yang akan dijelaskan adalah fungsi makefile dan program yang berada dalam loop while.

```C
void makefile(int angka){

    char filename[sizeof "makan_sehat10000.txt"];
    sprintf(filename, "makan_sehat%d.txt", angka);
    FILE* file_ptr = fopen(filename, "w");
    fclose(file_ptr);

}

```

Dalam fungsi makefile merupakan fungsi yang akan membuat file makan_sehat

```C
char filename[sizeof "makan_sehat10000.txt"]; 

```
agar dapat membuat file yang increament maka membuat sebuah array char yang dihitung dahulu size nya untuk nantinya dilakukan sprintf

```C
sprintf(filename, "makan_sehat%d.txt", angka);

```

dalam sprint f kita menggabungkan string makan sehat dan increament angka. sehingga nantinya string filename bisa melakukan increament

```C
FILE* file_ptr = fopen(filename, "w");
fclose(file_ptr);

```
Kemudian file diciptakan dengan File dan fopen serta tambahan w untuk writetable , string yang dipakai adalah filename dan kemduian diclose.

Pada bagian while pertama-tama dilakukan deklarasi terlebih dahulu

```C
struct stat filestat;
time_t now;
struct tm *now_tm;
struct tm *now_tm2;
int hour,seconds,minutes,seconds1,minutes1,hour1;

```
pertama tama membuat sebuah struct stat yang bernama file stat , nantinya struct ini akan berisi data tentang akses file makan enak.
kemudian membuat now , sebagai deklrasi waktu yang akan dimasukan nilai time nantinya. kemudian membuat struct tm , tm_1 tm2 untuk mengisi waktu.
struct tm dalam c telah terprogram berisi nilai waktu2 yang bisa dipanggil.

```C
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

```
pada bagian ini adalah debuging untuk menampilkan file acces time yang berguna menjadi penanda terbukanya file.

```C
/*untuk jam saat ini*/
now = time(NULL);
now_tm = localtime(&now);
seconds = now_tm->tm_sec;
minutes = now_tm->tm_min;
hour = now_tm->tm_hour;

/*untuk jam file diakses*/
now_tm2 = localtime(&filestat.st_atim.tv_sec);
seconds1 = now_tm2->tm_sec;
minutes1 = now_tm2->tm_min;
hour1    = now_tm2->tm_hour;

```
Pada bagian ini kita akan akan memasukan nilai waktu ketika daemon sedang berjalan dalam while,sehingga akan terupdate terus nilai waktunya.
now_tm = localtime(&now) untuk memasukan waktu saat ini. kemudian dilakukan extract jam,menit,second kedalam sebuah variable nantinya dibandingkan
dengan waktu file diakses.

```C
if(hour1==hour){
    if(minutes==minutes1){
        if((seconds-seconds1)<=30){
                
            makefile(angka);
            angka++;
            printf("make");
        };
    }
    else if((((minutes-minutes1)*60)-seconds1)<=30 && (((minutes-minutes1)*60)-seconds1)>=0 ){
        makefile(angka);
        angka++;
        printf("make");
    }
}

```
pada bagian ini adalah penjelasan fungsi tentang cek waktu apakah file sudah dibuka 30 detik , apabila 
beda waktu file dibuka dan waktu sekarang kurang dari 30 detik  dengan menit sama dan jamnya juga maka akan dijalankan fungsi makefile.
apabila menitnya tidak sama makan perbedaan menit dikali 60 dan dicek apakah kurang dari 30 detik maka akan dilakukan pembuatan file juga


### **Nomor 5**

### Soal

```
Kerjakan poin a dan b di bawah:
a.Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
Ket:
Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
Per menit memasukkan log#.log ke dalam folder tersebut
‘#’ : increment per menit. Mulai dari 1
b.Buatlah program c untuk menghentikan program di atas.
NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.
```

### Pemahaman Soal 5

Didalam Soal ini kita diminta untuk membuat sebuag folder setiap 30 menit yang bernama date saat ini , dengan bentuk
dd:MM:yyyy-hh:mm,kemudian setioa 1 menit dibuat file log#.log dimana # adalah increament integer mulai dari 1.isi file log adalah isi dari file syslog.
kemudian b membuat program untuk menghentikan process tersebut.

#### Jawaban 5a

```C
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

```

#### Penjelasan 5a
Didalam program ini kita menggunakan template daemon, Kemudian penjelasan pertama dari while dari int main adalah sebagai berikut

```C  
    time_t now;
    struct tm *now_tm;
    int hour,seconds,minutes,day,month,years;

```
Pertama tama kita melakukan dekrasai variable yang berisi now , now_tm dan variable waktu untuk mengisi jam,second,menit dll.

```C
now = time(NULL);
now_tm = localtime(&now);

```
Didalam ini kita melakukan pengambilan local time machine kita yang sekarang dan memasukanya kedalam struct tm ,sebagai informasi
struct tm memiloki banyak variable sepert tm_mon untuk mengambil bulan sehingga mudah untuk mengaksesnya

```C
    seconds = now_tm->tm_sec;
    minutes = now_tm->tm_min;
    hour = now_tm->tm_hour;
    day = now_tm->tm_mday;
    month = now_tm->tm_mon;
    years = now_tm->tm_year;

```
Dibagian ini kita melakukan pengambilan semua variable yang dibutuhkan untuk membuat nama folder. kemudian mengisikannya kedalam variable

``` C
makefolder(hour,minutes,day,month+1,years-100,renwaktu+1);

```
setelah itu kita melakukan pemanggilan fungsi makefolder ,kita memasukan parameter yang diperlukan dan ada penambahan yakni 
month ditambah satu agar sesuai dengan bulan sekarang , years dikurang sertaus agar dapat menampilakan 19 bila tahun 019 , 
kemudian ada rentang waktu untuk menjadi nilai # pada file log.


```C
    char filename[sizeof "dd:MM:yyyy-hh:mm"];
    sprintf(filename, "%02d:%02d:20%02d-%02d:%02d", day,month,years,hour,minutes);
    make_directory(filename,angka);

```
Setelah itu kita akan membuat sebuah directory sehinggaa kita memerlukan penamaan ,awalnya kita membuat char file name untuk tempat folder kemudian kita memberikan size seuai dengan format yang diminta kemudian , kita mengisi filename dengan format waktu.disini kita menggunakan %02d sebagai integer dan 2 digit. sehingga ketika 1 menjadi 01. kemudian
lanjut kefungsi make directory






