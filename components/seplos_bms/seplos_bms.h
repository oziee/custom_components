#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/uart/uart.h"

#include <vector>


namespace esphome {
namespace seplos_bms {

class SeplosBmsComponent : public PollingComponent, public uart::UARTDevice {
 public:
  SeplosBmsComponent() = default;

  // SENSORS
  void set_voltage_sensor(sensor::Sensor *voltage_sensor) { voltage_sensor_ = voltage_sensor; }
  void set_current_sensor(sensor::Sensor *current_sensor) { current_sensor_ = current_sensor; }
  void set_battery_level_sensor(sensor::Sensor *battery_level_sensor) { battery_level_sensor_ = battery_level_sensor; }
  void set_cycle_counter_sensor(sensor::Sensor *cycle_counter) { cycle_counter_ = cycle_counter; }
  void set_port_voltage_sensor(sensor::Sensor *port_voltage) { port_voltage_ = port_voltage; }
 
  void set_max_cell_voltage_sensor(sensor::Sensor *max_cell_voltage) { max_cell_voltage_ = max_cell_voltage; }
  void set_max_cell_voltage_number_sensor(sensor::Sensor *max_cell_voltage_number) {
    max_cell_voltage_number_ = max_cell_voltage_number;
  }
  void set_min_cell_voltage_sensor(sensor::Sensor *min_cell_voltage) { min_cell_voltage_ = min_cell_voltage; }
  void set_min_cell_voltage_number_sensor(sensor::Sensor *min_cell_voltage_number) {
    min_cell_voltage_number_ = min_cell_voltage_number;
  }
  void set_max_temperature_sensor(sensor::Sensor *max_temperature) { max_temperature_ = max_temperature; }
  void set_max_temperature_probe_number_sensor(sensor::Sensor *max_temperature_probe_number) {
    max_temperature_probe_number_ = max_temperature_probe_number;
  }
  void set_min_temperature_sensor(sensor::Sensor *min_temperature) { min_temperature_ = min_temperature; }
  void set_min_temperature_probe_number_sensor(sensor::Sensor *min_temperature_probe_number) {
    min_temperature_probe_number_ = min_temperature_probe_number;
  }
  void set_remaining_capacity_sensor(sensor::Sensor *remaining_capacity) { remaining_capacity_ = remaining_capacity; }
  void set_pack_capacity_sensor(sensor::Sensor *pack_capacity) { pack_capacity_ = pack_capacity; }
  void set_cells_number_sensor(sensor::Sensor *cells_number) { cells_number_ = cells_number; }

  void set_temperature_1_sensor(sensor::Sensor *temperature_1_sensor) { temperature_1_sensor_ = temperature_1_sensor; }
  void set_temperature_2_sensor(sensor::Sensor *temperature_2_sensor) { temperature_2_sensor_ = temperature_2_sensor; }
  void set_temperature_3_sensor(sensor::Sensor *temperature_3_sensor) { temperature_3_sensor_ = temperature_3_sensor; }
  void set_temperature_4_sensor(sensor::Sensor *temperature_4_sensor) { temperature_4_sensor_ = temperature_4_sensor; }
  void set_temperature_amb_sensor(sensor::Sensor *temperature_amb_sensor) { temperature_amb_sensor_ = temperature_amb_sensor; }
  void set_temperature_bms_sensor(sensor::Sensor *temperature_bms_sensor) { temperature_bms_sensor_ = temperature_bms_sensor; }

