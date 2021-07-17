# Latihan Soal Sisop 2021 - Modul 1

Mengambil dari tautan berikut: [MODUL 1](https://github.com/arsitektur-jaringan-komputer/Modul-Sisop/tree/master/2021/Modul1 "Goto MODUL 1").

## SOAL 1 ##

Buatlah sebuah program <b>bash script</b> yang dapat mengolah bilangan-bilangan yang diinputkan sebagai argumen! Bila jumlah argumen yang diinputkan ganjil, tampilkan jumlah bilangan-bilangan tersebut. Bila genap, tampilkan "Anda belum beruntung, coba lagi." Contoh:
```bash
$ bash script.sh 4 1 1
Output: 6

$ bash script.sh 3 3
Output: Anda belum beruntung, coba lagi.
```

## SOAL 2 ##

Membuat <i>task scheduling</i> menggunakan <b>crontab</b> untuk membuat <i>log</i> yang berisi <i>size</i> dari direktori `/home/<user>/Downloads` dalam <i>human readable format</i>. <i>Task</i> berjalan setiap 15 menit pada pukul 8 sampai 17. <i>File log</i> disimpan pada direktori `/home/<user>/log/` dengan format nama sesuai <i>command date</i>.

<img src="https://user-images.githubusercontent.com/37539546/126043654-6f7517e4-329d-4d60-b384-8cd9bc20ca08.png">

## SOAL 3 ##

Lakukan <i>download</i> dengan <i>command</i> `wget https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data` untuk mendapatkan <i>dataset</i>. Buatlah sebuah program <b>AWK</b> yang dapat menampilkan hasil perkalian dari kolom '<b>petal length in cm</b>' dan '<b>petal width in cm</b>' dengan format 2 angka di belakang koma hanya untuk <b>record</b> dengan kolom '<b><i>class</i></b>' yang mengandung <i>string</i> '<b>Iris-setosa</b>' dan memiliki nilai '<b>sepal length in cm</b>' lebih dari 5.4 berdasarkan <i>dataset</i> tersebut! Tampilkan hasil dengan format "<b>Luas petal pada baris n adalah y.yy</b>" dengan "<b>n</b>" adalah baris ke berapa <i>record</i> tersebut dan "<b>y.yy</b>" adalah hasil perkaliannya. Informasi atribut dapat dilihat di https://archive.ics.uci.edu/ml/datasets/iris/.
