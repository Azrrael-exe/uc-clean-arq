#include <Arduino.h>
#include <domain/temperature.h>
#include <infrastructure/hal/TemperatureSensor_Dummy.h>
#include <infrastructure/LM35_Sensor.h>
#include <app/alarm_use_case.h>

infrastructure::TemperatureSensor_Dummy dummySensor(25.0, 30.0);
infrastructure::LM35_Sensor lm35Sensor(A0);


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
}

void loop() {
  app::AlarmUseCase<domain::Temperature> alarm_use_case(app::AlarmConfig<domain::Temperature>(domain::Temperature(25.0), domain::Temperature(30.0)), lm35Sensor);
  app::AlarmState alarm_state = alarm_use_case.execute();
  if (alarm_state == app::AlarmState::LOW) {
    Serial.println("Low temperature");
  } else if (alarm_state == app::AlarmState::HIGH) {
    Serial.println("High temperature");
  } else {
    Serial.println("Normal temperature");
  }
  delay(1000);
}

