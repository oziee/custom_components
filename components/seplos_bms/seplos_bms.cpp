#include "seplos_bms.h"
#include "esphome/core/log.h"
#include <vector>
#include "Crc16.h"

namespace esphome {
namespace seplos_bms {

static const char *const TAG = "seplos_bms";

static const uint8_t SEPLOS_FRAME_SIZE = 76; 0-75 76 bytes
static const uint8_t SEPLOS_START_BYTE = 0x55;
static const uint8_t SEPLOS_END_BYTE = 0xaa;

static const uint8_t SEPLOS_TEMPERATURE_OFFSET = 40;
static const uint16_t SEPLOS_CURRENT_OFFSET = 30000;


// static const uint8_t SEPLOS_REQUEST_MIN_MAX_VOLTAGE = 0x91;
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

  // int bytes_read = 0 ;
  // bool be = false;
  // uint8_t buffer[76];
  // char tmp[16];

  // ESP_LOGW(TAG, "fetching data.");

  // value_.clear();

  // while (bytes_read < 76)
  // {
  //   if (available() > 0)
  //   {
  //     ESP_LOGW(TAG, "reading data.");
  //     uint8_t RXX = read();
  //     //wait for the starting byte to come in which is \xUFF (x55 x46 x46)
  //     if(RXX == 0x55) {
  //       be = true;
  //     }
  //     if (be==true) {
  //       buffer[bytes_read] = RXX;
  //       sprintf(tmp, "%.2X",buffer[bytes_read]);
  //       value_ = value_ + tmp;
  //       bytes_read ++;
  //     }
  //   }
  // }

  // get_seplos_data.push_back(0x01);
  // auto it = get_seplos_data.begin();
  // it = get_seplos_data.insert(it, 0x20);

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

void SeplosBmsComponent::decode_data_(std::vector<uint8_t> data) {
  auto it = data.begin();

  ESP_LOGD("TAG", "decoding data");


  while ((it = std::find(it, data.end(), SEPLOS_START_BYTE)) != data.end()) {
    if (data.end() - it >= SEPLOS_FRAME_SIZE && it[0] == SEPLOS_START_BYTE && it[1] == 0x46 && it[75] == SEPLOS_END_BYTE) {
      ESP_LOGD("TAG", "advance 1");
      ESP_LOGD("TAG", "CRC %f", (float)encode_uint16(it[73], it[74]));

      //std::advance(it, SEPLOS_FRAME_SIZE);
      break;
    } else {
      ESP_LOGD("TAG", "Data is not valid with 55 46 ..... 170");
      break;
    }
  }
}

}  // namespace seplos_bms
}  // namespace esphome
