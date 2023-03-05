#include "seplos_bms.h"
#include "esphome/core/log.h"
#include <vector>

namespace esphome {
namespace seplos_bms {

static const char *const TAG = "seplos_bms";

static const uint8_t SEPLOS_FRAME_SIZE = 76; //13
static const uint8_t SEPLOS_TEMPERATURE_OFFSET = 40;
static const uint16_t SEPLOS_CURRENT_OFFSET = 30000;

static const uint8_t SEPLOS_START_BYTE = 0x55;
static const uint8_t SEPLOS_REQUEST_MIN_MAX_VOLTAGE = 0x91;
// static const uint8_t SEPLOS_REQUEST_MIN_MAX_TEMPERATURE = 0x92;
// static const uint8_t SEPLOS_REQUEST_MOS = 0x93;
// static const uint8_t SEPLOS_REQUEST_STATUS = 0x94;
// static const uint8_t SEPLOS_REQUEST_CELL_VOLTAGE = 0x95;
// static const uint8_t SEPLOS_REQUEST_TEMPERATURE = 0x96;

void SeplosBmsComponent::setup() {}

void SeplosBmsComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Seplos BMS:");
  this->check_uart_settings(9600);
}

void SeplosBmsComponent::update() {
  // this->request_data_(SEPLOS_REQUEST_BATTERY_LEVEL);
  // this->request_data_(SEPLOS_REQUEST_MIN_MAX_VOLTAGE);
  // this->request_data_(SEPLOS_REQUEST_MIN_MAX_TEMPERATURE);
  // this->request_data_(SEPLOS_REQUEST_MOS);
  // this->request_data_(SEPLOS_REQUEST_STATUS);
  // this->request_data_(SEPLOS_REQUEST_CELL_VOLTAGE);
  // this->request_data_(SEPLOS_REQUEST_TEMPERATURE);

  std::vector<uint8_t> get_seplos_data;
  int available_data = this->available();
  ESP_LOGW(TAG, "reading avalible size: %d", available_data);
  if (available_data >= SEPLOS_FRAME_SIZE) {
    get_seplos_data.resize(available_data);
    this->read_array(get_seplos_data.data(), available_data);
    this->decode_data_(get_seplos_data);
  }

}

float SeplosBmsComponent::get_setup_priority() const { return setup_priority::DATA; }

// void SeplosBmsComponent::request_data_(uint8_t data_id) {
//   uint8_t request_message[SEPLOS_FRAME_SIZE];

//   request_message[0] = 0x55;     // Start Flag
//   request_message[1] = addr_;    // Communication Module Address
//   request_message[2] = data_id;  // Data ID
//   request_message[3] = 0x08;     // Data Length (Fixed)
//   request_message[4] = 0x00;     // Empty Data
//   request_message[5] = 0x00;     //     |
//   request_message[6] = 0x00;     //     |
//   request_message[7] = 0x00;     //     |
//   request_message[8] = 0x00;     //     |
//   request_message[9] = 0x00;     //     |
//   request_message[10] = 0x00;    //     |
//   request_message[11] = 0x00;    // Empty Data
//   request_message[12] = (uint8_t)(request_message[0] + request_message[1] + request_message[2] +
//                                   request_message[3]);  // Checksum (Lower byte of the other bytes sum)

//   this->write_array(request_message, sizeof(request_message));
//   this->flush();
// }

void SeplosBmsComponent::decode_data_(std::vector<uint8_t> data) {
  auto it = data.begin();

  ESP_LOGD("TAG", "decoding data");

  //while ((it = std::find(it, data.end(), 0xA5)) != data.end()) { //0xA5 i belive to to start byte
  while ((it = std::find(it, data.end(), SEPLOS_START_BYTE)) != data.end()) {
    for(i = 0; i < LIMIT - 76; i++)
    {
      ESP_LOGD("TAG", "it %d: %d",i,it[i]);
    } 

    if (data.end() - it >= SEPLOS_FRAME_SIZE && it[1] == 0x46 && it[76] == 0xaa) { //end byte?
      ESP_LOGD("TAG", "advance 1");
      std::advance(it, SEPLOS_FRAME_SIZE);
    } else {
      ESP_LOGD("TAG", "advance 2");
      std::advance(it, 1);
    }
  }

  

  ESP_LOGD("TAG", "end of decode data");
}

}  // namespace seplos_bms
}  // namespace esphome
