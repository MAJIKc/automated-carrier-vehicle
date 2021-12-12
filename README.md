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
- DPDT Switch

# Perancangan Sistem #
## Desain Sistem Keseluruhan ##
### Mock Up 3D Sistem ##
![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919600240544346152/unknown.png)

Roda kanan dan kiri kami tempatkan di bagian tengah samping kanan dan kiri container supaya robot memiliki sistem differential drive. Pada sistem ini, membelokan robot dapat dengan mudah dilakukan dengan membedakan kecepatan antara kedua motor. Dua roda caster tambahan digunakan supaya robot lebih stabil. Kotak komponen di belakang container digunakan untuk melindungi Arduino Uno, LCD, step down module, baterai, charging module, dan konektor-konektor dari komponen di luar kotak komponen. Bagian dalam container berisikan load cell dengan di atasnya ada penampang PVC Sheet dengan ketebalan 2 mm. Lalu, menggunakan 2 servo motor untuk bagian penguncian loker.

### Diagram Blok Sistem Keseluruhan ###
![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919600838161346611/unknown.png)

Robot kami terbentuk dari 6 sistem utama, yaitu sistem line following, deteksi halangan, pengukuran berat, penggerak, antarmuka, dan keamanan barang. Penjelasan lebih lanjut mengenai masing-masing sistem terdapat pada bagian selanjutnya.

### Flowchart Sistem ###
![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919600838371053598/unknown.png)
![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919600838568198264/unknown.png)

Secara Flowchart, ketika robot dinyalakan dengan switch power menuju mode ON, maka LCD akan menyala untuk menampilkan tujuan yang ada dan user tinggal memilih melalui button. Setelah itu, user meletakkan barang yang ingin diantarkan. Ketika barang bawaan melebihi 1 kg, pesan akan ditampilkan ke LCD dan menunggu sampai barang dikurangi beratnya. Jika kurang dari 1 kg, servo akan diaftifkan untuk mengunci loker dan robot akan berjalan. Selama perjalanan, robot akan mengikuti jalur yang sudah dibuat dan ketika robot bertemu halangan dengan jarak kurang dari 20 cm, buzzer akan diaktifkan selama 500 ms dan akan mengurangi kecepatan robot sebesar 20%. Ketika halangan sudah terdeteksi kurang dari 5 cm, robot akan membunyikan buzzer selama 10 s dan membuat robot berhenti total. Robot akan kembali berjalan sampai halangan yang ada sudah dihilangkan dari jalur robot. Jika selama perjalanan robot mendeteksi titik intersection, robot nantinya akan berbelok baik ke kiri atau kanan, ataupun lurus sesuai dengan mapping dari pilihan tujuan yang dipilih oleh user. Lalu, robot akan mengaktifkan servo untuk membuka kembali kunci loker ketika sudah sampai di titik tujuan dan akan menunggu konfirmasi pilihan tujuan dari user untuk kembali berjalan. Untuk mematikan robot, user cukup menekan kembali switch power menuju mode OFF.

### Desain Subsistem Line Following ###
![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919601571908714496/unknown.png)

Pada sistem ini, Arduino Uno membaca tangkapan intensitas cahaya inframerah oleh Photodiode yang akan berbeda ketika menghadap jalur atau ubin. Photodiode sendiri menangkap pantulan cahaya dari IR LED. Pembacaan ini kemudian diproses untuk digunakan oleh sistem penggerak.

### Desain Subsistem Deteksi Halangan ###
![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919601572105838592/unknown.png)

Pada sistem ini, sensor ultrasonik membaca jarak halangan di depan robot. Apabila jarak halangan sudah lebih kecil dari 20 cm, buzzer akan berbunyi selama 500 ms dan kecepatan robot akan dikurangi sebanyak 20%. Apabila jarak halangan sudah lebih kecil dari 5 cm, buzzer akan berbunyi selama 10 s dan robot diberhentikan.

### Desain Subsistem Pengukuran Berat ###
![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919601572349112390/unknown.png)

