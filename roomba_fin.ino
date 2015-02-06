//Joshua Collins 
// I have declared byte 0x00 as byte j beacues if not defined as a specific type the compile will reject it as being not defined - Joshua Collins  

#include <SoftwareSerial.h>

SoftwareSerial roomba(5,3);  // RX,TX
int rxPin = 5;
int txPin = 3;
int ddPin = 7;
int ledPin = 13;
int sonar = A0;

double dist=0;


void setup() {
//  pinMode(txPin,  OUTPUT);
  pinMode(ddPin,  OUTPUT);   // sets the pins as output
  pinMode(ledPin, OUTPUT);   // sets the pins as output
  Serial.begin(57600);
  roomba.begin(57600);

  digitalWrite(ledPin, HIGH); // say we're alive

  // wake up the robot
  digitalWrite(ddPin, HIGH);
  delay(100);
  digitalWrite(ddPin, LOW);
  delay(500);
  digitalWrite(ddPin, HIGH);
  delay(2000);
  // set up ROI to receive commands  
  roomba.write(128);  // START as defined in manual(adim) 
  delay(50);
  roomba.write(130);  // CONTROL adim
  delay(50);
  digitalWrite(ledPin, LOW);  
}

void loop() {

  
  dist=(analogRead(sonar)*.54);
  
 
//Serial.println(dist);
 
if((dist)>10){

   goForward();
   delay(50);
   halt();  

}

if((dist)<=10){
  goBackward();  
  delay(50);
  halt();
  //spinLeft();
}

}

void goForward() {
  
  byte j = 0x00;
  
  
  roomba.write(137);   // DRIVE
  roomba.write(j);   // 0x00c8 == 200
  roomba.write(0xc8);
  roomba.write(0x80);
  roomba.write(j);
}

void halt(){
    
  byte j = 0x00;
  
  
  roomba.write(137);   
  roomba.write(j);   
  roomba.write(j);
  roomba.write(j);
  roomba.write(j);
  
}


void goBackward() {
  byte j = 0x00;
  
  roomba.write(137);   // DRIVE
  roomba.write(0xff);   // 0xff38 == -200
  roomba.write(0x38);
  roomba.write(0x80);
  roomba.write(j);
}
void spinLeft() {
  byte j = 0x00;

  
  roomba.print(137);   // DRIVE
  roomba.print(j);   // 0x00c8 == 200
  roomba.print(0xc8);
  roomba.print(j);
  roomba.print(0x01);   // 0x0001 == spin left
}
void spinRight() {
  byte j = 0x00;
  

  roomba.print(137);   // DRIVE
  roomba.print(j);   // 0x00c8 == 200
  roomba.print(0xc8);
  roomba.print(0xff);
  roomba.print(0xff);   // 0xffff == -1 == spin right
}




   
