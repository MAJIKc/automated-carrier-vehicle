# automated-carrier-vehicle

# Latar Belakang #
Tuntutan pekerjaan modern yang semakin kompleks mengharuskan orang-orang untuk lebih bijak menggunakan waktu dan energi untuk mengerjakan hal-hal yang memaksimalkan kecerdasan otak manusia. Pekerjaan yang bersifat repetitif, monoton, dan tidak membutuhkan bantuan manusia dapat digantikan dengan sebuah robot.

Di masa pandemi ini, diperlukan juga cara agar dapat meminimalisir kontak langsung dengan orang lain. Salah satu saat di mana manusia paling sering berkontak langsung satu sama lain adalah ketika ingin memberikan sesuatu barang kepada yang lain.

Dari masalah ini, kami terinspirasi untuk membuat robot yang dapat mengantarkan barang secara otomatis. Robot kami merupakan sebuah AGV (Automated Guided Vehicle) pembawa barang yang paling cocok untuk implementasi skala kecil.

# Konsep Desain Perangkat #
Robot AGV pembawa barang kami memliki 4 bagian penting, yaitu drive system, UI & warning system, power & charging system, serta safety system. Berikut adalah uraian untuk masing-masing bagian.

## Drive System ##
Motor dan gearbox digunakan untuk menggerakan robot, serta beberapa photodiode dan sistem kendali PID dengan konsep line following untuk menjaga robot tetap pada jalurnya.

## UI & Warning System ##
LCD digunakan untuk menunjukan menu pilihan lokasi robot sekarang dan tujuannya. Setelah memilih, LCD juga dipakai untuk menunjukan lokasi awal dan tujuan robot ketika robot sedang beroperasi. Terakhir adalah buzzer yang dapat memberi tahu pengguna apabila robot mendeteksi halangan pada jalurnya.

## Power & Charging System ##
Robot menggunakan baterai yang dapat diisi ulang dengan charger smartphone.

## Safety System ##
Robot dapat memelankan diri dan berhenti apabila sensor ultrasonik mendeteksi halangan di depan robot. Barang bawaan robot diamankan dengan sistem loker dan pengunci. Kombinasi load cell dan penguat sinyalnya untuk mengukur beban angkut robot dan memberi tahu pengguna apabila beban angkut robot sudah melebihi batas kemampuannya.

# Komponen yang Dipakai #
- Photodiode BPV10NF
- Sensor Ultrasonik HC-SR04
- Micro Servo SG90
- IR LED (TSAL6100)
- Active Buzzer
- Arduino UNO
- Motor Driver L298N
- DC Gearbox Motor 3V-6V
- Baterai Li-Ion CGR18650D
- Modul Charge TP4056
- DC-DC Step Down Module LM2596
- LCD 1602
- Load Cell TAL220
- HX711 Module

# Perancangan Sistem #
## Desain Sistem Keseluruhan ##
### Mock Up 3D Sistem ##
![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919600240544346152/unknown.png)

aaaaaaaaaaa\
aaaaaaaaaaaaaaa

First Header  | Second Header
------------- | -------------
Content Cell  | Content Cell
Content Cell  | Content Cell

- Bullet list
    - Nested bullet
          - Sub-nested bull
- Bullet list item 2 


# Heading 1 #
## Heading 1 ##
### Heading 1 ###

![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/912291119277158430/unknown.png "wah kasar")
