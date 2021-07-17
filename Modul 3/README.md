# Latihan Soal Sisop 2021 - Modul 3

Mengambil dari tautan berikut: [MODUL 3](https://github.com/arsitektur-jaringan-komputer/Modul-Sisop/tree/master/2021/Modul3 "Goto MODUL 3").

## SOAL 1 ##

Buatlah program C yang bisa menghitung faktorial secara paralel, lalu menampilkan hasilnya secara berurutan.
```bash
$ ./faktorial 5 3 4
Output:
3! = 6  
4! = 24  
5! = 120
```

## SOAL 2 ##

Buatlah sebuah program untuk menampilkan <i>file</i> pada urutan ketiga dari sebuah direktori dengan menggunakan <b>pipe</b> dan <i>command</i> <b>ls</b>, <b>head</b>, <b>tail</b>.

## SOAL 3 ##

Buatlah sebuah program menggunakan <b>socket</b> yang terdiri dari <b><i>client</i></b> dan <b><i>server</i></b>. Saat <i>client</i> mengetikkan "<b>tambah</b>", maka suatu angka yang ada pada <i>server</i> bertambah 1 dan <i>server</i> otomatis mengirimkan pesan ke <i>client</i> yang berisi "<b>Penambahan berhasil</b>" dan ketika mengetikkan perintah "<b>kurang</b>", maka suatu angka yang ada pada <i>server</i> berkurang 1 dan <i>server</i> otomatis mengirimkan pesan ke <i>client</i> yang berisi "<b>Pengurangan berhasil</b>". Perintah lainnya pada <i>client</i> adalah "<b>cek</b>", lalu <i>server</i> akan mengirimkan pesan yang berisi jumlah terkini angka tersebut. Selain perintah tersebut, <i>server</i> akan mengirimkan pesan "<b>command tidak sesuai</b>". Program ini dapat berjalan tanpa henti. Nilai awal angka pada <i>server</i> adalah 5.
