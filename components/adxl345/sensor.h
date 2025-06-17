#pragma once
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include <Adafruit_ADXL345_U.h>
#include <cmath>

namespace esphome {
namespace adxl345 {

class ADXL345VibrationSensor : public PollingComponent {
 public:
  sensor::Sensor *vibration_sensor = new sensor::Sensor();
  Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

  ADXL345VibrationSensor() : PollingComponent(500) {}

  void setup() override {
    Wire.begin();
    accel.begin();
    accel.setRange(ADXL345_RANGE_16_G);
  }

  void update() override {
    sensors_event_t event;
    accel.getEvent(&event);
    float vibration = sqrt(
      pow(event.acceleration.x, 2) +
      pow(event.acceleration.y, 2) +
      pow(event.acceleration.z, 2)
    );
    vibration_sensor->publish_state(vibration);
  }
};

}  // namespace adxl345
}  // namespace esphome
