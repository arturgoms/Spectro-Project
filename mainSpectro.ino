// LCD Config
#include <SPI.h>
#include <TFT_ILI9163C.h>
#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif
uint8_t errorCode = 0;
#if defined(ESP8266)
#define __CS1   16
#define __DC    5
#else
#define __CS1   10
#define __DC  9
#endif
TFT_ILI9163C tft = TFT_ILI9163C(__CS1, __DC);
// End

// RTC Config
#include <Wire.h>
#include "ds3231.h"
#include "rtc_ds3231.h"
#define BUFF_MAX 128
uint8_t time[8];
char recv[BUFF_MAX];
unsigned int recv_size = 0;
unsigned long prev, interval = 1000;
//End

// BMP180
#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;
//End

// Another Things
int lol = 0;
int lBtn = 4;
int eBtn = 3;
int rBtn = 2;
int statelBtn;
int lastStatelBtn;
int stateeBtn;
int lastStateeBtn;
int staterBtn;
int lastStaterBtn;
int stadoDisplay;
int indexNotifc = 0;
char notifc[BUFF_MAX];
int stadoNotifc;
int i = 0;
uint8_t reg_gval;
// End

//MPU-6050
const int MPU=0x69;
int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void setup() {

  //Main Config
  pinMode(rBtn, INPUT);
  pinMode(eBtn, INPUT);
  pinMode(lBtn, INPUT);
  lastStatelBtn=HIGH;
  lastStateeBtn=HIGH;
  lastStaterBtn=HIGH;
  Serial.begin(9600);
  attachInterrupt(eBtn, rtc, FALLING);
  attachInterrupt(rBtn, home2, FALLING);
  attachInterrupt(lBtn, home3, FALLING);
  Serial.println("Initializing. . .");
  //End
  delay(1000);
  //LCD
  Serial.println("Checking LCD!");
  tft.begin();
  Serial.println("PASS!");

  tft.drawRect(0, 0, 128, 128, WHITE);
  tft.setRotation(2);
  tft.setForeground(WHITE);
  tft.setBackground(WHITE);
  tft.setTextScale(2);
  tft.setCursor(CENTER, CENTER);
  tft.print("Initializing. . . ");
  //End
  delay(1000);
  //RTC
  Serial.println("Checking RTC!");
  Wire.begin();
  Serial.println("PASS!");
  DS3231_init(DS3231_INTCN);
  memset(recv, 0, BUFF_MAX);
  Serial.println("GET time");
  //End
  delay(1000);
  //BMP180
  Serial.println("Checking BMP180!");
  bmp.begin();
  Serial.println("PASS!");
  //End
  delay(1000);
  //MPU6050
  Serial.println("Checking MPU6050!");
  Wire.beginTransmission(MPU);
  Serial.println("PASS!");
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  //End
  delay(1000);
  Serial.println("OK, Starting!");

  tft.fillRect(4, 25, 120, 60, BLACK);
  tft.fillRect(3, 105, 122, 20, BLACK);
  stadoDisplay = 0;

}
void loop(void) {

  rtc();
  home2();
  home3();




  staterBtn = digitalRead(rBtn);
  stateeBtn = digitalRead(eBtn);
  statelBtn = digitalRead(lBtn);

  if(staterBtn==1 && lastStaterBtn==0)
  {
      if ( lol != 1){

       lol = 1;
     }
     stadoDisplay++;
     Serial.println("Botao direito pressionado");
  }
  if(stateeBtn==1 && lastStateeBtn==0)
  {
      if ( lol != 1){

       lol = 1;
     }

     Serial.println("Botao enter pressionado");
  }
  if(statelBtn==1 && lastStatelBtn==0)
  {
      if ( lol != 1){

       lol = 1;
     }
     stadoDisplay--;
     Serial.println("Botao esquerdo pressionado");
  }

lastStaterBtn=staterBtn;
lastStateeBtn=stateeBtn;
lastStatelBtn=statelBtn;

}
void eraseNotifc(){
  tft.fillRect(1, 105, 126, 20, BLACK);
}


