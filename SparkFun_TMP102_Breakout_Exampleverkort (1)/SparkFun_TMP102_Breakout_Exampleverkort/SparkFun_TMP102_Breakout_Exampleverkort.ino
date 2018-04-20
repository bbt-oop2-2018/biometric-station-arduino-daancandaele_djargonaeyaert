
#include "SparkFunTMP102.h" 

const int ALERT_PIN = A3;

TMP102 sensor0(0x48); 


void setup() {
  Serial.begin(115200); 
  pinMode(ALERT_PIN,INPUT);  
  sensor0.begin();  
  
  sensor0.setFault(0);  // Trigger alarm immediately
  
  sensor0.setConversionRate(2);
 
  sensor0.setExtendedMode(0);
}
 
void loop()
{
  float temperature;
  boolean alertPinState, alertRegisterState;

  sensor0.wakeup();
 
  temperature = sensor0.readTempC();

  sensor0.sleep();

  Serial.print("Temperature: ");
  Serial.println(temperature);
 
  delay(1000);  // Wait 1000ms
}
