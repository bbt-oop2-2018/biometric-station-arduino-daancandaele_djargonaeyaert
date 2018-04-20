//  VARIABLES
int pulsePin = 1;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
//temp
#include "SparkFunTMP102.h" 
#include <Wire.h> // Must include Wire library for I2C
#include <SparkFun_MMA8452Q.h> // Includes the SFE_MMA8452Q library

const int ALERT_PIN = A3;


TMP102 sensor0(0x48); 
MMA8452Q accel;

// these variables are volatile because they are used during the interrupt service routine!
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
  
}

void loop(){
  sendDataToProcessing('S', Signal);     // send Processing the raw Pulse Sensor data
  
        sendDataToProcessing('B',BPM);   // send heart rate with a 'B' prefix
        sendDataToProcessing('Q',IBI);   // send time between beats with a 'Q' prefix
        QS = false;                      // reset the Quantified Self flag for next time    
     
                           //  take a break
  float temperature;
  boolean alertPinState, alertRegisterState;

  sensor0.wakeup();
 
  temperature = sensor0.readTempC();

  sensor0.sleep();
  
  if (accel.available())
  {
    accel.read();
    printCalculatedAccels();
  }
  Serial.print("Temperature: ");
  Serial.println(temperature);
 
  delay(1000);  // Wait 1000ms
}


void sendDataToProcessing(char symbol, int data ){
    Serial.print(symbol);                // symbol prefix tells Processing what type of data is coming
    Serial.println(data);                // the data to send culminating in a carriage return
  }

void printCalculatedAccels()
{ 
  Serial.print(accel.cx, 3);
  Serial.print("\t");
  Serial.print(accel.cy, 3);
  Serial.print("\t");
  Serial.print(accel.cz, 3);
  Serial.println("\t");
}




