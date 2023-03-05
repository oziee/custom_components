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

void resetBin() {
  for (int z=0; z<8; z++) {
    Bin[z]=0;
  }
}

void SeplosBmsComponent::decode_data_(std::vector<uint8_t> data) {
  auto it = data.begin();

  while ((it = std::find(it, data.end(), SEPLOS_START_BYTE)) != data.end()) {
    if (data.end() - it >= SEPLOS_FRAME_SIZE && it[0] == SEPLOS_START_BYTE && it[1] == 0x46 && it[75] == SEPLOS_END_BYTE) {
      
      unsigned short value1 = (int)encode_uint16(it[73], it[74]);
      unsigned short value2 = crc.XModemCrc(data.data(),1,72);
      if (value1 == value2) {
        //CRC ALL GOOD!!
        ESP_LOGD("TAG", "CRCCHeck GOOD!!");

        //NUMBER OF CELLS IN THE PACK
        if (this->cells_number_) {
          this->cells_number_->publish_state(it[3]);
        }

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
          ivt[looper] = cell_voltage / 1000;
          ESP_LOGV("TAG", "Cells: %d is: %f", looper+1, cell_voltage);
          looper = looper + 1;
        }
          
          
        if (this->cell_01_voltage_) {
          this->cell_01_voltage_->publish_state((float) ivt[0]);
        }
        if (this->cell_02_voltage_) {
          this->cell_02_voltage_->publish_state((float) ivt[1]);
        }
        if (this->cell_03_voltage_) {
          this->cell_03_voltage_->publish_state((float) ivt[2]);
        }
        if (this->cell_04_voltage_) {
          this->cell_04_voltage_->publish_state((float) ivt[3]);
        }
        if (this->cell_05_voltage_) {
          this->cell_05_voltage_->publish_state((float) ivt[4]);
        }
        if (this->cell_06_voltage_) {
          this->cell_06_voltage_->publish_state((float) ivt[5]);
        }
        if (this->cell_07_voltage_) {
          this->cell_07_voltage_->publish_state((float) ivt[6]);
        }
        if (this->cell_08_voltage_) {
          this->cell_08_voltage_->publish_state((float) ivt[7]);
        }
        if (this->cell_09_voltage_) {
          this->cell_09_voltage_->publish_state((float) ivt[8]);
        }
        if (this->cell_10_voltage_) {
          this->cell_10_voltage_->publish_state((float) ivt[9]);
        }
        if (this->cell_11_voltage_) {
          this->cell_11_voltage_->publish_state((float) ivt[10]);
        }
        if (this->cell_12_voltage_) {
          this->cell_12_voltage_->publish_state((float) ivt[11]);
        }
        if (this->cell_13_voltage_) {
          this->cell_13_voltage_->publish_state((float) ivt[12]);
        }
        if (this->cell_14_voltage_) {
          this->cell_14_voltage_->publish_state((float) ivt[13]);
        }
        if (this->cell_15_voltage_) {
          this->cell_15_voltage_->publish_state((float) ivt[14]);
        }
        if (this->cell_16_voltage_) {
          this->cell_16_voltage_->publish_state((float) ivt[15]);
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

        if (this->cell_deviation_) {
          this->cell_deviation_->publish_state((float) (max_cell_voltage-min_cell_voltage) / 1000);
        }

        //temps
        if (this->temperature_1_sensor_) { 
          this->temperature_1_sensor_->publish_state((float) (encode_uint16(it[37], it[38]) - 2731) / 10);
        }
        if (this->temperature_2_sensor_) { 
          this->temperature_2_sensor_->publish_state((float) (encode_uint16(it[39], it[40]) - 2731) / 10);
        }
        if (this->temperature_3_sensor_) { 
          this->temperature_3_sensor_->publish_state((float) (encode_uint16(it[41], it[42]) - 2731) / 10);
        }
        if (this->temperature_4_sensor_) { 
          this->temperature_4_sensor_->publish_state((float) (encode_uint16(it[43], it[44]) - 2731) / 10);
        }
        if (this->temperature_amb_sensor_) { 
          this->temperature_amb_sensor_->publish_state((float) (encode_uint16(it[45], it[46]) - 2731) / 10);
        }
        if (this->temperature_bms_sensor_) { 
          this->temperature_bms_sensor_->publish_state((float) (encode_uint16(it[47], it[48]) - 2731) / 10);
        }

        //current
        if (this->current_sensor_) { 
          this->current_sensor_->publish_state((float) encode_uint16(it[49], it[50])  / 10);
        }

        //total volt of pack
        if (this->voltage_sensor_) { 
          this->voltage_sensor_->publish_state((float) encode_uint16(it[51], it[52])  / 100);
        }

         //remaining pack capacity
        float rc = (float) encode_uint16(it[53], it[54])  / 100;
        if (this->remaining_capacity_) { 
          this->remaining_capacity_->publish_state(rc);
        }

        //total pack capacity
        float tc = (float) encode_uint16(it[56], it[57])  / 100;
        if (this->pack_capacity_) { 
          this->pack_capacity_->publish_state(tc);
        }

        // pack SOC
        if (this->battery_level_sensor_) { 
          this->battery_level_sensor_->publish_state((rc*100)/tc);
        }

        // pack charge cycle counter
        if (this->cycle_counter_) { 
          this->cycle_counter_->publish_state((float) encode_uint16(it[58], it[59]));
        }

        

        resetBin();
        //current operation of the unit.. charging, discharging.. nothing, off etc
        ESP_LOGD("TAG", "Status dec: %d", it[62]);
        if (this->status_text_sensor_ != nullptr) {
          convertDecToBin(it[62],Bin);
          for (int z=0; z<8; z++) {
            ESP_LOGD("TAG", "Status Bin: %d - %d", z, Bin[z]);
          }
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

        //system status switches
        resetBin();
        convertDecToBin(it[63],Bin);
        //discharging enabled
        if (Bin[7] == 1) {
          if (this->discharging_mos_enabled_ != nullptr) 
            this->discharging_mos_enabled_->publish_state(1);
        }
        else
        {
          if (this->discharging_mos_enabled_ != nullptr) 
            this->discharging_mos_enabled_->publish_state(0);
        }
        //charging enabled
        if (Bin[6] == 1) {
          if (this->charging_mos_enabled_ != nullptr) 
            this->charging_mos_enabled_->publish_state(1);
        }
        else
        {
          if (this->charging_mos_enabled_ != nullptr) 
            this->charging_mos_enabled_->publish_state(0);
        }
        //current limiting
        if (Bin[5] == 1) {
          if (this->current_limiting_enabled_ != nullptr) 
            this->current_limiting_enabled_->publish_state(1);
        }
        else
        {
          if (this->current_limiting_enabled_ != nullptr) 
            this->current_limiting_enabled_->publish_state(0);
        }
        //heating enabled
        if (Bin[4] == 1) {
          if (this->heating_enabled_ != nullptr) 
            this->heating_enabled_->publish_state(1);
        }
        else
        {
          if (this->heating_enabled_ != nullptr) 
            this->heating_enabled_->publish_state(0);
        }
          
      }
      else {
        ESP_LOGD("TAG", "CRC FAILED!!!");
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
