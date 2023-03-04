#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace seplos {

class SeplosComponent : public uart::UARTDevice, public Component {
 public:
  void set_charger_text_sensor(text_sensor::TextSensor *charger_text_sensor) { charger_text_sensor_ = charger_text_sensor; }
  
  void dump_config() override;
  void loop() override;

  float get_setup_priority() const { return setup_priority::DATA; }

 protected:
  void handle_value_();

  text_sensor::TextSensor *charger_text_sensor_{nullptr};


  int state_{0};
  std::string label_;
  std::string value_;
  uint32_t last_transmission_{0};
};

}  // namespace seplos
}  // namespace esphome