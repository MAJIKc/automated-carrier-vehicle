//Servo
#include <Servo.h>
Servo lockingServo;

void lock(){
  lockingServo.write(80);
}

void unlock(){
  lockingServo.write(180);
}

//L298N
int ENA=11;
int ENB=6;
int IN1=10;
int IN2=9;
int IN3=8;
int IN4=7;
int pwmA;
int pwmB;
int dir;

void setMotor(int dir,int pwmA,int pwmB){
  analogWrite(ENA,pwmA);
  analogWrite(ENB,pwmB);
  if(dir == 1){ //KIRI MAJU, KANAN MAJU
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
  }
  else if(dir == -1){ //KIRI MUNDUR, KANAN MUNDUR
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
  }
  else if(dir == 2){ //KIRI MAJU, KANAN MUNDUR (BELOK KANAN)
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
  }
  else if(dir == 3){ //KIRI MUNDUR, KANAN MAJU (BELOK KIRI)
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
  }
  else{ //BERHENTI
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
  }  
}

//ULTRASONIC SENSOR
int triggerPin=1;
int echoPin=0;
long duration;
int distance;
int startBrake=36;
int brakeValA;
int brakeValB;

//BUZZER
int buzzerPin=2;

//BUTTONS
#define buttonRight 13
#define buttonLeft 12

//LCD
#include <LiquidCrystal_I2C.h>

int buttonRightState = 0;
int buttonLeftState = 0;
int buttonEnterState = 0;
int locationCount = 0;
int locationAmount = 3;             // ganti jumlah lokasi yang tersedia harus ganti locationAmount juga
int locationStartPoint = 0;
int locationBuffer1 = 0;
int locationBuffer2 = 0;
int progressLength = 0;

bool startLocomotion = false;

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

char *availableLocation[] = {       // ganti lokasi yang tersedia
  "Ruang Potong",
  "Loker",
  "Pintu Keluar"
};

byte arrowRight[8] = {
  0b00000,
  0b10000,
  0b11000,
  0b11100,
  0b11100,
  0b11000,
  0b10000,
  0b00000
};

byte arrowRightExtend[8] = {
  0b00000,
  0b00100,
  0b00110,
  0b00111,
  0b00111,
  0b00110,
  0b00100,
  0b00000
};

byte arrowLeft[8] = {
  0b00000,
  0b00001,
  0b00011,
  0b00111,
  0b00111,
  0b00011,
  0b00001,
  0b00000
};

byte arrowLeftExtend[8] = {
  0b00000,
  0b00100,
  0b01100,
  0b11100,
  0b11100,
  0b01100,
  0b00100,
  0b00000
};

void printArrowRight() {
  lcd.setCursor(15, 1);
  lcd.write((byte)0);     // arrow right
}

void printArrowLeft() {
  lcd.setCursor(0, 1);
  lcd.write((byte)2);     // arrow left
}

void printArrow() {
  printArrowRight();
  printArrowLeft();
}

void arrowRightPressed() {
  lcd.setCursor(15, 1);
  lcd.write((byte)1);     // arrow right extend
}

void arrowLeftPressed() {
  lcd.setCursor(0, 1);
  lcd.write((byte)3);     // arrow left extend
}

void printArrowEnter1() { // kebalikan biasa
  lcd.setCursor(15, 1);
  lcd.write((byte)3);
  lcd.setCursor(0, 1);
  lcd.write((byte)1);
}

void printArrowEnter2() { // kebalikan dan extend
  lcd.setCursor(15, 1);
  lcd.write((byte)2);
  lcd.setCursor(0, 1);
  lcd.write((byte)0);
}

void printArrowEnterCycle() {
  printArrowEnter1();
  delay(500);
  printArrowEnter2();
  delay(500);
  printArrowEnter1();
  delay(500);
  printArrowEnter2();
  delay(500);
  printArrowEnter1();
  delay(500);
}

void printYourLocation() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your Location:");
  printArrow();
}

void printDestination() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Destination:");
  printArrow();
}

void clearRow1() {
  lcd.setCursor(1, 1);
  lcd.print("              ");
}

void printAvailLocation() {
  if (locationCount > (locationAmount - 1)) {
    locationCount = 0;
  }
  if (locationCount < 0) {
    locationCount = locationAmount - 1;
  }
  locationStartPoint = ((14 - strlen(availableLocation[locationCount])) / 2) + 1;
  // contoh:
  // Toilet      -> 14 - 6  / 2 = 4
  // Lab Elektro -> 14 - 11 / 2 = 1.5, karena int jadi 1
  // +1 lagi karena alamat blok mulai dari 0 bukan mulai dari 1
  clearRow1();
  lcd.setCursor(locationStartPoint, 1);
  lcd.print(availableLocation[locationCount]);
}

