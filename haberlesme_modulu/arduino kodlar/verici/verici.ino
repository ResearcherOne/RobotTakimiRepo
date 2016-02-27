#include <SPI.h>
#include <nRF24L01p.h>
 
// Pinler Sırayla CSN ve CE'dir.
nRF24L01p verici(7, 8);
 
void setup() {
  delay(150);
  Serial.begin(9600);
  
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  verici.channel(90); // Kanal numaraları aynı olmalı(0-125)
  verici.TXaddress("Oda 1");
  verici.RXaddress("Oda 2");
  verici.init();
}
 
String ileti = "Selam!";
String ileti2;
 
long int x = millis();
void loop() {
  // 1 saniye dolduysa yeni veri gönder
  if ( millis() - x >= 1000) {
    Serial.println("== Giden Veri Var");
    x = millis();
    verici.txPL(ileti+String(x/1000));
    verici.send(SLOW);
  }
  
  // Gelen veri varsa
  if (verici.available()) {
    Serial.print("== Gelen Veri Var: ");
    verici.read();
    verici.rxPL(ileti2);
    Serial.println(ileti2);
    ileti2 = "";
  }
}
