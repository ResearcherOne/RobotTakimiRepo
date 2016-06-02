/*******************************************************************
说明：MPU6050+HMC5883+BMP085
设计：allyzc
网站：www.wandianlain.com
日期：2015.9.7
********************************************************************/
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 accelgyro; 

int16_t ax, ay, az;
int16_t gx, gy, gz;
#define HMCaddress 0x1E 

char str[512]; 

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    HMC5883_init();
    BMP085_init();
    accelgyro.initialize();
    accelgyro.setI2CMasterModeEnabled(0);
    accelgyro.setI2CBypassEnabled(1);
    if((!accelgyro.getI2CMasterModeEnabled()) && accelgyro.getI2CBypassEnabled())
    Serial.println("Set MPU6000 Bypass Mode success!\n");
}

//HMC5883
//#define HMCaddress 0x1E //0011110b, I2C 7bit address of HMC5883

void HMC5883_init()
{
   Wire.beginTransmission(HMCaddress); //open communication with HMC5883
   Wire.write(0x02); //select mode register
   Wire.write(0x00); //continuous measurement mode
   Wire.endTransmission(); 
}

void HMC5883_set()
{
   int x,y,z; //triple axis data
  //Tell the HMC5883 where to begin reading data
  Wire.beginTransmission(HMCaddress);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();

   //Read data from each axis, 2 registers per axis
   Wire.requestFrom(HMCaddress, 6);
   if(6<=Wire.available())
   {
      x = Wire.read()<<8; //X msb
      x |= Wire.read(); //X lsb
      z = Wire.read()<<8; //Z msb
      z |= Wire.read(); //Z lsb
      y = Wire.read()<<8; //Y msb
      y |= Wire.read(); //Y lsb
   }

//Print out values of each axis
   Serial.print("HMC5883: ");
   Serial.print("X: ");
   Serial.print(x);
   Serial.print(" Y: ");
   Serial.print(y);
   Serial.print(" Z: ");
   Serial.print(z);
   Serial.println(" ");
   // delay(2000); 
}
void MPU6050_set()
{
     accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
     sprintf(str, "%d,%d,%d,%d,%d,%d", ax, ay, az, gx, gy, gz); 
     //Serial.println(" ");
     Serial.print("MPU6050: "); 
     Serial.print(str);
     Serial.write(byte(10));
     // Serial.println(" ");
}

#define BMP085_ADDRESS 0x77 // I2C address of BMP085

const unsigned char OSS = 0; // Oversampling Setting
// Calibration values
int ac1;
int ac2; 
int ac3; 
unsigned int ac4;
unsigned int ac5;
unsigned int ac6;
int b1; 
int b2;
int mb;
int mc;
int md;

// b5 is calculated in bmp085GetTemperature(...), this variable is also used in bmp085GetPressure(...)
// so ...Temperature(...) must be called before ...Pressure(...).
long b5; 

short temperature;
long pressure;

void BMP085_init()
{
    ac1 = bmp085ReadInt(0xAA);
    ac2 = bmp085ReadInt(0xAC);
    ac3 = bmp085ReadInt(0xAE);
    ac4 = bmp085ReadInt(0xB0);
    ac5 = bmp085ReadInt(0xB2);
    ac6 = bmp085ReadInt(0xB4);
    b1 = bmp085ReadInt(0xB6);
    b2 = bmp085ReadInt(0xB8);
    mb = bmp085ReadInt(0xBA);
    mc = bmp085ReadInt(0xBC);
    md = bmp085ReadInt(0xBE);
}

short bmp085GetTemperature(unsigned int ut)
{
    long x1, x2;
    x1 = (((long)ut - (long)ac6)*(long)ac5) >> 15;
    x2 = ((long)mc << 11)/(x1 + md);
    b5 = x1 + x2;
    return ((b5 + 8)>>4); 
}