Pada sistem ini, load cell beserta ADC dan amplifier-nya akan mengukur beban barang bawaan robot. Apabila beban melebihi 1 kg, robot tidak diperbolehkan berjalan dan muncul peringatan pada sistem antarmuka. Apabila beban di bawah 1 kg, loker barang mengunci dan robot diperbolehkan untuk berjalan.

### Desain Subsistem Penggerak ###
![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919601572579803196/unknown.png)

Pada sistem ini, robot akan menerima perintah jalan dari sistem pengukuran berat, menerima informasi jalur dari sistem line following, dan menerima interupsi dari sistem deteksi halangan. Bacaan Photodiode dari sistem line following akan diproses oleh sistem kendali PID untuk mengendali kecepatan motor kanan dan kiri melalui motor driver agar robot tetap di tengah jalur. Fungsi Mapping digunakan untuk membelokan robot ke kiri atau ke kanan ketika berada di intersection tergantung pada lokasi awal dan tujuan robot.

### Desain Subsistem Antarmuka ###
![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919601572856602674/unknown.png)

Pada sistem ini, robot akan meminta pengguna untuk memilih lokasi awal dan tujuan. Pilihan lokasi dapat dilihat di LCD. Button kiri dan kanan digunakan untuk scrolling lokasi. Menekan kedua button akan mengkonfirmasi pilihan pengguna. Pilihan pengguna nantinya digunakan fungsi Mapping untuk menentukan arah robot setiap intersection.

### Desain Subsistem Keamanan Barang ###
![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919601573062119424/unknown.png)

Pada sistem ini, robot akan menunggu perintah untuk mengunci loker dari sistem pengukuran berat. Apabila terdapat perintah untuk mengunci loker, servo depan dan belakang akan menggerakan lengannya supaya terkait pada dudukan lengan sehingga mengunci loker.

# Komponen Sistem #
## Breadboard Diagram ##
![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919603179023376394/unknown.png)

## Wiring Diagram ##
![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919603212598779934/unknown.png)

### IR LED ###
Selama robot mendapatkan sumber tegangan atau dinyalakan, IR LED akan menembakkan infrared ke jalur yang digunakan robot.

### Photodiode BPV10NF ###
Menangkap atau mendeteksi hasil intensitas pantulan cahaya infrared yang dihasilkan dari IR LED. Hasil intensitas cahaya yang diinginkan tidak bernilai besar untuk mendeteksi jalur yang dirancang dengan warna yang lebih gelap dari sekelilingnya dengan fungsi analogRead (0 – 1023) sehingga robot nantinya dapat mengetahui jalur yang harus dilewati ketika melakukan perjalanannya.

### Sensor Ultrasonik HC-SR04 ###
Pertama kali sensor tidak akan menembakkan gelombang ultrasonik selama 2 mikrosekon dengan membuat pin trigger LOW lalu menambahkan delay 2 mikrosekon, dan setelah itu baru akan menembakkan selama 10 mikrosekon dengan membuat pin trigger HIGH dan ditambah delay 10 mirkosekon lalu akan berhenti kembali dengan membuat pin trigger LOW. Pengoperasian sensor seperti ini akan dipakai dalam pendeteksian jarak halangan dengan sensor selama dalam perjalanan menuju lokasi tujuan melalui pengukuran waktu yang diperlukan gelombang ultrasonik dari pemancar untuk memantul dan mengenai receiver dengan membaca input pada pin echo dari sensor melalui fungsi pulseIn(echoPin, HIGH).

### Micro Servo SG90 ###
Micro servo digunakan dalam sistem sebagai mekanisme penguncian loker robot dengan kondisi awalnya berada di posisi 90 derajat melalui Arduino yang akan memberikan sinyal PWM dengan fungsi write(90). Posisi lengan servo akan diubah ke posisi mengunci oleh motor saat robot dalam perjalanan dengan  fungsi write(180), lalu lengan servo akan digerakan ke posisi terbuka setelah sampai pada tujuan dengan fungsi write(90).