  void set_cell_01_voltage_sensor(sensor::Sensor *cell_01_voltage) { cell_01_voltage_ = cell_01_voltage; }
  void set_cell_02_voltage_sensor(sensor::Sensor *cell_02_voltage) { cell_02_voltage_ = cell_02_voltage; }
  void set_cell_03_voltage_sensor(sensor::Sensor *cell_03_voltage) { cell_03_voltage_ = cell_03_voltage; }
  void set_cell_04_voltage_sensor(sensor::Sensor *cell_04_voltage) { cell_04_voltage_ = cell_04_voltage; }
  void set_cell_05_voltage_sensor(sensor::Sensor *cell_05_voltage) { cell_05_voltage_ = cell_05_voltage; }
  void set_cell_06_voltage_sensor(sensor::Sensor *cell_06_voltage) { cell_06_voltage_ = cell_06_voltage; }
  void set_cell_07_voltage_sensor(sensor::Sensor *cell_07_voltage) { cell_07_voltage_ = cell_07_voltage; }
  void set_cell_08_voltage_sensor(sensor::Sensor *cell_08_voltage) { cell_08_voltage_ = cell_08_voltage; }
  void set_cell_09_voltage_sensor(sensor::Sensor *cell_09_voltage) { cell_09_voltage_ = cell_09_voltage; }
  void set_cell_10_voltage_sensor(sensor::Sensor *cell_10_voltage) { cell_10_voltage_ = cell_10_voltage; }
  void set_cell_11_voltage_sensor(sensor::Sensor *cell_11_voltage) { cell_11_voltage_ = cell_11_voltage; }
  void set_cell_12_voltage_sensor(sensor::Sensor *cell_12_voltage) { cell_12_voltage_ = cell_12_voltage; }
  void set_cell_13_voltage_sensor(sensor::Sensor *cell_13_voltage) { cell_13_voltage_ = cell_13_voltage; }
  void set_cell_14_voltage_sensor(sensor::Sensor *cell_14_voltage) { cell_14_voltage_ = cell_14_voltage; }
  void set_cell_15_voltage_sensor(sensor::Sensor *cell_15_voltage) { cell_15_voltage_ = cell_15_voltage; }
  void set_cell_16_voltage_sensor(sensor::Sensor *cell_16_voltage) { cell_16_voltage_ = cell_16_voltage; }
  void set_cell_deviation_sensor(sensor::Sensor *cell_deviation) { cell_deviation_ = cell_deviation; }

  // TEXT_SENSORS
  void set_bms_status_text_sensor(text_sensor::TextSensor *status_text_sensor) { status_text_sensor_ = status_text_sensor; }
  // BINARY_SENSORS
  void set_charging_mos_enabled_binary_sensor(binary_sensor::BinarySensor *charging_mos_enabled) {
    charging_mos_enabled_ = charging_mos_enabled;
  }
  void set_discharging_mos_enabled_binary_sensor(binary_sensor::BinarySensor *discharging_mos_enabled) {
    discharging_mos_enabled_ = discharging_mos_enabled;
  }
   void set_current_limiting_enabled_binary_sensor(binary_sensor::BinarySensor *current_limiting_enabled) {
    current_limiting_enabled_ = current_limiting_enabled;
  }
   void set_heating_enabled_binary_sensor(binary_sensor::BinarySensor *heating_enabled) {
    heating_enabled_ = heating_enabled;
  }

  //failure warnings
  void set_voltage_sensor_failure_binary_sensor(binary_sensor::BinarySensor *voltage_sensor_failure) {voltage_sensor_failure_ = voltage_sensor_failure;}
  void set_temp_sensor_failure_binary_sensor(binary_sensor::BinarySensor *temp_sensor_failure) {temp_sensor_failure_ = temp_sensor_failure;}
  void set_current_sensor_failure_binary_sensor(binary_sensor::BinarySensor *current_sensor_failure) {current_sensor_failure_ = current_sensor_failure;}
  void set_button_failure_binary_sensor(binary_sensor::BinarySensor *button_failure) {button_failure_ = button_failure;}
  void set_voltage_difference_failure_binary_sensor(binary_sensor::BinarySensor *voltage_difference_failure) {voltage_difference_failure_ = voltage_difference_failure;}
  void set_charge_switch_failure_binary_sensor(binary_sensor::BinarySensor *charge_switch_failure) {charge_switch_failure_ = charge_switch_failure;}
  void set_discharge_switch_failure_binary_sensor(binary_sensor::BinarySensor *discharge_switch_failure) {discharge_switch_failure_ = discharge_switch_failure;}
  void set_current_limiting_failure_binary_sensor(binary_sensor::BinarySensor *current_limiting_failure) {current_limiting_failure_ = current_limiting_failure;}

  //warning 2 - voltages
  void set_ov_cell_warning_binary_sensor(binary_sensor::BinarySensor *ov_cell_warning) {ov_cell_warning_ = ov_cell_warning;}
  void set_ov_cell_protect_binary_sensor(binary_sensor::BinarySensor *ov_cell_protect) {ov_cell_protect_ = ov_cell_protect;}
  void set_uv_cell_warning_binary_sensor(binary_sensor::BinarySensor *uv_cell_warning) {uv_cell_warning_ = uv_cell_warning;}
  void set_uv_cell_protect_binary_sensor(binary_sensor::BinarySensor *uv_cell_protect) {uv_cell_protect_ = uv_cell_protect;}
  void set_ov_pack_warning_binary_sensor(binary_sensor::BinarySensor *ov_pack_warning) {ov_pack_warning_ = ov_pack_warning;}
  void set_ov_pack_protect_binary_sensor(binary_sensor::BinarySensor *ov_pack_protect) {ov_pack_protect_ = ov_pack_protect;}
  void set_uv_pack_warning_binary_sensor(binary_sensor::BinarySensor *uv_pack_warning) {uv_pack_warning_ = uv_pack_warning;}
  void set_uv_pack_protect_binary_sensor(binary_sensor::BinarySensor *uv_pack_protect) {uv_pack_protect_ = uv_pack_protect;}