void scrollRight() {
  arrowRightPressed();
  while(buttonRightState == HIGH) {
    buttonLeftState = digitalRead(buttonLeft);
    if(buttonLeftState == HIGH) {
      buttonEnterState = HIGH;
      break;
    }
    buttonRightState = digitalRead(buttonRight);
  }
  if(buttonEnterState != HIGH) {
    locationCount++; // ke array kanan
    printArrowRight();
    printAvailLocation();
  }
}

void scrollLeft() {
  arrowLeftPressed();
  while(buttonLeftState == HIGH) {
    buttonRightState = digitalRead(buttonRight);
    if(buttonRightState == HIGH) {
      buttonEnterState = HIGH;
      break;
    }
    buttonLeftState = digitalRead(buttonLeft);
  }
  if(buttonEnterState != HIGH) {
    locationCount--; // ke array kiri
    printArrowLeft();
    printAvailLocation();
  }
}

void errorBlinking() {
  lcd.setCursor(4, 1);
  lcd.print("Already");
  delay(500);
  clearRow1();
  delay(500);
  lcd.setCursor(6, 1);
  lcd.print("Here");
  delay(500);
  clearRow1();
  delay(500);
}

//LOAD CELL + HX711
#include <HX711_ADC.h>
#include <EEPROM.h>

const int HX711_dout = 4;
const int HX711_sck = 5;

HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_EEPROMAddress = 0;
unsigned long t = 0;

void ukurBerat(){  
  // Inisialisasi UI LCD untuk pengukuran berat
  lcd.clear();

  lcd.setCursor(2, 0);
  lcd.print("If Status is");
  lcd.setCursor(6, 1);
  lcd.print("Okay");
  delay(1650);
  
  lcd.setCursor(0, 0);
  lcd.print("Hold all button");
  lcd.setCursor(0, 1);
  lcd.print("to continue.....");
  delay(1650);
  
  lcd.setCursor(0, 0);
  lcd.print("Weight: ");
  lcd.setCursor(0, 1);
  lcd.print("Stat: ");
  
  while(true) {
    static boolean newDataReady = 0;
    const int serialPrintInterval = 0; //bisa dinaikin valuenya buat ngelambatin serial print
    float berat = 0;
  
    // Cek data baru dari konversi selanjutnya
    if (LoadCell.update()) newDataReady = true;
  
    if (newDataReady) {
      if (millis() > t + serialPrintInterval) {
        berat = LoadCell.getData();
        //Serial.print("Berat terukur pada Load Cell: ");
        //Serial.println(berat);
        newDataReady = 0;
        t = millis();
      }
    }
  
    // Menerima command dari terminal serial, ketik 't' untuk melakukan tare
    /*
    if (Serial.available() > 0) {
      char inByte = Serial.read();
      if (inByte == 't') LoadCell.tareNoDelay();
    }
  
    // Cek apakah tare bekerja
    if (LoadCell.getTareStatus() == true) {
      Serial.println("Tare complete");
    }
    */

    // Memunculkan pengukuran berat di LCD
    lcd.setCursor(8, 0);
    lcd.print("       ");
    lcd.setCursor(8, 0);
    lcd.print(berat);
    lcd.setCursor(15, 0);
    lcd.print("gr");

    // Memberi pesan Overloaded atau Okay
    if (berat > 1000) {
      lcd.setCursor(6, 1);
      lcd.print("          ");
      lcd.setCursor(6, 1);
      lcd.print("Overloaded");
    }
    else {
      lcd.setCursor(6, 1);
      lcd.print("          ");
      lcd.setCursor(6, 1);
      lcd.print("Okay");
      
      // Robot lanjut apabila semua button ditahan
      buttonRightState = digitalRead(buttonRight);
      buttonLeftState = digitalRead(buttonLeft);
      
      if(buttonRightState == HIGH) {
        while(buttonRightState == HIGH) {
          buttonLeftState = digitalRead(buttonLeft);
          if(buttonLeftState == HIGH) {
            buttonEnterState = HIGH;
            break;
          }
          buttonRightState = digitalRead(buttonRight);
        }
      }
      if(buttonLeftState == HIGH) {
        while(buttonLeftState == HIGH) {
          buttonRightState = digitalRead(buttonRight);
          if(buttonRightState == HIGH) {
            buttonEnterState = HIGH;
            break;
          }
          buttonLeftState = digitalRead(buttonLeft);
        }
      }
      if(buttonEnterState == HIGH) {
        buttonEnterState = LOW;
        // Lanjut ke fungsi selanjutnya
        break;
      }
    }
  }
}

