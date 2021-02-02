#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM900
SoftwareSerial mySerial(7, 8); //SIM900 Tx & Rx is connected to Arduino #7 & #8
const int buzzerPin = 12;
const int flamePin = 11;
int Flame = HIGH;
int redled = 5;
int greenled = 6;
int incomingByte = 0; // for incoming serial data
void setup() 
{
  pinMode(buzzerPin, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);

  pinMode(flamePin, INPUT);
  Serial.begin(19200); 
  mySerial.begin(19200);
  delay(1000); 
}

void loop() 
{

   if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
  
  Flame = digitalRead(flamePin);
  if (Flame== LOW)
  {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(redled, HIGH);
    digitalWrite(greenled, LOW);
    sendSMS();    
  }
  else
  {

    digitalWrite(buzzerPin, LOW);
    digitalWrite(greenled, HIGH);
    digitalWrite(redled, LOW);
  }
}


void sendSMS(){
  mySerial.println("AT"); //Handshaking with SIM900
  delay(200);
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  delay(200);
  mySerial.println("AT+CMGS=\"+8801722592693\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  delay(200);
  mySerial.print("Firing House"); //text content
  delay(200);
  mySerial.write(26);
 }
