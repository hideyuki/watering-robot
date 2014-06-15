/**
 * Title: Moiseture sensor data to serial #brhack
 * Author: Hideyuki Takei (hide@beatrobo.com)
 * Date: Jun. 14, 2014
 */
 
#define sampleCount 20;
#define sampleDelay 20;
#define moistureSensorPin 0;
#define temperatureSensorPin 1;
#define ledPin 13;
#define baudrate 57600;  // long
 
void setup(){
  // pin
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  // serial
  Serial.begin(baudrate);
}

// get analog value with avarage of some samples
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
  // read command
  char c = Serial.read();
  
  if(c=='m'){
    // Moisture sensor
    Serial.println(getAnalogValue(moistureSensorPin));  
  }
  else if(c=='t'){
    // Temperature sensor
    Serial.println(getAnalogValue(temperatureSensorPin));
  }
}
