/*
* Ethernet_Test.ino - Simple sketch to listen for E1.31 data on an 
*                     UNO Ethernet shield and print some statistics.
*
* Project: E131 - E.131 (sACN) library for Arduino
* Copyright (c) 2015 Shelby Merrick
* http://www.forkineye.com
*
*  This program is provided free for you to use in any way that you wish,
*  subject to the laws and regulations where you are using it.  Due diligence
*  is strongly suggested before using this code.  Please give credit where due.
*
*  The Author makes no warranty of any kind, express or implied, with regard
*  to this program or the documentation contained in this document.  The
*  Author shall not be liable in any event for incidental or consequential
*  damages in connection with, or arising out of, the furnishing, performance
*  or use of these programs.
*
*/
#include <SPI.h>
#include <Ethernet.h>
#include "E131.h"
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//Pin connected to ST_CP of 74HC595, HW pin: 
int latchPin = 8;
//Pin connected to SH_CP of 74HC595, HW pin:
int clockPin = 7;
////Pin connected to DS of 74HC595, HW pin:
int dataPin = 9;

#define NUMCHANNELS 24

byte mac[] = { 0xDE, 0xAD, 0xBE, 0x2F, 0x1E, 0xE4 };

E131 e131;

void setup() {
    Serial.begin(115200);
    delay(10);

    /* Configure via DHCP and listen Unicast on the default port */
    e131.begin(mac);
    
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
}

void loop() {
    /* Parse a packet */
    uint16_t num_channels = e131.parsePacket();
    
    /* Process channel data if we have it */
    if (num_channels) {
//        Serial.print(F("Universe "));
//        Serial.print(e131.universe);
//        Serial.print(F(" / "));
//        Serial.print(num_channels);
//        Serial.print(F(" Channels | Packet#: "));
//        Serial.print(e131.stats.num_packets);
//        Serial.print(F(" / Errors: "));
//        Serial.print(e131.stats.packet_errors);
//        Serial.print(F(" / CH1: "));
//        Serial.print(e131.data[0]);
//        Serial.print(F(" / CH2: "));
//        Serial.print(e131.data[1]);
//        Serial.print(F(" / CH3: "));
//        Serial.print(e131.data[2]);
//        Serial.print(F(" / CH4: "));
//        Serial.print(e131.data[3]);
//        Serial.print(F(" / CH5: "));
//        Serial.print(e131.data[4]);
//        Serial.print(F(" / CH6: "));
//        Serial.print(e131.data[5]);
//        Serial.print(F(" / CH7: "));
//        Serial.print(e131.data[6]);
//        Serial.print(F(" / CH8: "));
//        Serial.print(e131.data[7]);
         uint8_t data1 = 0;
         uint8_t data2 = 0;
         uint8_t data3 = 0;
         
         for(int i=0; i<8; i++) {
            if(e131.data[i]){
              data1 = data1 + (1<<i);
            }
            if(e131.data[i+8]){
              data2 = data2 + (1<<i);
            } 
            if(e131.data[i+16]){
              data3 = data3 + (1<<i);
            }           
         }
//         Serial.print(F(" / DATA1: "));
//         Serial.println(data1);
//         Serial.print(F(" / DATA2: "));
//         Serial.println(data2);
//         Serial.print(F(" / DATA3: "));
//         Serial.println(data3);
         
         digitalWrite(latchPin, 0);
         shiftOut(dataPin, clockPin, MSBFIRST, data1);
         shiftOut(dataPin, clockPin, MSBFIRST, data2);
         shiftOut(dataPin, clockPin, MSBFIRST, data3);
         digitalWrite(latchPin, 1);
      
    }
}
