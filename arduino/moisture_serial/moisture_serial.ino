/**
 * Title: Moiseture sensor data to serial #brhack
 * Author: Hideyuki Takei (hide@beatrobo.com)
 * Date: Jun. 14, 2014
 */

#include "DHT/DHT.h"

#define SAMPLE_COUNT 20;
#define SAMPLE_DELAY 20;
#define MOISTURE_SENSOR_PIN 0;
#define TEMPERATURE_SENSOR_PIN 1;
#define LED_PIN 13;
#define DHT_PIN 2;
#define BAUDRATE 57600;  // long
#define DHT_TYPE DHT11   // for DHT lib

// variables
DHT dht(DHT_PIN, DHT_TYPE);

void setup(){
  // pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  
  // serial
  Serial.begin(BAUDRATE);
  
  // HDHT
  dht.begin();
}

// get analog value with avarage of some samples
int getAnalogValue(int pin){
  long val = 0;
  
  for(int i=0; i<SAMPLE_COUNT; i++){
    val += analogRead(pin);
    delay(SAMPLE_DELAY);
  }
  val /= SAMPLE_COUNT;
  
  return val;
}

void loop(){
  // read command
  char c = Serial.read();
  
  if(c=='m'){
    // Moisture sensor
    Serial.println(getAnalogValue(MOISTURE_SENSOR_PIN));  
  }
  else if(c=='t'){
    // Temperature sensor
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" *C");
    //Serial.println(getAnalogValue(TEMPERATURE_SENSOR_PIN));
  }
}
