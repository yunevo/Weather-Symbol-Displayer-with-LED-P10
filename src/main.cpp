#include <Arduino.h>
#include "symbol.h"
#define OE 9
#define A 6
#define B 7
#define CLK 13 
#define SCLK 8
#define DS 11
#define GND 12
#define SW0 2
#define SW1 3
#define muc 1
#define RELAY 5
int8_t state;
int sang = 200;
unsigned long pastHinh0, pastHinh1, pastHinh2, pastHinh3, pastHinh4, pastHinh5, pastHinh6; 
unsigned long thresSun = 1000, thresRain = 100, thresCloud = 200, thresWind = 150;


int docNut();

void isr(){
  detachInterrupt(SW0); // Ngat interrupt
  detachInterrupt(SW1);
  delay(100); // Chong nhieu
  state = docNut();
  attachInterrupt(digitalPinToInterrupt(SW0), isr, CHANGE); // Cho phep interrupt
  attachInterrupt(digitalPinToInterrupt(SW1), isr, CHANGE);
}
void chuyen(unsigned char b);
void hang(int8_t line);
void hienThi(unsigned char arr[][4]);
void setup() {
  // put your setupmm  code here, to run once:
  pinMode(OE, OUTPUT); //set up chan
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(SCLK, OUTPUT);
  pinMode(DS, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(SW0, INPUT);
  pinMode(SW1, INPUT); 
  pinMode(GND, OUTPUT);
  state = docNut();
  attachInterrupt(digitalPinToInterrupt(SW0), isr, CHANGE); // Cho phep interrupt
  attachInterrupt(digitalPinToInterrupt(SW1), isr, CHANGE);
  digitalWrite(GND, 0);
  digitalWrite(RELAY, 1);
  delay(1000); //Khoi dong
  pastHinh0 = millis();
}

void loop() {
  switch(state){
    case 0: //Che do 0
      pastHinh0 = millis();
      while (millis() - pastHinh0 < thresSun){ //Hien thi anh sun0 trong thresSun ms
        hienThi(sun0);
      }
      
      pastHinh1 = millis();
      while (millis() - pastHinh1 < thresSun){ //Hienthi anh sun1 trong thresSun ms
        hienThi(sun1);
      }
      break;
    case 1://Che do 1
      pastHinh0 = millis();
      while (millis() - pastHinh0 < thresCloud){
        hienThi(cloud0);
      }

      pastHinh1 = millis();
      while(millis() - pastHinh1 < thresCloud){
        hienThi(cloud1);
      }

      pastHinh2 = millis();
      while(millis() - pastHinh2 < thresCloud){
        hienThi(cloud2);
      }

      pastHinh3 = millis();
      while(millis() - pastHinh3 < thresCloud+500){
        hienThi(cloud3);
      }
      break;
    case 2: //Che do 2
      pastHinh0 = millis();
      while (millis() - pastHinh0 < thresRain){
        hienThi(rain0);
      }

      pastHinh1 = millis();
      while(millis() - pastHinh1 < thresRain){
        hienThi(rain1);
      }

      pastHinh2 = millis();
      while(millis() - pastHinh2 < thresRain){
        hienThi(rain2);
      }

      pastHinh3 = millis();
      while(millis() - pastHinh3 < thresRain){
        hienThi(rain3);
      }
      break;
    case 3://Che do 3
      pastHinh0 = millis();
      while (millis() - pastHinh0 < thresWind+300){
        hienThi(wind0);
      }

      pastHinh1 = millis();
      while(millis() - pastHinh1 < thresWind+200){
        hienThi(wind1);
      }

      pastHinh2 = millis();
      while(millis() - pastHinh2 < thresWind){
        hienThi(wind2);
      }

      pastHinh3 = millis();
      while(millis() - pastHinh3 < thresWind){
        hienThi(wind3);
      }

      pastHinh4 = millis();
      while(millis() - pastHinh4 < thresWind+100){
        hienThi(wind4);
      }

      pastHinh5 = millis();
      while(millis() - pastHinh5 < thresWind+400){
        hienThi(wind5);
      }
      break;
  }
  
}

void hang(int8_t line){
  switch(line){
     case 0:
      digitalWrite(B, 0);
      digitalWrite(A, 0);
      digitalWrite(OE, 1);
      break;
     case 1:
      digitalWrite(B, 0);
      digitalWrite(A, 1);
      digitalWrite(OE, 1);
      break;
     case 2:
      digitalWrite(B, 1);
      digitalWrite(A, 0);
      digitalWrite(OE, 1);
      break;
     case 3:
      digitalWrite(B, 1);
      digitalWrite(A, 1);
      digitalWrite(OE, 1);
      break;
  }
}
void chuyen(unsigned char b){
  for(int8_t i = 0; i < 8; i++){
    digitalWrite(DS,b & (0x80>>i));      
    digitalWrite(CLK, 0);
    digitalWrite(CLK, 1);
  }
}
void hienThi(unsigned char arr[][4]) {
	for (unsigned char x = 1; x < 5; x++) {
		for (unsigned char a = 0; a < 4; a++)	{
			for (unsigned char b = 16; b > 0; b = b - 4) {
				chuyen(~arr[b - x][a]);  //Day 8 bit
        digitalWrite(SCLK, 0); //Xuat du lieu tu hc595 nay sang hc595 khac
			  digitalWrite(SCLK, 1);
			}
		}
		hang(4 - x);        //bat 4 hang LED
		delayMicroseconds(sang);
		digitalWrite(OE, 0);   //tat 4 hang LED
		delayMicroseconds(1000 - sang);
	}
}
int docNut(){
  if (digitalRead(SW0) != muc && digitalRead(SW1) != muc) //Doc tin hieu tu chan interrupt
    return 0;
  else if (digitalRead(SW0) != muc && digitalRead(SW1) == muc)
    return 1;
  else if (digitalRead(SW0) == muc && digitalRead(SW1) != muc)
    return 2;
  else return 3;
}
