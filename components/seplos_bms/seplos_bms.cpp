#include "seplos_bms.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"
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


void SeplosBmsComponent::setup() {
  update();
}

void SeplosBmsComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Seplos BMS:");
  this->check_uart_settings(9600);
}

void SeplosBmsComponent::update() {

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
  //reset Bin 
  for (int z=0; z<8; z++) {
    Bin[z]=0;
  }
  //work out values
  for(int i = 7 ; i >= 0 ; i--) {
    if(pow(2, i)<=Dec) {
      Dec = Dec - pow(2, i);
      Bin[8-(i+1)] = 1;
    } else {
    }
  }
}

void SeplosBmsComponent::decode_data_(std::vector<uint8_t> data) {

  //ESP_LOGD("TAG", "Received this data:");
  //ESP_LOGD(TAG, "%s", format_hex_pretty(&data.front(), data.size()).c_str());
  // std::string str1;
  // str1.assign(data.begin(), data.end());
  // ESP_LOGD("TAG", "%s", (char*) data.data().c_str());


  auto it = data.begin();


  while ((it = std::find(it, data.end(), SEPLOS_START_BYTE)) != data.end()) {
    if (data.end() - it >= SEPLOS_FRAME_SIZE && it[0] == SEPLOS_START_BYTE && it[1] == 0x46 && it[75] == SEPLOS_END_BYTE) {
      
      unsigned short value1 = (int)encode_uint16(it[73], it[74]);
      unsigned short value2 = crc.XModemCrc(data.data(),1,72);
      if (value1 == value2) {
        //CRC ALL GOOD!!
        ESP_LOGD("TAG", "CRCCHeck GOOD!!");

        auto seplos_get_16bit = [&](size_t i) -> uint16_t {
          return (uint16_t(data[i + 0]) << 8) | (uint16_t(data[i + 1]) << 0);
        };


        //NUMBER OF CELLS IN THE PACK
        int8_t cells = data[3];
        if (this->cells_number_) {
          this->cells_number_->publish_state(cells);
        }

        //Cell voltages
        float min_cell_voltage = 10000.0f;
        float max_cell_voltage = -0.0f;
        uint8_t min_voltage_cell = 0;
        uint8_t max_voltage_cell = 0;
        uint8_t looper = 0;
        
        //CELLS 8,72 
        float ivt[20];
        //for (int i = 4; i < 35; i += 2) {
        for (uint8_t i = 0; i < std::min((uint8_t) 16, cells); i++) {
          float cell_voltage = (float) seplos_get_16bit(4 + (i * 2)) ;
          //float cell_voltage = (float) encode_uint16(it[i], it[i+1]);
          if (cell_voltage < min_cell_voltage) {
            min_cell_voltage = cell_voltage;
            min_voltage_cell = looper+1;
          }
          if (cell_voltage > max_cell_voltage) {
            max_cell_voltage = cell_voltage;
            max_voltage_cell = looper+1;
          }
          ivt[looper] = cell_voltage * 0.001f;
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
          this->max_cell_voltage_->publish_state((float) max_cell_voltage * 0.001f);
        }
        if (this->max_cell_voltage_number_) {
          this->max_cell_voltage_number_->publish_state(max_voltage_cell);
        }
        if (this->min_cell_voltage_) {
          this->min_cell_voltage_->publish_state((float) min_cell_voltage * 0.001f);
        }
        if (this->min_cell_voltage_number_) {
          this->min_cell_voltage_number_->publish_state(min_voltage_cell);
        }

        if (this->cell_deviation_) {
          this->cell_deviation_->publish_state((float) (max_cell_voltage-min_cell_voltage) * 0.001f);
        }

        uint8_t offset = 4 + (cells * 2);

        //temps
        if (this->temperature_1_sensor_) { 
          float raw_temperature = (float) seplos_get_16bit(offset + 1 + (0 * 2));
          this->temperature_1_sensor_->publish_state((float) (raw_temperature - 2731) / 10);
        }
        if (this->temperature_2_sensor_) { 
          float raw_temperature = (float) seplos_get_16bit(offset + 1 + (1 * 2));
          this->temperature_2_sensor_->publish_state((float) (encode_uint16(it[39], it[40]) - 2731) / 10);
        }
        if (this->temperature_3_sensor_) { 
          float raw_temperature = (float) seplos_get_16bit(offset + 1 + (2 * 2));
          this->temperature_3_sensor_->publish_state((float) (encode_uint16(it[41], it[42]) - 2731) / 10);
        }
        if (this->temperature_4_sensor_) { 
          float raw_temperature = (float) seplos_get_16bit(offset + 1 + (3 * 2));
          this->temperature_4_sensor_->publish_state((float) (encode_uint16(it[43], it[44]) - 2731) / 10);
        }
        if (this->temperature_amb_sensor_) { 
          float raw_temperature = (float) seplos_get_16bit(offset + 1 + (4 * 2));
          this->temperature_amb_sensor_->publish_state((float) (encode_uint16(it[45], it[46]) - 2731) / 10);
        }
        if (this->temperature_bms_sensor_) { 
          float raw_temperature = (float) seplos_get_16bit(offset + 1 + (5 * 2));
          this->temperature_bms_sensor_->publish_state((float) (encode_uint16(it[47], it[48]) - 2731) / 10);
        }
        // if (this->temperature_1_sensor_) { 
        //   float raw_temperature = (float) seplos_get_16bit(37));
        //   this->temperature_1_sensor_->publish_state((float) (encode_uint16(it[37], it[38]) - 2731) / 10);
        // }
        // if (this->temperature_2_sensor_) { 
        //   this->temperature_2_sensor_->publish_state((float) (encode_uint16(it[39], it[40]) - 2731) / 10);
        // }
        // if (this->temperature_3_sensor_) { 
        //   this->temperature_3_sensor_->publish_state((float) (encode_uint16(it[41], it[42]) - 2731) / 10);
        // }
        // if (this->temperature_4_sensor_) { 
        //   this->temperature_4_sensor_->publish_state((float) (encode_uint16(it[43], it[44]) - 2731) / 10);
        // }
        // if (this->temperature_amb_sensor_) { 
        //   this->temperature_amb_sensor_->publish_state((float) (encode_uint16(it[45], it[46]) - 2731) / 10);
        // }
        // if (this->temperature_bms_sensor_) { 
        //   this->temperature_bms_sensor_->publish_state((float) (encode_uint16(it[47], it[48]) - 2731) / 10);
        // }


        
        float current = (float) ((int16_t) seplos_get_16bit(49)) * 0.01f;
        ESP_LOGD("TAG", "seplos_get_16bit current: %f", current);
        //current
        if (this->current_sensor_) { 
          this->current_sensor_->publish_state((float) encode_uint16(it[49], it[50])  / 100);
        }
        ESP_LOGD("TAG", "current: %f", (float) encode_uint16(it[49], it[50]));
        ESP_LOGD("TAG", "current: %d", it[49]);
        ESP_LOGD("TAG", "current: %d", it[50]);

        

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
        convertDecToBin(it[63],Bin);
        ESP_LOGD("TAG", "Status Switches dec: %d", it[63]);
        for (int z=0; z<8; z++) {
          ESP_LOGD("TAG", "Status switch Bin: %d - %d", z, Bin[z]);
        }
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

        //warning 1
        convertDecToBin(it[65],Bin);
        ESP_LOGD("TAG", "Warning 1 dec: %d", it[65]);
        for (int z=0; z<8; z++) {
          ESP_LOGD("TAG", "Warning 1 Bin: %d - %d", z, Bin[z]);
        }
        if (Bin[7] == 1) {
          if (this->voltage_sensor_failure_ != nullptr) 
            this->voltage_sensor_failure_->publish_state(1);
        }
        else
        {
          if (this->voltage_sensor_failure_ != nullptr) 
            this->voltage_sensor_failure_->publish_state(0);
        }
        if (Bin[6] == 1) {
          if (this->temp_sensor_failure_ != nullptr) 
            this->temp_sensor_failure_->publish_state(1);
        }
        else
        {
          if (this->temp_sensor_failure_ != nullptr) 
            this->temp_sensor_failure_->publish_state(0);
        }
        if (Bin[5] == 1) {
          if (this->current_sensor_failure_ != nullptr) 
            this->current_sensor_failure_->publish_state(1);
        }
        else
        {
          if (this->current_sensor_failure_ != nullptr) 
            this->current_sensor_failure_->publish_state(0);
        }
        if (Bin[4] == 1) {
          if (this->button_failure_ != nullptr) 
            this->button_failure_->publish_state(1);
        }
        else
        {
          if (this->button_failure_ != nullptr) 
            this->button_failure_->publish_state(0);
        }
        if (Bin[3] == 1) {
          if (this->voltage_difference_failure_ != nullptr) 
            this->voltage_difference_failure_->publish_state(1);
        }
        else
        {
          if (this->voltage_difference_failure_ != nullptr) 
            this->voltage_difference_failure_->publish_state(0);
        }
        if (Bin[2] == 1) {
          if (this->charge_switch_failure_ != nullptr) 
            this->charge_switch_failure_->publish_state(1);
        }
        else
        {
          if (this->charge_switch_failure_ != nullptr) 
            this->charge_switch_failure_->publish_state(0);
        }
        if (Bin[1] == 1) {
          if (this->discharge_switch_failure_ != nullptr) 
            this->discharge_switch_failure_->publish_state(1);
        }
        else
        {
          if (this->discharge_switch_failure_ != nullptr) 
            this->discharge_switch_failure_->publish_state(0);
        }
        if (Bin[0] == 1) {
          if (this->current_limiting_failure_ != nullptr) 
            this->current_limiting_failure_->publish_state(1);
        }
        else
        {
          if (this->current_limiting_failure_ != nullptr) 
            this->current_limiting_failure_->publish_state(0);
        }

        //warning 2
        convertDecToBin(it[66],Bin);
        ESP_LOGD("TAG", "Warning 2 dec: %d", it[66]);
        for (int z=0; z<8; z++) {
          ESP_LOGD("TAG", "Warning 2 Bin: %d - %d", z, Bin[z]);
        }
        if (Bin[7] == 1) {
          if (this->ov_cell_warning_ != nullptr) 
            this->ov_cell_warning_->publish_state(1);
        }
        else
        {
          if (this->ov_cell_warning_ != nullptr) 
            this->ov_cell_warning_->publish_state(0);
        }
        if (Bin[6] == 1) {
          if (this->ov_cell_protect_ != nullptr) 
            this->ov_cell_protect_->publish_state(1);
        }
        else
        {
          if (this->ov_cell_protect_ != nullptr) 
            this->ov_cell_protect_->publish_state(0);
        }
        if (Bin[5] == 1) {
          if (this->uv_cell_warning_ != nullptr) 
            this->uv_cell_warning_->publish_state(1);
        }
        else
        {
          if (this->uv_cell_warning_ != nullptr) 
            this->uv_cell_warning_->publish_state(0);
        }
        if (Bin[4] == 1) {
          if (this->uv_cell_protect_ != nullptr) 
            this->uv_cell_protect_->publish_state(1);
        }
        else
        {
          if (this->uv_cell_protect_ != nullptr) 
            this->uv_cell_protect_->publish_state(0);
        }
        if (Bin[3] == 1) {
          if (this->ov_pack_warning_ != nullptr) 
            this->ov_pack_warning_->publish_state(1);
        }
        else
        {
          if (this->ov_pack_warning_ != nullptr) 
            this->ov_pack_warning_->publish_state(0);
        }
        if (Bin[2] == 1) {
          if (this->ov_pack_protect_ != nullptr) 
            this->ov_pack_protect_->publish_state(1);
        }
        else
        {
          if (this->ov_pack_protect_ != nullptr) 
            this->ov_pack_protect_->publish_state(0);
        }
        if (Bin[1] == 1) {
          if (this->uv_pack_warning_ != nullptr) 
            this->uv_pack_warning_->publish_state(1);
        }
        else
        {
          if (this->uv_pack_warning_ != nullptr) 
            this->uv_pack_warning_->publish_state(0);
        }
        if (Bin[0] == 1) {
          if (this->uv_pack_protect_ != nullptr) 
            this->uv_pack_protect_->publish_state(1);
        }
        else
        {
          if (this->uv_pack_protect_ != nullptr) 
            this->uv_pack_protect_->publish_state(0);
        }

        //warning 3
        convertDecToBin(it[67],Bin);
        ESP_LOGD("TAG", "Warning 3 dec: %d", it[67]);
        for (int z=0; z<8; z++) {
          ESP_LOGD("TAG", "Warning 3 Bin: %d - %d", z, Bin[z]);
        }
        if (Bin[7] == 1) {
          if (this->ot_charge_warning_ != nullptr) 
            this->ot_charge_warning_->publish_state(1);
        }
        else
        {
          if (this->ot_charge_warning_ != nullptr) 
            this->ot_charge_warning_->publish_state(0);
        }
        if (Bin[6] == 1) {
          if (this->ot_charge_protect_ != nullptr) 
            this->ot_charge_protect_->publish_state(1);
        }
        else
        {
          if (this->ot_charge_protect_ != nullptr) 
            this->ot_charge_protect_->publish_state(0);
        }
        if (Bin[5] == 1) {
          if (this->ut_charge_warning_ != nullptr) 
            this->ut_charge_warning_->publish_state(1);
        }
        else
        {
          if (this->ut_charge_warning_ != nullptr) 
            this->ut_charge_warning_->publish_state(0);
        }
        if (Bin[4] == 1) {
          if (this->ut_charge_protect_ != nullptr) 
            this->ut_charge_protect_->publish_state(1);
        }
        else
        {
          if (this->ut_charge_protect_ != nullptr) 
            this->ut_charge_protect_->publish_state(0);
        }
        if (Bin[3] == 1) {
          if (this->ot_discharge_warning_ != nullptr) 
            this->ot_discharge_warning_->publish_state(1);
        }
        else
        {
          if (this->ot_discharge_warning_ != nullptr) 
            this->ot_discharge_warning_->publish_state(0);
        }
        if (Bin[2] == 1) {
          if (this->ot_discharge_protect_ != nullptr) 
            this->ot_discharge_protect_->publish_state(1);
        }
        else
        {
          if (this->ot_discharge_protect_ != nullptr) 
            this->ot_discharge_protect_->publish_state(0);
        }
        if (Bin[1] == 1) {
          if (this->ut_discharge_warning_ != nullptr) 
            this->ut_discharge_warning_->publish_state(1);
        }
        else
        {
          if (this->ut_discharge_warning_ != nullptr) 
            this->ut_discharge_warning_->publish_state(0);
        }
        if (Bin[0] == 1) {
          if (this->ut_discharge_protect_ != nullptr) 
            this->ut_discharge_protect_->publish_state(1);
        }
        else
        {
          if (this->ut_discharge_protect_ != nullptr) 
            this->ut_discharge_protect_->publish_state(0);
        }

        //warning 4
        convertDecToBin(it[68],Bin);
        ESP_LOGD("TAG", "Warning 4 dec: %d", it[68]);
        for (int z=0; z<8; z++) {
          ESP_LOGD("TAG", "Warning 4 Bin: %d - %d", z, Bin[z]);
        }
        if (Bin[7] == 1) {
          if (this->ot_amb_warning_ != nullptr) 
            this->ot_amb_warning_->publish_state(1);
        }
        else
        {
          if (this->ot_amb_warning_ != nullptr) 
            this->ot_amb_warning_->publish_state(0);
        }
        if (Bin[6] == 1) {
          if (this->ot_amb_protect_ != nullptr) 
            this->ot_amb_protect_->publish_state(1);
        }
        else
        {
          if (this->ot_amb_protect_ != nullptr) 
            this->ot_amb_protect_->publish_state(0);
        }
        if (Bin[5] == 1) {
          if (this->ut_amb_warning_ != nullptr) 
            this->ut_amb_warning_->publish_state(1);
        }
        else
        {
          if (this->ut_amb_warning_ != nullptr) 
            this->ut_amb_warning_->publish_state(0);
        }
        if (Bin[4] == 1) {
          if (this->ut_amb_protect_ != nullptr) 
            this->ut_amb_protect_->publish_state(1);
        }
        else
        {
          if (this->ut_amb_protect_ != nullptr) 
            this->ut_amb_protect_->publish_state(0);
        }
        if (Bin[3] == 1) {
          if (this->ot_bms_warning_ != nullptr) 
            this->ot_bms_warning_->publish_state(1);
        }
        else
        {
          if (this->ot_bms_warning_ != nullptr) 
            this->ot_bms_warning_->publish_state(0);
        }
        if (Bin[2] == 1) {
          if (this->ot_bms_protect_ != nullptr) 
            this->ot_bms_protect_->publish_state(1);
        }
        else
        {
          if (this->ot_bms_protect_ != nullptr) 
            this->ot_bms_protect_->publish_state(0);
        }
        if (Bin[1] == 1) {
          if (this->ut_heating_ != nullptr) 
            this->ut_heating_->publish_state(1);
        }
        else
        {
          if (this->ut_heating_ != nullptr) 
            this->ut_heating_->publish_state(0);
        }
        //preserved
        // if (Bin[0] == 1) { 
        //   if (this->???? != nullptr) 
        //     this->????->publish_state(1);
        // }
        // else
        // {
        //   if (this->???? != nullptr) 
        //     this->????->publish_state(0);
        // }

        //warning 5
        convertDecToBin(it[69],Bin);
        ESP_LOGD("TAG", "Warning 5 dec: %d", it[69]);
        for (int z=0; z<8; z++) {
          ESP_LOGD("TAG", "Warning 5 Bin: %d - %d", z, Bin[z]);
        }
        if (Bin[7] == 1) {
          if (this->oc_charge_warning_ != nullptr) 
            this->oc_charge_warning_->publish_state(1);
        }
        else
        {
          if (this->oc_charge_warning_ != nullptr) 
            this->oc_charge_warning_->publish_state(0);
        }
        if (Bin[6] == 1) {
          if (this->oc_charge_protect_ != nullptr) 
            this->oc_charge_protect_->publish_state(1);
        }
        else
        {
          if (this->oc_charge_protect_ != nullptr) 
            this->oc_charge_protect_->publish_state(0);
        }
        if (Bin[5] == 1) {
          if (this->oc_discharge_warning_ != nullptr) 
            this->oc_discharge_warning_->publish_state(1);
        }
        else
        {
          if (this->oc_discharge_warning_ != nullptr) 
            this->oc_discharge_warning_->publish_state(0);
        }
        if (Bin[4] == 1) {
          if (this->oc_discharge_protect_ != nullptr) 
            this->oc_discharge_protect_->publish_state(1);
        }
        else
        {
          if (this->oc_discharge_protect_ != nullptr) 
            this->oc_discharge_protect_->publish_state(0);
        }
        if (Bin[3] == 1) {
          if (this->oc_transient_protect_ != nullptr) 
            this->oc_transient_protect_->publish_state(1);
        }
        else
        {
          if (this->oc_transient_protect_ != nullptr) 
            this->oc_transient_protect_->publish_state(0);
        }
        if (Bin[2] == 1) {
          if (this->sc_output_current_protect_ != nullptr) 
            this->sc_output_current_protect_->publish_state(1);
        }
        else
        {
          if (this->sc_output_current_protect_ != nullptr) 
            this->sc_output_current_protect_->publish_state(0);
        }
        if (Bin[1] == 1) {
          if (this->oc_transient_lock_ != nullptr) 
            this->oc_transient_lock_->publish_state(1);
        }
        else
        {
          if (this->oc_transient_lock_ != nullptr) 
            this->oc_transient_lock_->publish_state(0);
        }
        if (Bin[0] == 1) {
          if (this->sc_output_current_lock_ != nullptr) 
            this->sc_output_current_lock_->publish_state(1);
        }
        else
        {
          if (this->sc_output_current_lock_ != nullptr) 
            this->sc_output_current_lock_->publish_state(0);
        }

        //warning 6
        convertDecToBin(it[70],Bin);
        ESP_LOGD("TAG", "Warning 6 dec: %d", it[70]);
        for (int z=0; z<8; z++) {
          ESP_LOGD("TAG", "Warning 6 Bin: %d - %d", z, Bin[z]);
        }
        if (Bin[7] == 1) {
          if (this->ov_charge_protect_ != nullptr) 
            this->ov_charge_protect_->publish_state(1);
        }
        else
        {
          if (this->ov_charge_protect_ != nullptr) 
            this->ov_charge_protect_->publish_state(0);
        }
        if (Bin[6] == 1) {
          if (this->power_supply_waiting_ != nullptr) 
            this->power_supply_waiting_->publish_state(1);
        }
        else
        {
          if (this->power_supply_waiting_ != nullptr) 
            this->power_supply_waiting_->publish_state(0);
        }
        if (Bin[5] == 1) {
          if (this->remaining_capacity_warning_ != nullptr) 
            this->remaining_capacity_warning_->publish_state(1);
        }
        else
        {
          if (this->remaining_capacity_warning_ != nullptr) 
            this->remaining_capacity_warning_->publish_state(0);
        }
        if (Bin[4] == 1) {
          if (this->remaining_capacity_protect_ != nullptr) 
            this->remaining_capacity_protect_->publish_state(1);
        }
        else
        {
          if (this->remaining_capacity_protect_ != nullptr) 
            this->remaining_capacity_protect_->publish_state(0);
        }
        if (Bin[3] == 1) {
          if (this->uv_cell_stop_charging_warning_ != nullptr) 
            this->uv_cell_stop_charging_warning_->publish_state(1);
        }
        else
        {
          if (this->uv_cell_stop_charging_warning_ != nullptr) 
            this->uv_cell_stop_charging_warning_->publish_state(0);
        }
        if (Bin[2] == 1) {
          if (this->reverse_polarity_protect_ != nullptr) 
            this->reverse_polarity_protect_->publish_state(1);
        }
        else
        {
          if (this->reverse_polarity_protect_ != nullptr) 
            this->reverse_polarity_protect_->publish_state(0);
        }
        if (Bin[1] == 1) {
          if (this->output_connection_failure_ != nullptr) 
            this->output_connection_failure_->publish_state(1);
        }
        else
        {
          if (this->output_connection_failure_ != nullptr) 
            this->output_connection_failure_->publish_state(0);
        }
        if (Bin[0] == 1) {
          if (this->internal_bit_ != nullptr) 
            this->internal_bit_->publish_state(1);
        }
        else
        {
          if (this->internal_bit_ != nullptr) 
            this->internal_bit_->publish_state(0);
        }

        //end of sending data  
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
