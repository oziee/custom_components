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

void SeplosComponent::setup() {
  startMillis = millis();
}

void SeplosComponent::loop() {
  currentMillis = millis();


  if (currentMillis - startMillis >= period)  //test whether the period has elapsed
  {
    ESP_LOGW(TAG, "transmission availabe.");
    if(available() > 1){
      fetchSerial();
    }
    startMillis = currentMillis;
  }
    

}

void SeplosComponent::fetchSerial(){
  int bytes_read = 0 ;
  bool be = false;
  uint8_t buffer[76];
  char tmp[16];

  while (bytes_read < 76)
  {
    if (available() > 0)
    {
      uint8_t RXX = read();
      //wait for the starting byte to come in which is \xUFF (x55 x46 x46)
      if(RXX == 0x55) {
        be = true;
      }
      if (be==true) {
        buffer[bytes_read] = RXX;
        sprintf(tmp, "%.2X",buffer[bytes_read]);
        value_ = value_ + tmp;
        bytes_read ++;
      }
    }
  }
  handle_value_();
}

void SeplosComponent::handle_value_() {
  // int value;
  // value = atoi(value_.c_str());

  if (charger_text_sensor_ != nullptr)
    charger_text_sensor_->publish_state(value_.c_str());

}

}  // namespace seplos
}  // namespace esphome