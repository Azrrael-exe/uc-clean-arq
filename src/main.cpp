#include <Arduino.h>
#include <domain/voltage.h>
#include <infrastructure/hal/VoltageSensor_ADC.h>

infrastructure::VoltageSensor_ADC sensor(A0);

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0, INPUT);
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  Serial.println("Hello, PlatformIO!");
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  
  Serial.println("LED blink cycle completed");

  sensor.read();
  Serial.println(sensor.getRead().volts());
}