void rtc(void) {


      char in;
      char buff[BUFF_MAX];
      unsigned long now = millis();
      struct ts t;

      // show time once in a while
      if ((now - prev > interval) && (Serial.available() <= 0)) {
          DS3231_get(&t);

          // there is a compile time option in the library to include unixtime support
  #ifdef CONFIG_UNIXTIME
          snprintf(buff, BUFF_MAX, "%d.%02d.%02d %02d:%02d:%02d %ld", t.year,
               t.mon, t.mday, t.hour, t.min, t.sec, t.unixtime);
  #else
          snprintf(buff, BUFF_MAX, "%d.%02d.%02d %02d:%02d:%02d", t.year,
               t.mon, t.mday, t.hour, t.min, t.sec);
  #endif



    i++;
    if (i==5){
      eraseNotifc();
      i = 0;
    }
      // SHOW HOME SCREEN


              tft.drawCircle(57, 10, 2, 0xFFFF);
              tft.fillCircle(64, 10, 2, 0xFFFF);
              tft.drawCircle(71, 10, 2, 0xFFFF);

              Serial.println(buff);
              prev = now;
          if (stadoDisplay == 0){
              tft.fillRect(24, 39, 80, 45, BLACK);

              tft.setCursor(41, 25);
              tft.setTextScale(1);
              tft.setTextColor(WHITE);
              tft.print(t.mon);
              tft.setCursor(CENTER, 20);
              tft.setTextScale(2);
              tft.setTextColor(WHITE);
              tft.print(t.mday);
              tft.setCursor(78, 25);
              tft.setTextScale(1);
              tft.setTextColor(WHITE);
              tft.print(t.year);

              if (t.hour<10) {
                tft.setCursor(26, 40);
                tft.setTextScale(3);
                tft.setTextColor(WHITE);
                tft.print("0");
                tft.setCursor(44, 40);
                tft.setTextScale(3);
                tft.setTextColor(WHITE);
                tft.print(t.hour);
              }else{
              tft.setCursor(26, 40);
              tft.setTextScale(3);
              tft.setTextColor(WHITE);
              tft.print(t.hour);
              }
              tft.setCursor(63, 40);
              tft.print(":");
              if (t.min <10) {
                tft.setCursor(70, 40);
                tft.setTextScale(3);
                tft.setTextColor(WHITE);
                tft.print("0");
                tft.setCursor(88, 40);
                tft.setTextScale(3);
                tft.setTextColor(WHITE);
                tft.print(t.min);
              }else{
              tft.setCursor(70, 40);
              tft.setTextScale(3);
              tft.setTextColor(WHITE);
              tft.print(t.min);
              }
              tft.setCursor(CENTER, 70);
              tft.setTextScale(2);
              tft.setTextColor(WHITE);
              tft.print(t.sec);

              }else{



            }

        }

      if (Serial.available() > 0) {
          in = Serial.read();

          if ((in == 10 || in == 13) && (recv_size > 0)) {
              parse_cmd(recv, recv_size);
              recv_size = 0;
              recv[0] = 0;
          } else if (in < 48 || in > 122) {;       // ignore ~[0-9A-Za-z]
          } else if (recv_size > BUFF_MAX - 2) {   // drop lines that are too long
              // drop
              recv_size = 0;
              recv[0] = 0;
          } else if (recv_size < BUFF_MAX - 2) {
              recv[recv_size] = in;
              recv[recv_size + 1] = 0;
              recv_size += 1;
          }

      }
}
void parse_cmd(char *cmd, int cmdsize)
{
    uint8_t i;
    uint8_t reg_val;
    char buff[BUFF_MAX];
    struct ts t;

    //snprintf(buff, BUFF_MAX, "cmd was '%s' %d\n", cmd, cmdsize);
    //Serial.print(buff);

    // TssmmhhWDDMMYYYY aka set time
    if (cmd[0] == 84 && cmdsize == 16) {
        //T355720619112011
        t.sec = inp2toi(cmd, 1);
        t.min = inp2toi(cmd, 3);
        t.hour = inp2toi(cmd, 5);
        t.wday = cmd[7] - 48;
        t.mday = inp2toi(cmd, 8);
        t.mon = inp2toi(cmd, 10);
        t.year = inp2toi(cmd, 12) * 100 + inp2toi(cmd, 14);
        DS3231_set(t);
        Serial.println("OK");
        stadoNotifc = 0;
        indexNotifc = 1;
        notification();

    } else if (cmd[0] == 49 && cmdsize == 1) {  // "1" get alarm 1
        DS3231_get_a1(&buff[0], 59);
        DS3231_get_a1(&notifc[0], 59);
        Serial.println(buff);
        stadoNotifc = 0;
        indexNotifc = 2;
        notification();

    } else if (cmd[0] == 50 && cmdsize == 1) {  // "2" get alarm 1
        DS3231_get_a2(&buff[0], 59);
        DS3231_get_a2(&notifc[0], 59);
        Serial.println(buff);
        stadoNotifc = 0;
        indexNotifc = 3;
        notification();

    } else if (cmd[0] == 51 && cmdsize == 1) {  // "3" get aging register
        Serial.print("aging reg is ");
        Serial.println(DS3231_get_aging(), DEC);
        stadoNotifc = 0;
        indexNotifc = 4;
        notification();

    } else if (cmd[0] == 65 && cmdsize == 9) {  // "A" set alarm 1
        DS3231_set_creg(DS3231_INTCN | DS3231_A1IE);
        //ASSMMHHDD
        for (i = 0; i < 4; i++) {
            time[i] = (cmd[2 * i + 1] - 48) * 10 + cmd[2 * i + 2] - 48; // ss, mm, hh, dd
        }
        uint8_t flags[5] = { 0, 0, 0, 0, 0 };
        DS3231_set_a1(time[0], time[1], time[2], time[3], flags);
        DS3231_get_a1(&buff[0], 59);
        DS3231_get_a1(&notifc[0], 59);
        Serial.println(buff);
        stadoNotifc = 0;
        indexNotifc = 5;
        notification();
    } else if (cmd[0] == 66 && cmdsize == 7) {  // "B" Set Alarm 2
        DS3231_set_creg(DS3231_INTCN | DS3231_A2IE);
        //BMMHHDD
        for (i = 0; i < 4; i++) {
            time[i] = (cmd[2 * i + 1] - 48) * 10 + cmd[2 * i + 2] - 48; // mm, hh, dd
        }
        uint8_t flags[5] = { 0, 0, 0, 0 };
        DS3231_set_a2(time[0], time[1], time[2], flags);
        DS3231_get_a2(&buff[0], 59);
        Serial.println(buff);
        DS3231_get_a2(&notifc[0], 59);
        stadoNotifc = 0;
        indexNotifc = 6;
        notification();
    } else if (cmd[0] == 67 && cmdsize == 1) {  // "C" - get temperature register
        Serial.print("temperature reg is ");
        Serial.println(DS3231_get_treg(), DEC);
        stadoNotifc = 0;
        indexNotifc = 7;
        notification();
    } else if (cmd[0] == 68 && cmdsize == 1) {  // "D" - reset status register alarm flags
        reg_val = DS3231_get_sreg();
        reg_val &= B11111100;
        DS3231_set_sreg(reg_val);
        stadoNotifc = 0;
        indexNotifc = 8;
        notification();
    } else if (cmd[0] == 70 && cmdsize == 1) {  // "F" - custom fct
        reg_val = DS3231_get_addr(0x5);
        reg_gval = reg_val;
        Serial.print("orig ");
        Serial.print(reg_val,DEC);
        Serial.print("month is ");
        Serial.println(bcdtodec(reg_val & 0x1F),DEC);
        stadoNotifc = 0;
        indexNotifc = 9;
        notification();
    } else if (cmd[0] == 71 && cmdsize == 1) {  // "G" - set aging status register
        DS3231_set_aging(0);
    } else if (cmd[0] == 83 && cmdsize == 1) {  // "S" - get status register
        Serial.print("status reg is ");
        Serial.println(DS3231_get_sreg(), DEC);
        stadoNotifc = 0;
        indexNotifc = 10;
        notification();
    } else {
        Serial.print("unknown command prefix ");
        Serial.println(cmd[0]);
        Serial.println(cmd[0], DEC);
        stadoNotifc = 0;
        indexNotifc = 11;
        notification();
    }
}

