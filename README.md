# SoalShift_modul2_B04
Pengerjaan Soal Shift Modul 2 Sisop 2019

# Soal Shift Modul 2

## Kelompok B4

### **Nomor 1**

#### Soal

```
Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

```

#### Pemahaman Soal 1


#### Jawaban
```
code

```

#### Penjelasan

### **Nomor 2**

#### Soal 2

```
Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab

```
#### Pemahaman Soal 2

#### Jawaban 2
```
code

```

#### Penjelasan


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
Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
Ket:
Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
Per menit memasukkan log#.log ke dalam folder tersebut
‘#’ : increment per menit. Mulai dari 1
Buatlah program c untuk menghentikan program di atas.
NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.
```

### Pemahaman Soal 5

#### Jawaban
```
code

```

#### Penjelasan