### Active Buzzer ###
Digunakan dalam robot kami sebagai penanda untuk orang sekitar bila ada halangan di depan robot yang membuat robot tidak dapat melanjutkan perjalanannya ketika robot sedang bergerak mengikuti jalur ke lokasi tujuannya. Buzzer akan aktif dengan dibantu dari sensor ultrasonik, dimana ketika jarak antara objek dengan sensor dibawah 20 cm, pin buzzer akan HIGH selama 500 ms dengan bantuan delay lalu akan mati kembali. Proses pengecekan jarak akan diulang terus menerus sampai akhirnya mencapai jarak 5 cm, pin buzzer akan HIGH selama 10 s dengan bantuan delay.

### Arduino UNO ###
Penggunaan mikrokontroler dalam robot adalah untuk mengontrol proses input dan memberikan output berdasarkan logika program robot yang sudah dirancang atau dibuat dari berbagai komponen yang diimplementasikan di dalamnya untuk bisa menyelesaikan misinya dengan baik dan benar.

### Motor Driver L298N ###
Mengatur segala parameter pada DC motor dari arah dan kecepatan. Melalui kinerja dari driver L298N, arah arus yang mengalir pada motor dapat dibalik sesuai dengan sinyal digital sehingga motor dapat berganti arah dengan perintah dari Arduino. Driver juga dapat meneruskan sinyal PWM dari Arduino ke DC motor.

### DC Gearbox Motor 3V-6V ###
Membantu memutarkan roda yang terpasang pada robot agar dapat bergerak sesuai dengan input yang diterima dari driver L298N. Kecepatan 2 DC Motor yang digunakan robot akan diatur melalui analogWrite dengan nilai 0 – 255 melalui pin PWM (pin ENA dan pin ENB) dan arah perputaran melalui pin IN1 dan IN2 atau IN3 dan IN4 melalui HIGH dan LOW. Kombinasi HIGH – LOW akan membuat putaran clockwise, LOW – HIGH membuat putaran counter-clockwise, dan LOW – LOW roda tidak akan berputar.

### Baterai Li-ion CGR18650D ###
Mensuplai daya untuk rangkaian kelistrikan robot yang akan memberikan daya secara langsung ke Arduino dan daya setelah melewati Step Down ke sisa komponen yang membantu kinerja robot dalam melakukan misinya.

### Modul Charge TP4056 ###
Akan melakukan pengisian ulang baterai Li-ion yang terpasang bila disambungkan dengan koneksi micro-USB.

### DC-DC Step Down Module LM2596 ###
Menurunkan tegangan dari 2 baterai Li-ion yang terpasang pada robot secara seri, yaitu dari 7,4V menjadi 5V untuk bisa digunakan oleh komponen robot lainnya seperti photodiode, sensor ultrasonik, micro servo, dan lain-lain dalam melakukan kinerjanya.

### LCD 1602 ###
Sesaat LCD sudah mendapatkan daya dari baterai, LCD akan berproses dan akan menampilkan pilihan lokasi robot serta tujuan pengantaran kepada user. LCD akan menunjukan cursor penunjukan yang sudah terpogram terlebih dahulu dengan bantuan button yang akan ditekan oleh user. Contohnya bila user menekan tombol panah kanan, cursor pilihan pada LCD akan bergeser ke kanan.

### DPTD Switch ###
Kinerjanya bisa membuat rangkaian baterai dari seri ke paralel dan sebaliknya sesuai dengan apakah baterai ingin dipakai untuk memberikan daya ke rangkaian atau ingin dicharge menggunakan charging module.

### Load Cell ###
Load cell jenis batang dengan kapasitas 5 kg digunakan untuk mengukur beban angkut robot supaya pengguna tahu apabila beban angkut robot sudah melebihi batas kemampuannya. Ketika beban diterapkan, hambatan listrik akan berubah sebagai respons terhadap tekanan yang diterapkan ini. Dengan mengambil informasi ini dan beberapa kalibrasi, kita dapat menentukan massa beban yang tepat.

