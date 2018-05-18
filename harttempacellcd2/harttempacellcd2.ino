//  VARIABLES
int pulsePin = 1;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
//temp
#include "SparkFunTMP102.h" 
#include <Wire.h> // Must include Wire library for I2C
#include <SparkFun_MMA8452Q.h> // Includes the SFE_MMA8452Q library
#include <LiquidCrystal.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const int ALERT_PIN = A3;


TMP102 sensor0(0x48); 
MMA8452Q accel;

volatile int BPM;                   // used to hold the pulse rate
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // holds the time between beats, the Inter-Beat Interval
volatile boolean Pulse = false;     // true when pulse wave is high, false when it's low
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.


void setup(){
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  Serial.begin(115200);             // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 
  analogReference(EXTERNAL);   
//temp
  pinMode(ALERT_PIN,INPUT);  
  sensor0.begin();  
// accel
  accel.init();
//lcd
lcd.begin(16, 2);
  
}

void loop(){
  QS = false;        
  float temperature;
  boolean alertPinState, alertRegisterState;

  sensor0.wakeup();
 
  temperature = sensor0.readTempC();

  sensor0.sleep();
  
  if (accel.available())
  {
    accel.read();
  }
  
delay(1000);
/*
   lcd.clear();
   lcd.print("T: ");
   lcd.print(temperature);
   
   lcd.print(" HB: ");
   lcd.print(BPM);
   lcd.print(" BPM");
   lcd.setCursor(0,1);
   lcd.print("X");
   lcd.print(accel.cx);
   lcd.print("Y");
   lcd.print(accel.cy);
   lcd.print("Z");
   lcd.print(accel.cz);
*/
int i = 1;
if (i=1){
   lcd.clear();
   lcd.print("Temp: ");
   lcd.print(temperature);
   lcd.print(" C");
   lcd.setCursor(0,1);
   lcd.print("Heart: ");
   lcd.print(BPM);
   lcd.print(" BPM");
   i++;
}
  delay(2000); 
if (i=2){
   lcd.clear();
   lcd.print("X: ");
   lcd.print(accel.cx);
   lcd.print(" Y:");
   lcd.print(accel.cy);
   lcd.setCursor(0,1);
   lcd.print("Z: ");
   lcd.print(accel.cz);
  i--;
}  
   Serial.print(String("[") + temperature + 
   String("|") + BPM + String(",") +
   accel.cx + String(";") + accel.cy + 
   String(":") + accel.cz + String("]"));
}




