





















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

//byte data[8]; //holding for onewire capture
byte addr_1[8][9]; //1wire wire address and CRC
byte addr_2[8][9]; 
byte addr_3[8][9]; 
byte addr_4[8][9]; 
byte addr_5[8][9]; 
byte addr_6[8][9]; 
byte addr_7[8][9]; 
byte addr_8[8][9]; 
byte addr[8][9]; 
 

byte one_addr[8]={0x28,0x73,0x48,0x4D,0x0A,0x00,0x00,0x1f};
byte two_addr[8]={0x28,0x47,0x41,0x4D,0x0A,0x00,0x00,0xDD};
 double Tc_100=0;
  TimePlot LightPlot;
void setup() 
{ 
   Wire.begin(); 
   ds.configure(0x01);
  ds.reset();
  p.Begin(); // start plotter      

  // start serial port
  Serial.begin(9600);
  
  
  ds.wireResetSearch();
 
   ds.wireReset(); 
  
   ds.wireSkip();
   //need to send high power to bus??  Adding 5 volts to devices makes it work.
    ds.selectChannel(0);
   ds.wireWriteByte(0x44); //convert temperature on all devices
   delay(1000); //wait for conversion
   for(int i=0;i<8;i++){
 ds.wireSearch(addr_1[i]);
  
 }
 ds.wireResetSearch();
 
   ds.wireReset(); 
  
   ds.wireSkip();
   //need to send high power to bus??  Adding 5 volts to devices makes it work.
 
   ds.wireWriteByte(0x44); //convert temperature on all devices
   delay(1000); //wait for conversion
      ds.selectChannel(1);
   for(int i=0;i<8;i++){
 ds.wireSearch(addr_2[i]);
  
 }
  ds.wireResetSearch();
 
   ds.wireReset(); 
  
   ds.wireSkip();
   //need to send high power to bus??  Adding 5 volts to devices makes it work.
 
   ds.wireWriteByte(0x44); //convert temperature on all devices
   delay(1000); //wait for conversion
      ds.selectChannel(2);
   for(int i=0;i<8;i++){
 ds.wireSearch(addr_3[i]);
  
 }
  ds.wireResetSearch();
 
   ds.wireReset(); 
  
   ds.wireSkip();
   //need to send high power to bus??  Adding 5 volts to devices makes it work.
 
   ds.wireWriteByte(0x44); //convert temperature on all devices
   delay(1000); //wait for conversion
      ds.selectChannel(6);
   for(int i=0;i<8;i++){
 ds.wireSearch(addr_7[i]);
  
 }
 ds.wireResetSearch();
 
   ds.wireReset(); 
  
   ds.wireSkip();
   //need to send high power to bus??  Adding 5 volts to devices makes it work.
 
   ds.wireWriteByte(0x44); //convert temperature on all devices
   delay(1000); //wait for conversion
      ds.selectChannel(3);
   for(int i=0;i<8;i++){
 ds.wireSearch(addr_4[i]);
  
 }
 ds.wireResetSearch();
 
   ds.wireReset(); 
  
   ds.wireSkip();
   //need to send high power to bus??  Adding 5 volts to devices makes it work.
 
   ds.wireWriteByte(0x44); //convert temperature on all devices
   delay(1000); //wait for conversion
      ds.selectChannel(4);
   for(int i=0;i<8;i++){
 ds.wireSearch(addr_5[i]);
  
 }
  ds.wireResetSearch();
 
   ds.wireReset(); 
  
   ds.wireSkip();
   //need to send high power to bus??  Adding 5 volts to devices makes it work.
 
   ds.wireWriteByte(0x44); //convert temperature on all devices
   delay(1000); //wait for conversion
      ds.selectChannel(5);
   for(int i=0;i<8;i++){
 ds.wireSearch(addr_6[i]);
  
 }
 ds.wireResetSearch();
 
   ds.wireReset(); 
  
   ds.wireSkip();
   //need to send high power to bus??  Adding 5 volts to devices makes it work.
 
   ds.wireWriteByte(0x44); //convert temperature on all devices
   delay(1000); //wait for conversion
      ds.selectChannel(7);
   for(int i=0;i<8;i++){
 ds.wireSearch(addr_8[i]);
  
 }
 }
     
//  p.AddTimeGraph( "Some title of a graph", 500, "label for x", Tc_100 );