### HX711 Module ###
Perubahan resistansi listrik yang disediakan oleh Load Cell perlu diperkuat sehingga dapat dibaca oleh Arduino. Dari sini, modul HX711 akan membaca informasi dari Load Cell lalu akan memperkuat sinyal dan kemudian mengirimkannya ke Arduino untuk diproses. Menghubungkannya HX711 ke Arduino bisa dengan 2 pin (Clock dan Data), VCC, dan Ground. Cara Arduino untuk berkomunikasi dengan HX711 tersedia dengan fitur kalibrasi dan Tare (reset) untuk dengan mudah menentukan berat suatu objek.

# Implementasi dan Analisis #
## Gambar Hasil Implementasi ##
### Tampak Depan Robot (Sensor Ultrasonik dan Penguncian Sistem Engsel) ###
![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919607251826794536/unknown.png)

### Tampak Belakang Robot (Komponen Box dan Servo Motor) ###
![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919607489257943082/unknown.png)

### Tampak Samping Kiri Robot (Penglihatan Tata Letak Roda) ###
![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919607489534754927/unknown.png)

### Tampak Samping Kanan Robot (Penglihatan Tata Letak Roda) ###
![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919607489765449728/unknown.png)

### Tampak Bawah Robot (IR LED dan Photodiode) ###
![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919607489975189554/unknown.png)

## Penggantian Dua Servo menjadi Satu ##
Dibandingkan dengan design awal yang berupa dua buah servo mengait ke kail pada tutup, design akhir yang dipilih adalah tangan servo dilekatkan pada pengunci yang sudah tersedia dari container. Jadi ketika servo bergerak, pengunci container yang sudah ada akan berotasi mengunci container robot. Selain itu, tidak digunakan juga dua buah servo tapi hanya satu untuk ke salah satu pengait container. Sisi tutup container yang satunya dilepas penguncinya dan dibuat menjadi engsel agar tutup container dapat bekerja sebagai tutup loker.

![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919607490226827324/unknown.png)

## Malfungsi pada Load Cell ##
Hasil penimbangan barang dan pencegahan overload pada robot tidak bekerja karena terdapat masalah pada HX711. Saat dilakukan debug, ditemukan bahwa load cell masih bekerja seperti seharusnya dan mengeluarkan voltage yang berubah sesuai berat yang diberikan. Masalah terdapat pada output dari  HX711 yang tidak terbaca oleh Arduino. Kemungkinan masalah ada pada rangkaian yang salah sehingga menyebabkan sistem load cell tidak bekerja atau HX711-nya sendiri yang malfungsi.

![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919607490558181436/unknown.png)

## Kondisi PVC Sheet Penahan Beban ##
Terdapat PVC Sheet yang terdapat di dalam container robot yang bekerja sebagai penghitung berat dan dasar dari loker yang menahan barang di atasnya. PVC sheet ini dipotong sendiri menggunakan tangan setelah melakukan pengukuran dinding dalam container. Namun karena dinding dalam container tidak tegak lurus, serta sulit untuk secara tepat menghitung keliling dinding dalam container, PVC yang dipotong akhirnya sedikit lebih kecil dan longgar. Terdapat sela kecil antara PVC dan dinding yang menyebabkan PVC Sheet sedikit goyang, namun karena lubang kecil barang yang berada dalam loker masih tidak akan jatuh.

![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919607490851766363/unknown.png)

## Penyebab Caster Wheel Tidak Stabil ##
Pemakaian dua Caster Wheel yang terpasang pada robot membuat pergerakan robot menjadi tidak stabil, dikarenakan pada saat robot ingin melakukan perjalanan maju, Caster Wheel yang merupakan roda tipe freewheel pada awalannya akan mengkondisikan posisinya untuk mengikuti kondisi pergerakan robot, hal tersebut yang akan membuat robot akan keluar dari jalur. Untuk itu, Caster Wheel diposisikan lurus dan direkatkan dengan lem tembak. Hal tersebut sudah membuat Caster Wheel tidak perlu memposisikan dirinya untuk menjadi lurus dan membuat robot berjalan lebih stabil.

