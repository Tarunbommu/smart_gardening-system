#include <RTClib.h>
#include <Wire.h>
RTC_DS3231 rtc;
char t[32];
int soilsensorPin = A0; // select the input pin for LDR
int ldrsensorPin = 2; // select the input pin for LDR

int ldrsensorValue = 0; // variable to store the value coming from the sensor
int soilsensorValue=0;
String st1,st2;
void setup() {

pinMode(3, OUTPUT); // LDR output
pinMode(4, OUTPUT); // soil output
pinMode(5, OUTPUT); // RELAY MODLE
Wire.begin();
rtc.begin();
rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));  //rtc.adjust(DateTime(2019, 1, 21, 5, 0, 0));
digitalWrite(3,LOW);
digitalWrite(4,LOW);
digitalWrite(5,LOW);
Serial.begin(9600); //sets serial port for communication

}
void loop() {

DateTime now = rtc.now();
sprintf(t, "%02d:%02d:%02d %02d/%02d/%02d", now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());  
Serial.print(F("Date/Time: "));
Serial.println(t);
delay(1000);    
st1=String(String(now.hour())+":"+String(now.minute()));
Serial.println(st1);

soilsensorValue = analogRead(soilsensorPin); // read the value from the sensor
ldrsensorValue = digitalRead(ldrsensorPin); // read the value from the sensor
Serial.println(soilsensorValue); //prints the values coming from the sensor on the screen
Serial.println(ldrsensorValue); //prints the values coming from the sensor on the screen
if(ldrsensorValue==1)
{
digitalWrite(3, HIGH); // to connect with LED lights 
}
else{                     // wait for a second
digitalWrite(3, LOW);
}
//soil and rtc check

if(st1=="15:30"){

if(soilsensorValue<500)
{
  digitalWrite(4, LOW);   // turn the INDICATION LED OFF (LOW is the voltage level)                   
  digitalWrite(5, LOW);   // turn the MOTOR OFF (LOW is the voltage level)                   

}
  else{
  digitalWrite(4, HIGH);   // turn the LED  ON (HIGH is the voltage level)  
  digitalWrite(5, HIGH);   // turn the MOTOR ON (HIGH is the voltage level)                   
                 
  }
}
if(st1=="15:50"){
digitalWrite(4, LOW);   // turn the LED OFF (LOW is the voltage level)                   
digitalWrite(5, LOW);   // turn the MOTOR OFF (LOW is the voltage level)                   

}
delay(100);

}