void loop() 
{
  Serial.println("Test Done"); 
  for( int j = 0; j < 8; j++) {
  
 while(!ds.selectChannel(j));    
ds.wireReset(); 
    
   ds.wireSkip();
   //need to send high power to bus??  Adding 5 volts to devices makes it work.
 
   ds.wireWriteByte(0x44); //convert temperature on all devices

  
     
   
  }
   delay(600 ); 
    for( int j = 0; j < 8; j++) {

    Serial.print("Channel:"); 
  Serial.print(j); 
Serial.println("");
 //  ds.selectChannel(j);

    for( int k = 0; k < 8; k++) {
        ds.selectChannel(j);
         ds.wireReset();
      
 
   
   if(j==0)
    ds.wireSelect(addr_1[k]);
    if(j==1) 
     ds.wireSelect(addr_2[k]);
      if(j==2) 
     ds.wireSelect(addr_3[k]);
     if(j==3) 
     ds.wireSelect(addr_4[k]);
     if(j==4) 
     ds.wireSelect(addr_5[k]);
     if(j==5) 
     ds.wireSelect(addr_6[k]);
      if(j==6) 
     ds.wireSelect(addr_7[k]);
     if(j==7) 
     ds.wireSelect(addr_8[k]);
 ds.wireWriteByte(0xbe);         // Read Scratchpad command
//   for( int i = 0; i < 8; i++) {
//    Serial.write(' ');
//    if(j==0){
//   if (addr_2[k] < 16) Serial.print("0");
//     Serial.print(addr_1[k][i], HEX);
//    }
//     if(j==1){
//   if (addr_2[k] < 16) Serial.print("0");
//     Serial.print(addr_2[k][i], HEX);
//    }
//     if(j==5){
//   if (addr_2[k] < 16) Serial.print("0");
//     Serial.print(addr_6[k][i], HEX);
//    }
//   
//   if(j==2){
//   if (addr_2[k] < 16) Serial.print("0");
//     Serial.print(addr_3[k][i], HEX);
//    }
//   }
//   
//    Serial.println(" ");
////display hex values of scratchpad
//  Serial.println(" ");
//   Serial.print("Scratch pad value");
  for ( int i = 0; i < 8; i++) {           // we need 9 bytes
    data[i] = ds.wireReadByte();
  }
int LowByte = data[0];
  int HighByte = data[1];
  double TReading = (HighByte << 8) + LowByte;
////  int SignBit = (int)TReading & 0x8000;  // test most sig bit
////  if (SignBit) // negative
////  {
// ///   TReading = ((int)TReading ^ 0xffff) + 1; // 2's comp
// // }
//
   Tc_100 = (double)TReading * 0.0625 * 10;
//
////  if (SignBit) // If its negative
////  {
////     Tc_100=0-Tc_100;
////  }
// 
//  //print temp for each device 
//    count=count+1;
////  Serial.print("Temperature");                                                                                                                                                                                                                                 
////   Serial.print("=");
// ///    p.Plot(); 
if(Tc_100/10==-0.0625)
   Serial.print("");
   else
   Serial.println(Tc_100/10,4);
//  Serial.print(".");
//  Serial.println((int)Tc_100%10);
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////plot crap
 if(j==2){
// LightPlot.SendData("Light", (double)Tc_100);   

//  Serial.print("No more addresses.\n"); 
  
 //////// stuff to sense that one sensor on the graph//////////////////////////////////////////////////////
 
  ds.wireReset(); //ds.reset();
 // ds.selectChannel(0); //necessary on -800
  ds.wireSelect(two_addr);
     ds.wireWriteByte(0xbe);   
       for ( int i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.wireReadByte();

//   if (data[i]<16)Serial.print("0"); 
//   Serial.print(data[i],HEX);
//      Serial.print(" ");
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
 LightPlot.SendData("Bus_2", (double)Tc_100);  
  }
    
    if(j==5){
// LightPlot.SendData("Light", (double)Tc_100);   

//  Serial.print("No more addresses.\n"); 
  
 //////// stuff to sense that one sensor on the graph//////////////////////////////////////////////////////
 
  ds.wireReset(); //ds.reset();
 // ds.selectChannel(0); //necessary on -800
  ds.wireSelect(one_addr);
     ds.wireWriteByte(0xbe);   
       for ( int i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.wireReadByte();

//   if (data[i]<16)Serial.print("0"); 
//   Serial.print(data[i],HEX);
//      Serial.print(" ");
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
 LightPlot.SendData("Bus_5", (double)Tc_100);  
  }
    }
}











































































   

















  
