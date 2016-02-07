#include <DS3231.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>
#define  BLACK   0x0000
#define  BLUE    0x001F
#define  RED     0xF800
#define  GREEN   0x07E0
#define  CYAN    0x07FF
#define  MAGENTA 0xF81F
#define  YELLOW  0xFFE0  
#define  WHITE   0xFFFF
#define __CS 10
#define __DC 8
DS3231 Clock;
bool Century=false;
bool h12;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;
byte year, month, date, DoW, hour, minute, second, temperature;
Adafruit_BMP085 bmp180;
int i;
TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC, 9);

void setup() {
  bmp180.begin();
  tft.begin();
  tft.fillScreen();
  delay(500);
  Wire.begin();
  tft.setRotation(2);
  Clock.setSecond(00);
  Clock.setMinute(31);
  Clock.setHour(15); 
  Clock.setDoW(1); 
  Clock.setDate(07); 
  Clock.setMonth(02); 
  Clock.setYear(16); 
}

void loop() {
  relogioMenu1();
  delay(60000);
}

void displayTime(){
  
 int second,minute,hour,date,month,year,temperature, day;
 second=Clock.getSecond();
 minute=Clock.getMinute();
 hour=Clock.getHour(h12, PM);
 date=Clock.getDate();
 day=Clock.getDoW();
 month=Clock.getMonth(Century);
 year=Clock.getYear();
  Serial.print(hour, DEC);
  Serial.print(":");
  if (minute<10)
  {
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second<10)
  {
    Serial.print("0");
  }
}

void relogioMenu1(){
  
 int second,minute,hour,date,month,year,temperature;
 second=Clock.getSecond();
 minute=Clock.getMinute();
 hour=Clock.getHour(h12, PM);
 date=Clock.getDate();
 month=Clock.getMonth(Century);
 year=Clock.getYear();

 temperature=Clock.getTemperature();
 tft.setTextColor(WHITE);
 tft.setTextSize(1);
 tft.setCursor(40, 10);
 tft.print('/');
 tft.print(date,DEC);
 tft.print(month,DEC);
 tft.print('/');
 tft.print("20");
 tft.print(year,DEC);
 tft.setCursor(5, 35);
 tft.setTextColor(WHITE);
 tft.setTextSize(4);
 setWindowHoras();
 tft.print(hour,DEC);
 tft.print(':');
 tft.print(minute,DEC);
 setWindowTemp();
 tft.setCursor(0, 107);
 tft.setTextColor(WHITE);
 tft.setTextSize(1);
 tft.print("Temperatura:");
 tft.setTextSize(2);
 tft.setCursor(75, 100);
 tft.setTextColor(RED);
 tft.print(bmp180.readTemperature(),1);
 tft.print('\n');
 
}
void setWindowSegundos(){
for( i = 0; i < 1; i++)
{
tft.setAddrWindow(53, 64, 75, 86);
tft.fillRect(53, 64, 22, 22, BLACK);
}
}
void setWindowHoras(){
for( i = 0; i < 1; i++)
{
tft.setAddrWindow(5, 35, 120, 75);
tft.fillRect(5, 35, 120, 29, BLACK);
}
}
void setWindowTemp(){
for( i = 0; i < 1; i++)
{
tft.setAddrWindow(75, 90, 128, 128);
tft.fillRect(74, 90, 500, 300, BLACK);
}
}
