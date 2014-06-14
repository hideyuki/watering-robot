/**
 * Title: Moiseture sensor data to serial #brhack
 * Author: Hideyuki Takei (hide@beatrobo.com)
 * Date: Jun. 14, 2014
 */
 
void setup(){
  Serial.begin(57600);
}

void loop(){
  Serial.print("Moisture Sensor Value:");
  Serial.println(analogRead(0));  
  delay(500);
}
