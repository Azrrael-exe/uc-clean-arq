#include <Arduino.h>
#include <domain/temperature.h>
#include <infrastructure/hal/TemperatureSensor_Dummy.h>
#include <infrastructure/hal/LM35_Sensor.h>
#include <app/alarm_use_case.h>
#include <infrastructure/hal/ServoMotor.h>
#include <infrastructure/hal/LinearActuatorFromMotor.h>
#include <infrastructure/hal/LimitSwitchSensor.h>
#include <app/catersian_move.h>
#include <app/analog_sensor_reporter.h>
#include <infrastructure/hal/VoltageSensor_ADC.h>

infrastructure::VoltageSensor_ADC voltageSensor(A0);
app::VoltageSensorReporter voltageSensorReporter(voltageSensor);


void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
}

void loop() {
  voltageSensorReporter.report(Serial);
  delay(1000);
}

