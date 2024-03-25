#include <RTClib.h>
#include <Wire.h>
RTC_DS3231 rtc;
char t[32];
int soilsensorPin = A0; // select the input pin for Soil
int ldrsensorPin = 2;
int ldrsensorValue = 0;
int soilsensorValue=0;
String st1;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(3, OUTPUT); // LDR output 3
digitalWrite(3,LOW);
pinMode(4, OUTPUT); // soil output 4
digitalWrite(4,LOW);
pinMode(5, OUTPUT); // RELAY output 5
digitalWrite(5,LOW);
Wire.begin();
rtc.begin();
rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));// RTC adjust
}

void loop() {
  // put your main code here, to run repeatedly:
DateTime now = rtc.now();
sprintf(t, "%02d:%02d:%02d %02d/%02d/%02d", now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());  
Serial.print(F("Date/Time: "));
Serial.println(t);
delay(1000);    
st1=String(String(now.hour())+":"+String(now.minute()));
Serial.println(st1);

ldrsensorValue = digitalRead(ldrsensorPin); // read the value from the LDR sensor
soilsensorValue = analogRead(soilsensorPin); // read the value from the soil sensor
Serial.println(ldrsensorValue); //prints the values coming from the sensor on the screen
if(ldrsensorValue==1)
{
digitalWrite(3, HIGH); // to connect with LED lights 6
Serial.println("Lights ON");
}
else{                     // wait for a second
digitalWrite(3, LOW);  //6
Serial.println("Lights OFF");
}

//soil and rtc check

if(st1=="11:53"){

if(soilsensorValue<500)
{
  digitalWrite(4, LOW);  // turn the LED on (HIGH is the voltage level)  
  digitalWrite(5, LOW);   // signal for relay                  
  Serial.println("Motor OFF");
}
  else{
  digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)   
  digitalWrite(5, HIGH);   // signal for relay                  
  Serial.println("Motor ON");
  }
}
if(st1=="11:56"){
digitalWrite(4, LOW);   // turn the LED on (HIGH is the voltage level)
digitalWrite(5, LOW);   // signal for relay                   
}
delay(100);

}
