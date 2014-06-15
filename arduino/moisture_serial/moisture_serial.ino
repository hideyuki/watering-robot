/**
 * Title: Moiseture sensor data to serial #brhack
 * Author: Hideyuki Takei (hide@beatrobo.com)
 * Date: Jun. 14, 2014
 */
 
const int sampleCount = 20;
const int sampleDelay = 20;
const int pinMoistureSensor = 0;
const int pinTemperatureSensor = 1;
const long baudrate = 57600;
 
void setup(){
  Serial.begin(baudrate);
}

int getAnalogValue(int pin){
  long val = 0;
  
  for(int i=0; i<sampleCount; i++){
    val += analogRead(pin);
    delay(sampleDelay);
  }
  val /= sampleCount;
  
  return val;
}

void loop(){
  char c = Serial.read();
  
  if(c=='m'){
    // Moisture sensor
    Serial.println(getAnalogValue(pinMoistureSensor));  
  }
  else if(c=='t'){
    // Temperature sensor
    Serial.println(getAnalogValue(pinTemperatureSensor));
  }
}
