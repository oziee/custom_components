#include "seplos_bms.h"
#include "esphome/core/log.h"
#include <vector>
#include "Crc16.h"

namespace esphome {
namespace seplos_bms {

static const char *const TAG = "seplos_bms";

static const uint8_t SEPLOS_FRAME_SIZE = 76; //0-75 76 bytes
static const uint8_t SEPLOS_START_BYTE = 0x55;
static const uint8_t SEPLOS_END_BYTE = 0xaa;

static const uint8_t SEPLOS_TEMPERATURE_OFFSET = 40;
static const uint16_t SEPLOS_CURRENT_OFFSET = 30000;

Crc16 crc;

bool Bin[] = {0,0,0,0,0,0,0,0};


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

void SeplosBmsComponent::convertDecToBin(int Dec, bool Bin[]) {
  for(int i = 7 ; i >= 0 ; i--) {
    if(pow(2, i)<=Dec) {
      Dec = Dec - pow(2, i);
      Bin[8-(i+1)] = 1;
    } else {
    }
  }
}

void SeplosBmsComponent::decode_data_(std::vector<uint8_t> data) {
  auto it = data.begin();

  while ((it = std::find(it, data.end(), SEPLOS_START_BYTE)) != data.end()) {
    if (data.end() - it >= SEPLOS_FRAME_SIZE && it[0] == SEPLOS_START_BYTE && it[1] == 0x46 && it[75] == SEPLOS_END_BYTE) {

      unsigned short value1 = (int)encode_uint16(it[73], it[74]);
      unsigned short value2 = crc.XModemCrc(data.data(),1,72);
      if (value1 == value2) {

        //Cell voltages
        float min_cell_voltage = 10000.0f;
        float max_cell_voltage = -0.0f;
        uint8_t min_voltage_cell = 0;
        uint8_t max_voltage_cell = 0;
        uint8_t looper = 0;
        
        //CELLS 8,72 
        float ivt[20];
        for (int i = 4; i < 35; i += 2) {
          float cell_voltage = (float) encode_uint16(it[i], it[i+1]);
          if (cell_voltage < min_cell_voltage) {
            min_cell_voltage = cell_voltage;
            min_voltage_cell = looper+1;
          }
          if (cell_voltage > max_cell_voltage) {
            max_cell_voltage = cell_voltage;
            max_voltage_cell = looper+1;
          }
          ivt[looper] = cell_voltage;
          ESP_LOGV("TAG", "Cells: %d is: %f", looper+1, cell_voltage);
          looper = looper + 1;
        }
          
          
        if (this->cell_1_voltage_) {
          this->cell_1_voltage_->publish_state((float) ivt[0]/ 1000);
        }
        if (this->cell_2_voltage_) {
          this->cell_2_voltage_->publish_state((float) ivt[1] / 1000);
        }
        if (this->cell_3_voltage_) {
          this->cell_3_voltage_->publish_state((float) ivt[2] / 1000);
        }
        if (this->cell_4_voltage_) {
          this->cell_4_voltage_->publish_state((float) ivt[3] / 1000);
        }
        if (this->cell_5_voltage_) {
          this->cell_5_voltage_->publish_state((float) ivt[4] / 1000);
        }
        if (this->cell_6_voltage_) {
          this->cell_6_voltage_->publish_state((float) ivt[5] / 1000);
        }
        if (this->cell_7_voltage_) {
          this->cell_7_voltage_->publish_state((float) ivt[6] / 1000);
        }
        if (this->cell_8_voltage_) {
          this->cell_8_voltage_->publish_state((float) ivt[7] / 1000);
        }
        if (this->cell_9_voltage_) {
          this->cell_9_voltage_->publish_state((float) ivt[8] / 1000);
        }
        if (this->cell_10_voltage_) {
          this->cell_10_voltage_->publish_state((float) ivt[9] / 1000);
        }
        if (this->cell_11_voltage_) {
          this->cell_11_voltage_->publish_state((float) ivt[10] / 1000);
        }
        if (this->cell_12_voltage_) {
          this->cell_12_voltage_->publish_state((float) ivt[11] / 1000);
        }
        if (this->cell_13_voltage_) {
          this->cell_13_voltage_->publish_state((float) ivt[12] / 1000);
        }
        if (this->cell_14_voltage_) {
          this->cell_14_voltage_->publish_state((float) ivt[13] / 1000);
        }
        if (this->cell_15_voltage_) {
          this->cell_15_voltage_->publish_state((float) ivt[14] / 1000);
        }
        if (this->cell_16_voltage_) {
          this->cell_16_voltage_->publish_state((float) ivt[15] / 1000);
        }
          
        if (this->max_cell_voltage_) {
          this->max_cell_voltage_->publish_state((float) max_cell_voltage / 1000);
        }
        if (this->max_cell_voltage_number_) {
          this->max_cell_voltage_number_->publish_state(max_voltage_cell);
        }
        if (this->min_cell_voltage_) {
          this->min_cell_voltage_->publish_state((float) min_cell_voltage / 1000);
        }
        if (this->min_cell_voltage_number_) {
          this->min_cell_voltage_number_->publish_state(min_voltage_cell);
        }
        
        ESP_LOGD("TAG", "CRCCHeck GOOD!!");
        if (this->status_text_sensor_ != nullptr) {
          convertDecToBin(it[62],Bin);
          if (Bin[7] == 1) {
            this->status_text_sensor_->publish_state("Discharging");
          }
          if (Bin[6] == 1) {
            this->status_text_sensor_->publish_state("Charging");
          }
          if (Bin[5] == 1) {
            this->status_text_sensor_->publish_state("Float Charge");
          }
          if (Bin[4] == 1) {
            this->status_text_sensor_->publish_state("Preserved bits");
          }
          if (Bin[3] == 1) {
            this->status_text_sensor_->publish_state("Standby");
          }
          if (Bin[2] == 1) {
            this->status_text_sensor_->publish_state("Poweed off");
          }
          if (Bin[1] == 1) {
            this->status_text_sensor_->publish_state("Preserved bits");
          }
          if (Bin[0] == 1) {
            this->status_text_sensor_->publish_state("Preserved bits");
          }
        }
          
      }
      else {
        ESP_LOGD("TAG", "CRCCHeck FAILED!!!");
      }


      break;
    } 
    else 
    {
      ESP_LOGD("TAG", "Data is not valid.. no 55 46 ..... 170");
      break;
    }
  }
}

}  // namespace seplos_bms
}  // namespace esphome