void home2(){
        Serial.print("Temperature = ");
        Serial.print(bmp.readTemperature());
        Serial.println(" *C");
        Serial.print("Pressure = ");
        Serial.print(bmp.readPressure());
        Serial.println(" Pa");
        Serial.print("Altitude = ");
        Serial.print(bmp.readAltitude());
        Serial.println(" meters");
        Serial.print("Pressure at sealevel (calculated) = ");
        Serial.print(bmp.readSealevelPressure());
        Serial.println(" Pa");
        Serial.print("Real altitude = ");
        Serial.print(bmp.readAltitude(101500));
        Serial.println(" meters");
        Serial.println();
if (stadoDisplay == 1){
              tft.fillRect(24, 25, 80, 60, BLACK);
              tft.setCursor(25, 40);
              tft.setTextScale(3);
              tft.setTextColor(WHITE);
              tft.print(bmp.readTemperature());
              delay(1000);
}else{

}

}
void home3 (){

    Wire.beginTransmission(MPU);
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    //Solicita os dados do sensor
    Wire.requestFrom(MPU,14,true);
    //Armazena o valor dos sensores nas variaveis correspondentes
    AcX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    AcY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AcZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    Tmp=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    GyX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    GyY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    GyZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
    //Envia valor X do acelerometro para a serial e o LCD
    Serial.print("AcX = "); Serial.print(AcX);
    //Envia valor Y do acelerometro para a serial e o LCD
    Serial.print(" | AcY = "); Serial.print(AcY);
    //Envia valor Z do acelerometro para a serial e o LCD
    Serial.print(" | AcZ = "); Serial.print(AcZ);
    //Envia valor da temperatura para a serial e o LCD
    //Calcula a temperatura em graus Celsius
    Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);
    //Envia valor X do giroscopio para a serial e o LCD
    Serial.print(" | GyX = "); Serial.print(GyX);
    //Envia valor Y do giroscopio para a serial e o LCD
    Serial.print(" | GyY = "); Serial.print(GyY);
    //Envia valor Z do giroscopio para a serial e o LCD
    Serial.print(" | GyZ = "); Serial.println(GyZ);
    if (stadoDisplay == -1){
              tft.fillRect(24, 25, 80, 60, BLACK);
              tft.setCursor(25, 40);
              tft.setTextScale(3);
              tft.setTextColor(WHITE);
              tft.print(AcX);
              delay(1000);
    }else{

    }

}

