/*
Arduino library for controlling DS2482-100 and DS2482-800 1-wire masters.
Uses Wire library to communicate with DS2482 so be sure to call Wire.begin() before using the library.
Quick example modeled after Onewire example:
*/



#include "MegunoLink.h"
 #include "Plotter.h"
#include <Wire.h>
#include "DS2482.h"

Plotter p;
DS2482 ds(0);  //channels ds2482-800 is 0 to 7, DS2482-100 is just set 0
int a=0;
double imp_temp;
int count =0;
byte data[8]; //holding for onewire capture
byte addr[8]; //1wire wire address and CRC
byte one_addr[8]={0x28,0xF1,0x4F,0x4D,0x0A,0x00,0x00,0xCA};
 double Tc_100=0;
  TimePlot LightPlot;
void setup() 
{ 
  Wire.begin(); 
   
  ds.reset();
  p.Begin(); // start plotter      

  // start serial port
  Serial.begin(9600);
  
  
  ds.wireResetSearch();
  
   ds.wireReset(); 
  
   ds.wireSkip();
   //need to send high power to bus??  Adding 5 volts to devices makes it work.
    // ds.selectChannel(1);
   ds.wireWriteByte(0x44); //convert temperature on all devices
   delay(1000); //wait for conversion
 
     
//  p.AddTimeGraph( "Some title of a graph", 500, "label for x", Tc_100 );
}

void loop() 
{ 
  
  //do search
//...................
 if(count==0){
  ds.selectChannel(a);
 }
 count++; 
   if ( !ds.wireSearch(addr)) 
      {
      count=0;  
      a=a+1;
      if(a==8)
      a=0;
       Serial.print("Channel:"); 
  Serial.print(a); 
Serial.println(""); 
if(a==1){
// LightPlot.SendData("Light", (double)Tc_100);   

//  Serial.print("No more addresses.\n"); 
  
 //////// stuff to sense that one sensor on the graph//////////////////////////////////////////////////////
 
  ds.wireReset(); //ds.reset();
 // ds.selectChannel(0); //necessary on -800
  ds.wireSelect(one_addr);
     ds.wireWriteByte(0xbe);   
       for ( int i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.wireReadByte();

 //  if (data[i]<16)Serial.print("0"); 
 //  Serial.print(data[i],HEX);
 //     Serial.print(" ");
  }
  int LowByte = data[0];
  int HighByte = data[1];
  double TReading = (HighByte << 8) + LowByte;
//  int SignBit = (int)TReading & 0x8000;  // test most sig bit
//  if (SignBit) // negative
//  {
 ///   TReading = ((int)TReading ^ 0xffff) + 1; // 2's comp
 // }

   Tc_100 = (double)TReading * 0.0625 * 10;
//Serial.println(" ");
//Serial.println("Dope");
//Serial.println(Tc_100/10);
 LightPlot.SendData("Light", (double)Tc_100);   

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ds.wireResetSearch();
  
  // set up en 12 bits (0x7F)
 // ds.wireWriteByte(0x48);
   ds.wireReset(); 
 //   ds.selectChannel(1);
  // copy scratchpad to EEPROM
   ds.wireSkip();
   //need to send high power to bus??  Adding 5 volts to devices makes it work.
  // ds.selectChannel(1);
   ds.wireWriteByte(0x44); //convert temperature on all devices
   delay(1000); //wait for conversion 
 // ds.wireWriteByte(0x4E); // write on scratchPad

    return; 
      }
  //  Serial.print("Temp =");
  //  Serial.print(count);
 //   Serial.print(" ");  
 //  Serial.print("ROM =");
   for( int i = 0; i < 8; i++) {
//    Serial.write(' ');
//   if (addr[i] < 16) Serial.print("0");
 //    Serial.print(addr[i], HEX);
    }
   
   if (ds.crc8(addr, 7) != addr[7]) {
 //   Serial.println("CRC is not valid!");
    return;
   }
  int i=0;
  //test if device code DS18b20
if (addr[0]==0x28) {

  //read temperature data.
  ds.wireReset(); //ds.reset();
//  ds.selectChannel(a); //necessary on -800
  ds.wireSelect(addr);
  i++;
  ds.wireWriteByte(0xbe);         // Read Scratchpad command

  
//display hex values of scratchpad
//  Serial.println(" ");
//   Serial.print("Scratch pad value");
  for ( int i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.wireReadByte();

 //  if (data[i]<16)Serial.print("0"); 
 //  Serial.print(data[i],HEX);
 //     Serial.print(" ");
  }


//convert to decimal temperature

  int LowByte = data[0];
  int HighByte = data[1];
  double TReading = (HighByte << 8) + LowByte;
//  int SignBit = (int)TReading & 0x8000;  // test most sig bit
//  if (SignBit) // negative
//  {
 ///   TReading = ((int)TReading ^ 0xffff) + 1; // 2's comp
 // }

   Tc_100 = (double)TReading * 0.0625 * 10;

//  if (SignBit) // If its negative
//  {
//     Tc_100=0-Tc_100;
//  }
 
  //print temp for each device 
    count=count+1;
//  Serial.print("Temperature");                                                                                                                                                                                                                                 
//   Serial.print("=");
 ///    p.Plot(); 
    Serial.println(Tc_100/10,4);
  //  Serial.print(".");
  //  Serial.println((int)Tc_100%10);
  
   
}

}