//IR + PHOTODIODE
int analogPhotodiode1 = A0;
int analogPhotodiode2 = A1;
int analogPhotodiode3 = A2;
int analogPhotodiode4 = A3;
int valuePhotodiode;
bool detectPhotodiode1;
bool detectPhotodiode2;
bool detectPhotodiode3;
bool detectPhotodiode4;

int detectValue1 = 130; //(0 - 1023) Bacaan Photodiode yang menjadi penentu dia detect atau tidak, harus melakukan uji coba nilai
int detectValue2 = 85;
int detectValue3 = 165;
int detectValue4 = 215;
/*
int detectValue1 = 80; //(0 - 1023) Bacaan Photodiode yang menjadi penentu dia detect atau tidak, harus melakukan uji coba nilai
int detectValue2 = 55;
int detectValue3 = 80;
int detectValue4 = 120;
*/

//PID
int e = 0;
int pos = 0;
long prevT = 0;
float eprev = 0;
float eintegral = 0;

//MAPPING
int counterIntersection = 0;
int arrived = 0;
int yourLocation = 0;
int destination = 0;

void turnRight(){
  setMotor(2,255,255);
  delay(1650);
  setMotor(1,255,255);
  delay(500);
  counterIntersection++;
}

void turnLeft(){
  setMotor(3,255,255);
  delay(1650);
  setMotor(1,255,255);
  delay(500);
  counterIntersection++;
}

void turnForward(){
  setMotor(1,255,255);
  delay(1650);
  counterIntersection++;
}

void arrive(){
  setMotor(3,255,255);
  delay(3300);
  counterIntersection = 0;
  arrived = 1;
  unlock();
}

void mapping(){
  if(yourLocation == 0 && destination == 1){
    if(counterIntersection==1){
      turnRight();
    }
    else if(counterIntersection==2){
      arrive();
    }
  }
  if(yourLocation == 0 && destination == 2){
    if(counterIntersection==1){
      turnForward();
    }
    else if(counterIntersection==2){
      turnLeft();
    }
    else if(counterIntersection==3){
      turnRight();
    }
    else if(counterIntersection==4){
      arrive();
    }
  }
  if(yourLocation == 1 && destination == 0){
    if(counterIntersection==1){
      turnLeft();
    }
    else if(counterIntersection==2){
      arrive();
    }
  }
  if(yourLocation == 1 && destination == 2){
    if(counterIntersection==1){
      turnRight();
    }
    else if(counterIntersection==2){
      turnLeft();
    }
    else if(counterIntersection==3){
      turnRight();
    }
    else if(counterIntersection==4){
      arrive();
    }
  }
  if(yourLocation == 2 && destination == 0){
    if(counterIntersection==1){
      turnLeft();
    }
    else if(counterIntersection==2){
      turnRight();
    }
    else if(counterIntersection==3){
      turnForward();
    }
    else if(counterIntersection==4){
      arrive();
    }
  }
  if(yourLocation == 2 && destination == 1){
    if(counterIntersection==1){
      turnLeft();
    }
    else if(counterIntersection==2){
      turnRight();
    }
    else if(counterIntersection==3){
      turnLeft();
    }
    else if(counterIntersection==4){
      arrive();
    }
  }
}

void setup() {
  //Setup Servo
  lockingServo.attach(3);
  unlock();
  
  //Setup Serial
  //Serial.begin(57600);

  //Setup L298N
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  //Setup Ultrasonic Sensor
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  
  //Setup Buzzer
  pinMode(buzzerPin, OUTPUT);
  
  //Setup Buttons
  pinMode(buttonRight, INPUT);
  pinMode(buttonLeft, INPUT);
  
  //Setup LCD
  lcd.init();
  lcd.backlight();
  lcd.noCursor();
  lcd.createChar(0, arrowRight);
  lcd.createChar(1, arrowRightExtend);
  lcd.createChar(2, arrowLeft);
  lcd.createChar(3, arrowLeftExtend);

  //Setup Load Cell + HX711
  /*
  Serial.begin(57600); delay(10);
  Serial.println();
  Serial.println("Starting Setup Load Cell...");
  */
  
  LoadCell.begin();
  float calibrationValue;
  EEPROM.get(calVal_EEPROMAddress, calibrationValue);

  unsigned long stabilizingtime = 1800;
  boolean _tare = true;
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    //Serial.println("ERROR, cek koneksi dan pin antara Arduino dengan HX711");
    while (1);
  }
  else {
    LoadCell.setCalFactor(calibrationValue);
    //Serial.println("Setup Load Cell berhasil");
  }
}

