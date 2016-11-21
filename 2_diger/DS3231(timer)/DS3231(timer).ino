#include "Wire.h"
#define DS3231_I2C_ADDRESS 0x68

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val){
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val){
  return( (val/16*10) + (val%16) );
}

// Zamanı okuyan metod bu
void readDS3231time(byte *second, byte *minute, byte *hour,
  byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year){
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

//Ben yazdım, eğer değerler tek basamaklıysa başına sıfır koyması için display ederken
void displayCorrectly(byte info){
  if (info<10){
    Serial.print("0");
  }
  Serial.print(info,DEC);
}

//Seri ekranda gösterilmesini sağlayan metod, kontroller için gerekli olacak
void displayTime(){
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
  // send it to the serial monitor
  byte timeArray[]={hour, minute, second, dayOfMonth, month, year};
  for (int i=0;i<6;i++){
    displayCorrectly(timeArray[i]);
    if (i>=0 && i<2){
      Serial.print(":");
    } else if (i==2){
      Serial.print(" ");
    } else{
      Serial.print("/");
    }
  }
  Serial.print(" Day of week: ");
  //bu kısmı ben hemen üstte yeniden yazdım daha temiz oldu
  /*Serial.print(hour, DEC);// convert the byte variable to a decimal number when displayed
  Serial.print(":");
  if (minute<10){
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second<10){
    Serial.print("0");
  }
  Serial.print(second, DEC);
  Serial.print(" ");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
  Serial.print(" Day of week: ");*/
  
  switch(dayOfWeek){
  case 1:
    Serial.println("Sunday");
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

void setup(){
  Wire.begin();
  Serial.begin(9600);
  /* alttaki set metodu ile bir keze mahsus olmak üzere RTC'nin saatini kurabilirsin, sonra burayı silmeyi unutma*/
  // set the initial time here:
  // DS3231 seconds, minutes, hours, day, date, month, year
  // setDS3231time(30,40,16,7,05,11,16);
}

void loop(){
  displayTime(); // display the real-time clock data on the Serial Monitor,
  delay(1000); // every second
}

/*void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
dayOfMonth, byte month, byte year){
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}*/
