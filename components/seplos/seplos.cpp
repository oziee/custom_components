#include "seplos.h"
#include "esphome/core/log.h"

namespace esphome {
namespace seplos {

static const char *TAG = "seplos";

void SeplosComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Seplos:");
  LOG_TEXT_SENSOR("  ", "Charger Text", charger_text_sensor_);
  check_uart_settings(9600);
}

void SeplosComponent::loop() {
  const uint32_t now = millis();
  if ((state_ > 0) && (now - last_transmission_ >= 200)) {
    // last transmission too long ago. Reset RX index.
    ESP_LOGW(TAG, "Last transmission too long ago.");
    state_ = 0;
  }

  if (!available())
    return;

  last_transmission_ = now;
  while (available()) {
    uint8_t c;
    read_byte(&c);
    if (state_ == 0) {
      if ((c == '\r') || (c == '\n'))
        continue;
      label_.clear();
      value_.clear();
      state_ = 1;
    }
    if (state_ == 1) {
      if (c == '\t')
        state_ = 2;
      else
        label_.push_back(c);
      continue;
    }
    if (state_ == 2) {
      if (label_ == "Checksum") {
        state_ = 0;
        continue;
      }
      if ((c == '\r') || (c == '\n')) {
        handle_value_();
        state_ = 0;
      } else {
        value_.push_back(c);
      }
    }
  }
}



void SeplosComponent::handle_value_() {
  int value;
  value = atoi(value_.c_str());

  if (charger_text_sensor_ != nullptr)
    charger_text_sensor_->publish_state("greg");

}

}  // namespace seplos
}  // namespace esphome