void loop() {
  printYourLocation();
  printAvailLocation();
  unlock();
  
  while(true) {
    buttonRightState = digitalRead(buttonRight);
    buttonLeftState = digitalRead(buttonLeft);
    
    if(buttonRightState == HIGH) {
      scrollRight();
    }
    if(buttonLeftState == HIGH) {
      scrollLeft();
    }
    if(buttonEnterState == HIGH) {
      yourLocation = locationCount;    // menyimpan lokasi yang dipilih sebagai lokasi sekarang
      printArrowEnterCycle();
      printDestination();
      printAvailLocation();
      buttonEnterState = LOW;
      break;
    }
  }
  while(true) {
    buttonRightState = digitalRead(buttonRight);
    buttonLeftState = digitalRead(buttonLeft);
    //buttonEnterState = digitalRead(buttonEnter);
    
    if(buttonRightState == HIGH) {
      scrollRight();
    }
    if(buttonLeftState == HIGH) {
      scrollLeft();
    }
    if(buttonEnterState == HIGH) {
      destination = locationCount;     // menyimpan lokasi yang dipilih sebagai destinasi
      if(destination == yourLocation){ // blinking pesan error
        clearRow1();
        errorBlinking();
        printAvailLocation();
        buttonEnterState = LOW;
      }
      else {
        printArrowEnterCycle();
        buttonEnterState = LOW;
        break;
      }
    }
  }
  
  // mengecek beban dahulu
  ukurBerat();
  
  startLocomotion = true;
  progressLength = (strlen(availableLocation[yourLocation]) + 4 + strlen(availableLocation[destination])) - 16;
  // sisa karakter yang belum terlihat

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(availableLocation[yourLocation]);
  lcd.print(" to ");
  lcd.print(availableLocation[destination]);
  
  for(int i = 1; i <= progressLength; i++) {
    lcd.scrollDisplayLeft();
    delay(500);
  }

  lcd.setCursor(progressLength, 1);
  lcd.print("In Progress...");
  // di while(true) ini bisa masukin kode utama yang di void loop()
  // tambah break untuk keluar while(true) dan mereset kode

  //lock
  lock();
  
  while(true) { //LOOPING PROGRAM SEBENARNYA ADA DI SINI
    while(true){
      digitalWrite(triggerPin, LOW);
      delayMicroseconds(2);
      digitalWrite(triggerPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(triggerPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = duration*0.034/2;
      if(distance != 0){
        break;
      }
    }

    // Mengerem dari halangan < 35 cm
    if(startBrake == 36) {
      brakeValA = (pwmA/15);
      brakeValB = (pwmB/15);
    }
    if(distance < startBrake) {
      pwmA -= brakeValA;
      pwmB -= brakeValB;
      setMotor(dir,pwmA,pwmB);
      startBrake--;
      digitalWrite(buzzerPin, HIGH);
      delay(10);
      digitalWrite(buzzerPin, LOW);
    }
    if(distance > startBrake && startBrake < 36) {
      pwmA = pwmA + brakeValA;
      pwmB = pwmB + brakeValB;
      setMotor(dir,pwmA,pwmB);
      startBrake++;
      digitalWrite(buzzerPin, LOW);
    }
    if(startBrake <= 20) {
      setMotor(0,255,255);
      digitalWrite(buzzerPin, HIGH);
    }
    else{
      if(counterIntersection == 0){
        setMotor(1,255,255);
        delay(1650);
        counterIntersection++;
      }
      dir = 1;
      pwmA = 255;
      pwmB = 255;
    
      //BACA PHOTODIODE & HITUNG
      valuePhotodiode = analogRead(analogPhotodiode1);
      if (valuePhotodiode <= detectValue1) {
        detectPhotodiode1 = 1;
      }
      else {
        detectPhotodiode1 = 0;
      }
      valuePhotodiode = analogRead(analogPhotodiode2);
      if (valuePhotodiode <= detectValue2) {
        detectPhotodiode2 = 1;
      }
      else {
        detectPhotodiode2 = 0;
      }
      valuePhotodiode = analogRead(analogPhotodiode3);
      if (valuePhotodiode <= detectValue3) {
        detectPhotodiode3 = 1;
      }
      else {
        detectPhotodiode3 = 0;
      }
      valuePhotodiode = analogRead(analogPhotodiode4);
      if (valuePhotodiode <= detectValue4) {
        detectPhotodiode4 = 1;
      }
      else {
        detectPhotodiode4 = 0;
      }
      eintegral = 0;
      if (detectPhotodiode1 == 0 && detectPhotodiode2 == 0 && detectPhotodiode3 == 0 && detectPhotodiode4 == 1) { //0 0 0 1, ERROR = 3
        e = 120;
        //Serial.println("0 0 0 1");
      }
      if (detectPhotodiode1 == 0 && detectPhotodiode2 == 0 && detectPhotodiode3 == 1 && detectPhotodiode4 == 1) { //0 0 1 1, ERROR = 2
        e = 80;
        //Serial.println("0 0 1 1");
      }
      if (detectPhotodiode1 == 0 && detectPhotodiode2 == 0 && detectPhotodiode3 == 1 && detectPhotodiode4 == 0) { //0 0 1 0, ERROR = 1
        e = 40;
        //Serial.println("0 0 1 0");
      }
      if (detectPhotodiode1 == 0 && detectPhotodiode2 == 1 && detectPhotodiode3 == 1 && detectPhotodiode4 == 0) { //0 1 1 0, ERROR = 0
        e = 0;
        //Serial.println("0 1 1 0");
      }
      if (detectPhotodiode1 == 0 && detectPhotodiode2 == 1 && detectPhotodiode3 == 0 && detectPhotodiode4 == 0) { //0 1 0 0, ERROR = -1
        e = -40;
        //Serial.println("0 1 0 0");
      }
      if (detectPhotodiode1 == 1 && detectPhotodiode2 == 1 && detectPhotodiode3 == 0 && detectPhotodiode4 == 0) { //1 1 0 0, ERROR = -2
        e = -80;
        //Serial.println("1 1 0 0");
      }
      if (detectPhotodiode1 == 1 && detectPhotodiode2 == 0 && detectPhotodiode3 == 0 && detectPhotodiode4 == 0) { //1 0 0 0, ERROR = -3
        e = -120;
        //Serial.println("1 0 0 0");
      }
      if (detectPhotodiode1 == 1 && detectPhotodiode2 == 1 && detectPhotodiode3 == 1 && detectPhotodiode4 == 1) { //1 1 1 1, DETECTED INTERSECTION
        setMotor(0,pwmA,pwmB);
        digitalWrite(2, HIGH);
        delay(1000);
        mapping();
        //Serial.println("1 1 1 1");
        //doubleCheck();
      }
      digitalWrite(2, LOW);

      if(arrived == 1){
        arrived = 0;
        setMotor(1,0,0);
        break;
      }
      
      //HITUNG u(t) (Pengendalian PID)
    
      // menentukan konstanta PID (dapat di-adjust lagi sesuai respon nanti)
      float kp = 2;
      float ki = 0.25;
      float kd = 100;
    
      // menghitung delta t
      long currT = micros();
      // delta t dalam sekon
      float deltaT = ((float)(currT - prevT)) / 1.0e6;
      prevT = currT;
    
      // menghitung integral (I)
      eintegral = eintegral + (e * deltaT);
    
      // menghitung derivative (D)
      float dedt = (e - eprev) / (deltaT);
    
      // menghitung control signal u(t)
      float u = (kp * e) + (ki * eintegral) + (kd * dedt);
      //Serial.print(u);
      //Serial.print("   ");
    
      // menghitung kecepatan motor
      if (u < 0) {
        pwmA -= fabs (u);
      }
      else {
        pwmB -= u;
      }
      if (pwmA < 0) {
        pwmA = fabs (pwmA);
        if (pwmA > 255) {
          pwmA = 255;
        }
        dir = 3;
      } else {
        if (pwmA > 255) {
          pwmA = 255;
        }
        dir = 1;
      }
      if (pwmB < 0) {
        pwmB = fabs (pwmB);
        if (pwmB > 255) {
          pwmB = 255;
        }
        dir = 2;
      } else {
        if (pwmB > 255) {
          pwmB = 255;
        }
        dir = 1;
      }
    
      // memberikan sinyal pada motor
      setMotor(dir, pwmA, pwmB);
    
      // menyimpan error sebelumnya
      eprev = e;  
    }
  }
}
