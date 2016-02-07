#define DS3231_I2C_ADDRESS 0x68
#include <DS3231.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>
#define    BLACK   0x0000
#define    BLUE    0x001F
#define    RED     0xF800
#define    GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF
#define __CS 10
#define __DC 8

Adafruit_BMP085 bmp180;

DS3231 Clock;
TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC, 9);
// Convert normal decimal numbers to binary coded decimal

char escrita[10];
char dataDMA[12];

bool Century=false;
bool h12;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;
byte year, month, date, DoW, hour, minute, second, temperature, day;

int mostrador = 0;

void setup()
{
  
  bmp180.begin();
  tft.begin();
  Wire.begin();


  tft.setRotation(2);

 Clock.setSecond(00);//Set the second
 Clock.setMinute(8);//Set the minute
 Clock.setHour(13); //Set the hour
 Clock.setDoW(1); //Set the day of the week
 Clock.setDate(07); //Set the date of the month
 Clock.setMonth(02); //Set the month of the year
 Clock.setYear(16); //Set the year (Last two digits of the year)

  // set the initial time here:
  // DS3231 seconds, minutes, hours, day, date, month, year
  // setDS3231time(30,42,21,4,26,11,14);
}

void displayTime()
{
 int second,minute,hour,date,month,year,temperature, day;
 second=Clock.getSecond();
 minute=Clock.getMinute();
 hour=Clock.getHour(h12, PM);
 date=Clock.getDate();
 day=Clock.getDoW();
 month=Clock.getMonth(Century);
 year=Clock.getYear();
  // send it to the serial monitor
  Serial.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
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
  Serial.print(second, DEC);
  Serial.print(" ");
  Serial.print(date, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
  Serial.print(" Day of week: ");
  switch(day){
  case 1:
    Serial.println("Sunday");
    tft.print("Sunday");
    break;
  case 2:
    Serial.println("Monday");
    break;
  case 3:
    Serial.println("Tuesday");
    break;
  case 4:
    Serial.println("Wednesday");
    break;
  case 5:
    Serial.println("Thursday");
    break;
  case 6:
    Serial.println("Friday");
    break;
  case 7:
    Serial.println("Saturday");
    break;
  }
}
void loop()
{ // display the real-time clock data on the Serial Monitor,
  tft.setCursor(0, 0);
  relogio();
  delay(1000);
 
  

}
void segundos() {
 int second,minute,hour,date,month,year,temperature;
 second=Clock.getSecond();
 minute=Clock.getMinute();
 hour=Clock.getHour(h12, PM);
 date=Clock.getDate();
 month=Clock.getMonth(Century);
 year=Clock.getYear();
 tft.fillRect(53, 74, 22, 20, BLACK);
 tft.setTextColor(CYAN);
 tft.setTextSize(2);
 tft.setCursor(53, 74);
 tft.print(second);
 tft.println();

}
void horas() {
 int second,minute,hour,date,month,year,temperature;
 second=Clock.getSecond();
 minute=Clock.getMinute();
 hour=Clock.getHour(h12, PM);
 date=Clock.getDate();
 month=Clock.getMonth(Century);
 year=Clock.getYear();
  tft.fillRect(5, 35, 128, 35, BLACK);
 tft.setCursor(5, 35);
 tft.setTextColor(BLACK);
 tft.setTextSize(4);
 sprintf(escrita, "%02d:%02d" ,hour-1, minute-1);
 tft.print(escrita);
 tft.setCursor(5, 35);
 tft.setTextColor(WHITE);
 tft.setTextSize(4);
 sprintf(escrita, "%02d:%02d" ,hour, minute);
 tft.print(escrita);
 tft.println();
}

void data() {
 int second,minute,hour,date,month,year,temperature;
 second=Clock.getSecond();
 minute=Clock.getMinute();
 hour=Clock.getHour(h12, PM);
 date=Clock.getDate();
 month=Clock.getMonth(Century);
 year=Clock.getYear();
 tft.setCursor(0, 0);
 tft.println();
 tft.setTextColor(WHITE);
 tft.setTextSize(1);
 tft.setCursor(35, 10);
 sprintf(dataDMA, "%02d/%02d/20%02d", date,month, year);
 tft.print(dataDMA);
 tft.println();
 tft.println();
}

void temp() {
 int second,minute,hour,date,month,year,temperature, day;
 second=Clock.getSecond();
 minute=Clock.getMinute();
 day=Clock.getDoW();
 hour=Clock.getHour(h12, PM);
 date=Clock.getDate();
 month=Clock.getMonth(Century);
 year=Clock.getYear();
 temperature=Clock.getTemperature();
 tft.fillRect(85, 100, 60, 40, BLACK);

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


void relogio()
{
 int second,minute,hour,date,month,year,temperature;
 second=Clock.getSecond();
 minute=Clock.getMinute();
 hour=Clock.getHour(h12, PM);
 date=Clock.getDate();
 month=Clock.getMonth(Century);
 year=Clock.getYear();
 tft.setRotation(2);
 data();
 segundos();
 horas();
 temp();
}

void Temperatura()
{
 int second,minute,hour,date,month,year,temperature;
 second=Clock.getSecond();
 minute=Clock.getMinute();
 hour=Clock.getHour(h12, PM);
 date=Clock.getDate();
 month=Clock.getMonth(Century);
 year=Clock.getYear();
 tft.setRotation(2);
   tft.setCursor(0, 0);
   tft.print("Temp. :  ");
   Serial.print("Temperatura : ");
   if ( bmp180.readTemperature() < 10)
   {
     tft.print(" "); 
     tft.print(bmp180.readTemperature());
     Serial.print(bmp180.readTemperature());
     Serial.println(" C");
   }
   else
   {
     tft.print(bmp180.readTemperature(),1);
     Serial.print(bmp180.readTemperature(),1);
     Serial.println(" C");
   }
   tft.print(" ");
   tft.print((char)223); 
   tft.print("C   ");
       
   if (mostrador == 0)
   {
     tft.setCursor(0, 1);
     tft.print("                ");
     tft.setCursor(0, 1);
     tft.print("Altit.: ");
     Serial.print("Altitude : ");
     tft.print(bmp180.readAltitude());
     Serial.print(bmp180.readAltitude());
     Serial.println(" m");
     tft.print(" m");  
    }
   if (mostrador == 1)
   {
     tft.setCursor(0, 1);
     tft.print("                ");
     tft.setCursor(0, 1);
     tft.print("Press.: ");
     Serial.print("Pressao : ");
     tft.print(bmp180.readPressure());  
     Serial.print(bmp180.readPressure());  
     Serial.println(" Pa");
     tft.print(" Pa");
   }
}

