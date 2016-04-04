#include <SPI.h>
#include <nRF24L01p.h>
 
// Pinler Sırayla CSN ve CE'dir.
nRF24L01p alici(7,8);
 
void setup(){
  delay(150);
  Serial.begin(9600);
  
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  alici.channel(90); // Kanal numaraları aynı olmalı(0-125)
  alici.RXaddress("Oda 1");
  alici.TXaddress("Oda 2");
  alici.init();
}
 
// Gelen mesajı tutacak
String ileti;
 
void loop(){ 
  // Gelen veri varsa
  if(alici.available()){
    alici.read();
    alici.rxPL(ileti);
    Serial.println(ileti);
    ileti = "";
    alici.txPL("Mesaj alindi!");
    alici.send(SLOW);
  }
}