  //warning 3 - temps
  void set_ot_charge_warning_binary_sensor(binary_sensor::BinarySensor *ot_charge_warning) {ot_charge_warning_ = ot_charge_warning;}
  void set_ot_charge_protect_binary_sensor(binary_sensor::BinarySensor *ot_charge_protect) {ot_charge_protect_ = ot_charge_protect;}
  void set_ut_charge_warning_binary_sensor(binary_sensor::BinarySensor *ut_charge_warning) {ut_charge_warning_ = ut_charge_warning;}
  void set_ut_charge_protect_binary_sensor(binary_sensor::BinarySensor *ut_charge_protect) {ut_charge_protect_ = ut_charge_protect;}
  void set_ot_discharge_warning_binary_sensor(binary_sensor::BinarySensor *ot_discharge_warning) {ot_discharge_warning_ = ot_discharge_warning;}
  void set_ot_discharge_protect_binary_sensor(binary_sensor::BinarySensor *ot_discharge_protect) {ot_discharge_protect_ = ot_discharge_protect;}
  void set_ut_discharge_warning_binary_sensor(binary_sensor::BinarySensor *ut_discharge_warning) {ut_discharge_warning_ = ut_discharge_warning;}
  void set_ut_discharge_protect_binary_sensor(binary_sensor::BinarySensor *ut_discharge_protect) {ut_discharge_protect_ = ut_discharge_protect;}

  //warning 4 - temps amb and bms
  void set_ot_amb_warning_binary_sensor(binary_sensor::BinarySensor *ot_amb_warning) {ot_amb_warning_ = ot_amb_warning;}
  void set_ot_amb_protect_binary_sensor(binary_sensor::BinarySensor *ot_amb_protect) {ot_amb_protect_ = ot_amb_protect;}
  void set_ut_amb_warning_binary_sensor(binary_sensor::BinarySensor *ut_amb_warning) {ut_amb_warning_ = ut_amb_warning;}
  void set_ut_amb_protect_binary_sensor(binary_sensor::BinarySensor *ut_amb_protect) {ut_amb_protect_ = ut_amb_protect;}
  void set_ot_bms_warning_binary_sensor(binary_sensor::BinarySensor *ot_bms_warning) {ot_bms_warning_ = ot_bms_warning;}
  void set_ot_bms_protect_binary_sensor(binary_sensor::BinarySensor *ot_bms_protect) {ot_bms_protect_ = ot_bms_protect;}
  void set_ut_heating_binary_sensor(binary_sensor::BinarySensor *ut_heating) {ut_heating_ = ut_heating;}
  //void set_??_binary_sensor(binary_sensor::BinarySensor *sen) {sen_ = sen;} //Preserved bits

  //warning 5 - currents
  void set_oc_charge_warning_binary_sensor(binary_sensor::BinarySensor *oc_charge_warning) {oc_charge_warning_ = oc_charge_warning;}
  void set_oc_charge_protect_binary_sensor(binary_sensor::BinarySensor *oc_charge_protect) {oc_charge_protect_ = oc_charge_protect;}
  void set_oc_discharge_warning_binary_sensor(binary_sensor::BinarySensor *oc_discharge_warning) {oc_discharge_warning_ = oc_discharge_warning;}
  void set_oc_discharge_protect_binary_sensor(binary_sensor::BinarySensor *oc_discharge_protect) {oc_discharge_protect_ = oc_discharge_protect;}
  void set_oc_transient_protect_binary_sensor(binary_sensor::BinarySensor *oc_transient_protect) {oc_transient_protect_ = oc_transient_protect;}
  void set_sc_output_current_protect_binary_sensor(binary_sensor::BinarySensor *sc_output_current_protect) {sc_output_current_protect_ = sc_output_current_protect;}
  void set_oc_transient_lock_binary_sensor(binary_sensor::BinarySensor *oc_transient_lock) {oc_transient_lock_ = oc_transient_lock;}
  void set_sc_output_current_lock_binary_sensor(binary_sensor::BinarySensor *sc_output_current_lock) {sc_output_current_lock_ = sc_output_current_lock;}

