# Latihan Soal Sisop 2021 - Modul 4

Mengambil dari tautan berikut: [MODUL 4](https://github.com/arsitektur-jaringan-komputer/Modul-Sisop/tree/master/2021/Modul4 "Goto MODUL 4").

## SOAL 1 ##

Buat sebuah <i>filesystem</i> yang mengarah ke `/home/<user>/Downloads`, <i>filesystem</i> bernama '<b>JagoFS</b>', sehingga nama <i>file</i> yang ada pada folder tersebut akan ditampilkan '<b>Jago_[nama_file]</b>'. Sebagai contoh `contohfile.txt` menjadi `Jago_contohfile.txt`. <I>Filesystem</i> ini hanya memiliki akses <b>read</b>. Contoh lainnya, `Jago_contohkedua.txt` menjadi `Jago_Jago_contohkedua.txt`.

## SOAL 2 ##

Buat sebuah <i>filesystem</i> yang mengarah ke `/home/<user>/Documents`. <i>Filesystem</i> ini memiliki fitur pencatatan, ketika <i>file</i> pada folder tersebut dimodifikasi, kejadian perubahannya akan dicatat pada suatu <i>file log</i> dengan format '<b>.time:date...</b>'. Jika <i>file log</i> belum ada, maka secara otomatis akan membuat <i>file log</i> baru sebelum melakukan pencatatan.
