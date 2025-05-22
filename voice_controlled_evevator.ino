#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"
#include <Stepper.h>

#include <LiquidCrystal_I2C.h>
  // set the LCD address to 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,16,2);

const int stepsPerRevolution = 800;


VR myVR(10,11);    // 2:RX 3:TX, you can choose your favourite pins.
uint8_t records[7]; // save record
uint8_t buf[64];
Stepper myStepper = Stepper(stepsPerRevolution, 6, 7, 8, 9);


#define groundfloor    (0)
#define floor1   (1)
#define floor2   (2) 
#define floor3   (3)  


int pos;

void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}

/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf  -->  VR module return value when voice is recognized.
             buf[0]  -->  Group mode(FF: None Group, 0x8n: User, 0x0n:System
             buf[1]  -->  number of record which is recognized. 
             buf[2]  -->  Recognizer index(position) value of the recognized record.
             buf[3]  -->  Signature length
             buf[4]~buf[n] --> Signature
*/
void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}
void upstep(int z)
{ int a=0;
a=z*2;
   for(int y=0;y<a;y++){
    Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);
}
}
void downstep(int v)
{int b=0;
b=v*2;
   for(int w=0;w<b;w++){
    Serial.println("anticlockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);
  
}
}
 
void setup(){
  lcd.init();
   lcd.clear();         
   lcd.backlight(); 
   //lcd.setCursor(2,0); 
  
  
  
  /** initialize */
  pos =0;
  myVR.begin(9600);
   // Set the speed to 5 rpm:
  myStepper.setSpeed(20);
  
  // Begin Serial communication at a baud rate of 9600:
  Serial.begin(9600);
  Serial.println("Elechouse Voice Recognition V3 Module\r\nControl LED sample");
  
  //pinMode(led, OUTPUT);
    
  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }
  
  if(myVR.load((uint8_t)groundfloor) >= 0){
    Serial.println("groundfloor loaded");
  }
  
  if(myVR.load((uint8_t)floor1) >= 0){
    Serial.println("floor1 loaded");
  }
    if(myVR.load((uint8_t)floor2) >= 0){
    Serial.println("floor2 loaded");
  }
  
  if(myVR.load((uint8_t)floor3) >= 0){
    Serial.println("floor3 loaded");
  }
}


void loop(){

  int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0){
    switch(buf[1]){
      case groundfloor:
      if(pos==1)
      {
        downstep(1);
      }
      if(pos==2)
      {
        downstep(2);
      }
      if(pos==3)
      {
        downstep(3);
      } 
      delay(500);
     pos=0;
     lcd.clear();
     lcd.print("GROUND FLOOR");
        break;
        
      case floor1:
       if(pos==0)
      {
        upstep(1);
      }
      if(pos==2)
      {
        downstep(1);
      }
      if(pos==3)
      {
        downstep(2);
      }
      delay(500);
      lcd.clear();
     pos=1;
     lcd.print("FLOOR 1");
        break;
        
        case floor2:
      if(pos==0)
      {
       upstep(2);
      }
      if(pos==1)
      {
        upstep(1);
      }
      if(pos==3)
      {
        downstep(1);
      }
      delay(500); 
     pos=2;
     lcd.clear();
     lcd.print("FLOOR 2");
        break;

        case floor3:
            if(pos==0)
      {
       upstep(3);
      }
      if(pos==1)
      {
        upstep(2);
      }
      if(pos==2)
      {
       upstep(1);
      }
      delay(500);
     lcd.clear(); 
     pos=3;
     lcd.print("FLOOR 3");
        break;
        
      default:
        Serial.println("Record function undefined");
        break;
    }
    /** voice recognized */
    printVR(buf);
  }
}