void notification(){

  if (indexNotifc == 1){ //Mostra "Time Set"
        if (stadoNotifc == 0){
        tft.setCursor(CENTER, 108);
        tft.setTextScale(2);
        tft.setTextColor(WHITE);
        tft.print("Time Set");
        stadoNotifc = 1;
        }else{
        }
  }else if (indexNotifc == 2){ //Mostra o Alarm 1
        if (stadoNotifc == 0){
        tft.setCursor(CENTER, 108);
        tft.setTextScale(1);
        tft.setTextColor(WHITE);
        tft.print(notifc);
        stadoNotifc = 1;
        }else{
        }
  }else if (indexNotifc == 3){ //Mostra o Alarm 2
        if (stadoNotifc == 0){
        tft.setCursor(CENTER, 108);
        tft.setTextScale(1);
        tft.setTextColor(WHITE);
        tft.print(notifc);
        stadoNotifc = 1;
        }else{
        }
  }else if(indexNotifc == 4){ //Mostra o aging reg, seja lá o que isso for
        if (stadoNotifc == 0){
        tft.setCursor(CENTER, 108);
        tft.setTextScale(1);
        tft.setTextColor(WHITE);
        tft.print(DS3231_get_aging(), DEC);
        stadoNotifc = 1;
        }else{
        }
  }else if(indexNotifc == 5){ //Mostra o Alarm que foi setado
        if (stadoNotifc == 0){
        tft.setCursor(CENTER, 108);
        tft.setTextScale(1);
        tft.setTextColor(WHITE);
        tft.print(notifc);
        stadoNotifc = 1;
        }else{
        }
   }else if(indexNotifc == 6){ //Mostra o Alarm 2 que foi setado
         if (stadoNotifc == 0){
         tft.setCursor(CENTER, 108);
         tft.setTextScale(1);
         tft.setTextColor(WHITE);
         tft.print(notifc);
         stadoNotifc = 1;
         }else{
         }
    }else if(indexNotifc == 7){ //Mostra a temperatura
          if (stadoNotifc == 0){
          tft.setCursor(CENTER, 108);
          tft.setTextScale(1);
          tft.setTextColor(WHITE);
          tft.print(DS3231_get_treg(), DEC);
          stadoNotifc = 1;
          }else{
          }
     }else if(indexNotifc == 8){ //Mostra "Status Reseted"
           if (stadoNotifc == 0){
           tft.setCursor(CENTER, 108);
           tft.setTextScale(1);
           tft.setTextColor(WHITE);
           tft.print("Status Reseted");
           stadoNotifc = 1;
           }else{
           }
      }else if(indexNotifc == 9){ //Mostra o Alarm que foi setado
            if (stadoNotifc == 0){
            tft.setCursor(CENTER, 108);
            tft.setTextScale(1);
            tft.setTextColor(WHITE);
            tft.print("orig ");
            tft.print(reg_gval,DEC);
            tft.print("month is ");
            tft.println(bcdtodec(reg_gval & 0x1F),DEC);
            stadoNotifc = 1;
            }else{
            }
       }else if(indexNotifc == 10){ //Mostra o status do reg
             if (stadoNotifc == 0){
             tft.setCursor(CENTER, 108);
             tft.setTextScale(1);
             tft.setTextColor(WHITE);
             tft.print(DS3231_get_sreg(), DEC);
             stadoNotifc = 1;
             }else{
             }
        }else if(indexNotifc == 11){ //Mostra "Comando Desconhecido"
              if (stadoNotifc == 0){
              tft.setCursor(CENTER, 108);
              tft.setTextScale(1);
              tft.setTextColor(WHITE);
              tft.print("Comando Desconhecido");
              stadoNotifc = 1;
              }else{
              }
         }
}