// Calculate pressure given up
// calibration values must be known
// b5 is also required so bmp085GetTemperature(...) must be called first.
// Value returned will be pressure in units of Pa.
long bmp085GetPressure(unsigned long up)
{
   long x1, x2, x3, b3, b6, p;
   unsigned long b4, b7;
   b6 = b5 - 4000;
   // Calculate B3
   x1 = (b2 * (b6 * b6)>>12)>>11;
   x2 = (ac2 * b6)>>11;
   x3 = x1 + x2;
   b3 = (((((long)ac1)*4 + x3)<<OSS) + 2)>>2;
   // Calculate B4
   x1 = (ac3 * b6)>>13;
   x2 = (b1 * ((b6 * b6)>>12))>>16;
   x3 = ((x1 + x2) + 2)>>2;
   b4 = (ac4 * (unsigned long)(x3 + 32768))>>15;
   b7 = ((unsigned long)(up - b3) * (50000>>OSS));
   if (b7 < 0x80000000)
      p = (b7<<1)/b4;
   else
      p = (b7/b4)<<1;
   x1 = (p>>8) * (p>>8);
   x1 = (x1 * 3038)>>16;
   x2 = (-7357 * p)>>16;
   p += (x1 + x2 + 3791)>>4;
   return p;
}

// Read 1 byte from the BMP085 at 'address'
char bmp085Read(unsigned char address)
{
   unsigned char data;
  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(BMP085_ADDRESS, 1);
  while(!Wire.available());
  return Wire.read();
}

// Read 2 bytes from the BMP085
// First byte will be from 'address'
// Second byte will be from 'address'+1
int bmp085ReadInt(unsigned char address)
{
   unsigned char msb, lsb;
   Wire.beginTransmission(BMP085_ADDRESS);
   Wire.write(address);
   Wire.endTransmission();
   Wire.requestFrom(BMP085_ADDRESS, 2);
   while(Wire.available()<2);
   msb = Wire.read();
   lsb = Wire.read();
   return (int) msb<<8 | lsb;
}

// Read the uncompensated temperature value
unsigned int bmp085ReadUT()
{
   unsigned int ut;

           // Write 0x2E into Register 0xF4
          // This requests a temperature reading
          Wire.beginTransmission(BMP085_ADDRESS);
          Wire.write(0xF4);
          Wire.write(0x2E);
          Wire.endTransmission();
           // Wait at least 4.5ms
           delay(5);
          // Read two bytes from registers 0xF6 and 0xF7
          ut = bmp085ReadInt(0xF6);
          return ut;
}

// Read the uncompensated pressure value
unsigned long bmp085ReadUP()
{
   unsigned char msb, lsb, xlsb;
   unsigned long up = 0;
   // Write 0x34+(OSS<<6) into register 0xF4
   // Request a pressure reading w/ oversampling setting
   Wire.beginTransmission(BMP085_ADDRESS);
   Wire.write(0xF4);
   Wire.write(0x34 + (OSS<<6));
   Wire.endTransmission();
   // Wait for conversion, delay time dependent on OSS
   delay(2 + (3<<OSS));
   // Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
   Wire.beginTransmission(BMP085_ADDRESS);
   Wire.write(0xF6);
   Wire.endTransmission();
   Wire.requestFrom(BMP085_ADDRESS, 3);
   // Wait for data to become available
   while(Wire.available() < 3);
   msb = Wire.read();
   lsb = Wire.read();
   xlsb = Wire.read();
   up = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-OSS);
   return up;
}
void BMP085_set()
{
   temperature = bmp085GetTemperature(bmp085ReadUT());
   pressure = bmp085GetPressure(bmp085ReadUP());
   Serial.print("Temperature: ");
   Serial.print(temperature*0.1);
   Serial.println(" C ");
   Serial.print("Pressure: ");
   Serial.print(pressure*0.001);
   Serial.println(" K Pa");
   Serial.println();
   //delay(2000);
}

void loop()
{

   MPU6050_set();
   HMC5883_set();
   BMP085_set();
   delay(1000);
}