![picture alt](https://cdn.discordapp.com/attachments/611548819322044437/919607491086655549/unknown.png)

## Motor Roda Kurang Kuat Menarik Benda di Atas 1 kg ##
Dua DC Motor yang dipakai sebagai lokomosi robot tidak memiliki torsi yang cukup kuat ketika robot sudah membawa barang yang memiliki berat di atas 1 kg. Hal tersebut dikarenakan tegangan yang di dapat oleh masing - masing motor hanya berkisar 3 V. Terminal input 12 V motor driver tidak dapat digunakan untuk memberi tegangan pada motor sehingga tidak ada pilihan lain selain memberi tegangan pada motor melalui terminal input 5 V sehingga dengan voltage drop motor driver sekitar 2 V, motor hanya mendapatkan tegangan berkisar 3 V. Hal ini mungkin dikarenakan oleh koneksi antara terminal dengan baterai yang kurang baik atau terminalnya itu sendiri yang mengalami kerusakan.

## Ban Roda Slip ##
Pada saat robot sedang berjalan dari suatu titik ke titik yang lain, terkadang terjadi slip dikarenakan kondisi ubin tempat robot berjalan. Lantai yang berdebu atau miring menyebabkan salah satu roda melayang sehingga tidak belok dengan sesuai. Ini menyebabkan ketika robot berbelok bisa terjadi oversteer atau understeer. Untuk mengantisipasi hal tersebut, ban dilekatkan dengan double tape dan ditaburi bubuk debu agar tidak terlalu lengket. Dengan adanya bantuan tersebut, roda robot sudah tidak terlalu slip dan bisa melakukan pergerakan sampai tujuan. Bila masih terjadi slip, diberi bantuan berupa geseran dari operator.

## Baterai Cepat Habis (2 Jam) ##
Karena sistem terdiri dari banyak komponen, daya baterai yang termakan cukup tinggi, diestimasikan robot bisa bertahan dan melakukan fungsi dengan baik selama 2 jam, lebih dari itu robot tidak akan menghasilkan kinerja yang lebih baik ketimbang dari kondisi fully charged ke 2 jam tersebut. Setelah 2.5 jam robot akan berhenti bekerja karena baterai sudah benar-benar mau habis dan tidak sanggup lagi memberikan daya untuk komponen.

## Komponen Box Sulit dibongkar bila ingin Melakukan Debug ##
Banyaknya komponen yang dimasukkan ke dalam komponen box menyebabkan banyaknya kabel yang tersebar dan menimpa satu sama lain. Hal tersebut mengakibatkan ketika terjadi suatu malfungsi di salah satu komponen yang ada di dalam komponen box, selain harus membuka baut yang terpasang, diperlukan juga pencarian kabel komponen yang mengalami malfungsi. Ini membuat waktu debug menjadi lebih lama dan juga adanya resiko merusak sistem yang lain.

## Komponen lainnya pada Robot ACV ##
Untuk sistem dan komponen selain yang disebutkan di atas, sudah bekerja dengan baik sesuai perancangan sistem. Sistem seperti braking, mapping. line following, warning, pemilihan lokasi, dan pemlihan tujuan dapat bekerja sesuai rancangan awal dan tidak mengalami perubahan.

# Kesimpulan #
- Subsistem Line Following dapat bekerja dengan baik sesuai design awal.
- Subsistem Deteksi Halangan dapat bekerja dengan baik sesuai design awal.
- Subsistem Pengukuran Berat tidak dapat bekerja dengan baik karena kerusakan komponen atau rangkaian.
- Subsistem Penggerak tidak bekerja secara maksimal dan terdapat perubahan dari design awal.
- Subsistem Antarmuka dapat bekerja dengan baik sesuai design awal.
- Subsistem Keamanan Barang dapat bekerja dengan baik, tapi berubah dari design yang awal.
- Secara keseluruhan, robot Automated Carrier Vehicle (ACV) berhasil membawa barang dari satu tempat ke tempat yang lain berdasarkan input dari pengguna sesuai dengan map pada programa.