  //warning 6 - random
  void set_ov_charge_protect_binary_sensor(binary_sensor::BinarySensor *ov_charge_protect) {ov_charge_protect_ = ov_charge_protect;}
  void set_power_supply_waiting_binary_sensor(binary_sensor::BinarySensor *power_supply_waiting) {power_supply_waiting_ = power_supply_waiting;}
  void set_remaining_capacity_warning_binary_sensor(binary_sensor::BinarySensor *remaining_capacity_warning) {remaining_capacity_warning_ = remaining_capacity_warning;}
  void set_remaining_capacity_protect_binary_sensor(binary_sensor::BinarySensor *remaining_capacity_protect) {remaining_capacity_protect_ = remaining_capacity_protect;}
  void set_uv_cell_stop_charging_warning_binary_sensor(binary_sensor::BinarySensor *uv_cell_stop_charging_warning) {uv_cell_stop_charging_warning_ = uv_cell_stop_charging_warning;}
  void set_reverse_polarity_protect_binary_sensor(binary_sensor::BinarySensor *reverse_polarity_protect) {reverse_polarity_protect_ = reverse_polarity_protect;}
  void set_output_connection_failure_binary_sensor(binary_sensor::BinarySensor *output_connection_failure) {output_connection_failure_ = output_connection_failure;}
  void set_internal_bit_binary_sensor(binary_sensor::BinarySensor *internal_bit) {internal_bit_ = internal_bit;} //dont know??


  void setup() override;
  void dump_config() override;
  void update() override;

  float get_setup_priority() const override;
  void set_address(uint8_t address) { this->addr_ = address; }

 protected:
  void request_data_(uint8_t data_id);
  void decode_data_(std::vector<uint8_t> data);
  void convertDecToBin(int Dec, bool Bin[]);

  uint8_t addr_;

  sensor::Sensor *voltage_sensor_{nullptr};
  sensor::Sensor *current_sensor_{nullptr};
  sensor::Sensor *battery_level_sensor_{nullptr};
  sensor::Sensor *max_cell_voltage_{nullptr};
  sensor::Sensor *max_cell_voltage_number_{nullptr};
  sensor::Sensor *min_cell_voltage_{nullptr};
  sensor::Sensor *min_cell_voltage_number_{nullptr};
  sensor::Sensor *max_temperature_{nullptr};
  sensor::Sensor *max_temperature_probe_number_{nullptr};
  sensor::Sensor *min_temperature_{nullptr};
  sensor::Sensor *min_temperature_probe_number_{nullptr};
  sensor::Sensor *remaining_capacity_{nullptr};
  sensor::Sensor *pack_capacity_{nullptr};
  sensor::Sensor *cells_number_{nullptr};
  sensor::Sensor *temperature_1_sensor_{nullptr};
  sensor::Sensor *temperature_2_sensor_{nullptr};
  sensor::Sensor *temperature_3_sensor_{nullptr};
  sensor::Sensor *temperature_4_sensor_{nullptr};
  sensor::Sensor *temperature_amb_sensor_{nullptr};
  sensor::Sensor *temperature_bms_sensor_{nullptr};
  sensor::Sensor *cell_01_voltage_{nullptr};
  sensor::Sensor *cell_02_voltage_{nullptr};
  sensor::Sensor *cell_03_voltage_{nullptr};
  sensor::Sensor *cell_04_voltage_{nullptr};
  sensor::Sensor *cell_05_voltage_{nullptr};
  sensor::Sensor *cell_06_voltage_{nullptr};
  sensor::Sensor *cell_07_voltage_{nullptr};
  sensor::Sensor *cell_08_voltage_{nullptr};
  sensor::Sensor *cell_09_voltage_{nullptr};
  sensor::Sensor *cell_10_voltage_{nullptr};
  sensor::Sensor *cell_11_voltage_{nullptr};
  sensor::Sensor *cell_12_voltage_{nullptr};
  sensor::Sensor *cell_13_voltage_{nullptr};
  sensor::Sensor *cell_14_voltage_{nullptr};
  sensor::Sensor *cell_15_voltage_{nullptr};
  sensor::Sensor *cell_16_voltage_{nullptr};
  sensor::Sensor *cell_deviation_{nullptr};
  sensor::Sensor *cycle_counter_{nullptr};
   sensor::Sensor *port_voltage_{nullptr};

