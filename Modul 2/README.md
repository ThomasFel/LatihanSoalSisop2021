# Latihan Soal Sisop 2021 - Modul 2

Mengambil dari tautan berikut: [MODUL 2](https://github.com/arsitektur-jaringan-komputer/Modul-Sisop/tree/master/2021/Modul2 "Goto MODUL 2").

## SOAL 1 ##

Modifikasi kode [soal1.c](https://github.com/arsitektur-jaringan-komputer/Modul-Sisop/blob/master/2021/Modul2/soal1.c "Goto soal1.c") agar outputnya menjadi angka urut dari 0 sampai 100, tanpa menghapus fungsi yang sudah ada dan menggunakan <b>wait</b>.

## SOAL 2 ##

Buatlah sebuah program yang dapat meng-<i>copy</i> folder beserta semua isi dari folder di `/home/<USER>/Downloads` ke dalam sebuah folder dengan format nama '<b>tanggal-bulan-tahun_jam:menit:detik</b>' (contoh: 26-03-2021_16:22:09). Gunakan <b>fork</b>, <b>exec</b>, dan <b>wait</b>.

## SOAL 3 ##

Buatlah sebuah <b>daemon</b> yang berjalan setiap 10 detik yang dapat melakukan <i>backup</i> isi dari <i>file</i> `error.txt` dan disimpan ke dalam <i>file</i> '<b>error.log.{no}</b>' (contoh: error.log.1, error.log.2, ...), lalu menghapus isi `error.txt` tersebut sehingga <i>file</i> tersebut kosong kembali. Tidak diperbolehkan menggunakan <b>exec</b> dan <b>system</b>.
