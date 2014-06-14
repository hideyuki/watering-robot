/**
 * Title: Moiseture sensor data to serial #brhack
 * Author: Hideyuki Takei (hide@beatrobo.com)
 * Date: Jun. 14, 2014
 */
 
void setup(){
  Serial.begin(57600);
}

void loop(){
  char c = Serial.read();
  
  if(c=='m'){
    // Moisture sensor
    Serial.println(analogRead(0));  
  }
  else if(c=='t'){
    // Temperature sensor
    Serial.println(analogRead(1));
  }
}