  text_sensor::TextSensor *status_text_sensor_{nullptr};

  binary_sensor::BinarySensor *charging_mos_enabled_{nullptr};
  binary_sensor::BinarySensor *discharging_mos_enabled_{nullptr};
  binary_sensor::BinarySensor *current_limiting_enabled_{nullptr};
  binary_sensor::BinarySensor *heating_enabled_{nullptr};
  //4-7 Preserved bits

  //warning 1 - failures
  binary_sensor::BinarySensor *voltage_sensor_failure_{nullptr};
  binary_sensor::BinarySensor *temp_sensor_failure_{nullptr};
  binary_sensor::BinarySensor *current_sensor_failure_{nullptr};
  binary_sensor::BinarySensor *button_failure_{nullptr};
  binary_sensor::BinarySensor *voltage_difference_failure_{nullptr};
  binary_sensor::BinarySensor *charge_switch_failure_{nullptr};
  binary_sensor::BinarySensor *discharge_switch_failure_{nullptr};
  binary_sensor::BinarySensor *current_limiting_failure_{nullptr};

  //warning 2 - voltages
  binary_sensor::BinarySensor *ov_cell_warning_{nullptr};
  binary_sensor::BinarySensor *ov_cell_protect_{nullptr};
  binary_sensor::BinarySensor *uv_cell_warning_{nullptr};
  binary_sensor::BinarySensor *uv_cell_protect_{nullptr};
  binary_sensor::BinarySensor *ov_pack_warning_{nullptr};
  binary_sensor::BinarySensor *ov_pack_protect_{nullptr};
  binary_sensor::BinarySensor *uv_pack_warning_{nullptr};
  binary_sensor::BinarySensor *uv_pack_protect_{nullptr};

  //warning 3 - temps
  binary_sensor::BinarySensor *ot_charge_warning_{nullptr};
  binary_sensor::BinarySensor *ot_charge_protect_{nullptr};
  binary_sensor::BinarySensor *ut_charge_warning_{nullptr};
  binary_sensor::BinarySensor *ut_charge_protect_{nullptr};
  binary_sensor::BinarySensor *ot_discharge_warning_{nullptr};
  binary_sensor::BinarySensor *ot_discharge_protect_{nullptr};
  binary_sensor::BinarySensor *ut_discharge_warning_{nullptr};
  binary_sensor::BinarySensor *ut_discharge_protect_{nullptr};

  //warning 4 - temps amb and bms
  binary_sensor::BinarySensor *ot_amb_warning_{nullptr};
  binary_sensor::BinarySensor *ot_amb_protect_{nullptr};
  binary_sensor::BinarySensor *ut_amb_warning_{nullptr};
  binary_sensor::BinarySensor *ut_amb_protect_{nullptr};
  binary_sensor::BinarySensor *ot_bms_warning_{nullptr};
  binary_sensor::BinarySensor *ot_bms_protect_{nullptr};
  binary_sensor::BinarySensor *ut_heating_{nullptr};
  //binary_sensor::BinarySensor *ut_discharge_protect_{nullptr}; //Preserved bits
  
  //warning 5 - currents
  binary_sensor::BinarySensor *oc_charge_warning_{nullptr};
  binary_sensor::BinarySensor *oc_charge_protect_{nullptr};
  binary_sensor::BinarySensor *oc_discharge_warning_{nullptr};
  binary_sensor::BinarySensor *oc_discharge_protect_{nullptr};
  binary_sensor::BinarySensor *oc_transient_protect_{nullptr};
  binary_sensor::BinarySensor *sc_output_current_protect_{nullptr};
  binary_sensor::BinarySensor *oc_transient_lock_{nullptr};
  binary_sensor::BinarySensor *sc_output_current_lock_{nullptr};

  //warning 6 - random
  binary_sensor::BinarySensor *ov_charge_protect_{nullptr};
  binary_sensor::BinarySensor *power_supply_waiting_{nullptr};
  binary_sensor::BinarySensor *remaining_capacity_warning_{nullptr};
  binary_sensor::BinarySensor *remaining_capacity_protect_{nullptr};
  binary_sensor::BinarySensor *uv_cell_stop_charging_warning_{nullptr};
  binary_sensor::BinarySensor *reverse_polarity_protect_{nullptr};
  binary_sensor::BinarySensor *output_connection_failure_{nullptr};
  binary_sensor::BinarySensor *internal_bit_{nullptr}; //dont know??



};

}  // namespace seplos_bms
}  // namespace esphome
