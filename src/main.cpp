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
#include <app/analog_sensor_reporter_llm.h>
#include <infrastructure/hal/VoltageSensor_ADC.h>


infrastructure::VoltageSensor_ADC voltageSensor(A0);
app::VoltageSensorReporter voltageSensorReporter(voltageSensor);
app::VoltageSensorReporterLlp voltageSensorReporterLlp(voltageSensor);

bool output_llm = false;
long timer = millis();

void setup() {
  pinMode(A1, INPUT);
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
}

void loop() {
  if (digitalRead(A1) == HIGH) {
    output_llm = true;
  } else {
    output_llm = false;
  }
  if (millis() - timer > 1000) {
    if (output_llm) {
      voltageSensorReporterLlp.report(Serial);
    } else {
      voltageSensorReporter.report(Serial);
    }
    timer = millis();
  }
}

