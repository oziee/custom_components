# Seplos BMS - LCD rs485 communication

A configured uart component is required.

Example:
```yaml
seplos_bms:
  uart_id: uart_bus
  update_interval: 60s

binary_sensor:
  - platform: seplos_bms
    charging_mos_enabled:
      name: "Charging MOS"
    discharging_mos_enabled:
      name: "Discharging MOS"
    current_limiting_enabled:
      name: "Current Limiting Enabled"
    ...

text_sensor:
  - platform: seplos_bms
    bms_status:
      name: "Status"

sensor:
  - platform: seplos_bms
    voltage:
      name: "Battery Voltage"
    current:
      name: "Battery Current"
    battery_level:
      name: "Battery SOC"
    ...
```

The `uart_id` is optional.
the `update_interval` is optional.

All sensors are optional.

The available sensors are:
- `cell_01_voltage`
- `cell_02_voltage`
- `cell_03_voltage`
- `cell_04_voltage`
- `cell_05_voltage`
- `cell_06_voltage`
- `cell_07_voltage`
- `cell_08_voltage`
- `cell_09_voltage`
- `cell_10_voltage`
- `cell_11_voltage`
- `cell_12_voltage`
- `cell_13_voltage`
- `cell_14_voltage`
- `cell_15_voltage`
- `cell_16_voltage`
- `cell_deviation`
- `max_cell_voltage`
- `max_cell_voltage_number`
- `min_cell_voltage`
- `min_cell_voltage_number`
- `cells_number`
- `pack_capacity`
- `remaining_capacity`
- `cycle_counter`
- `port_voltage`
- `temperature_1`
- `temperature_2`
- `temperature_3`
- `temperature_4`
- `temperature_amb`
- `temperature_bms`

The available text sensor is: (this reports Charging, Discharging, Float .. etc)
- `bms_status`

The available binary sensors are:
- `charging_mos_enabled`
- `discharging_mos_enabled`
- `current_limiting_enabled`
- `heating_enabled`
- `voltage_sensor_failure`
- `temp_sensor_failure`
- `current_sensor_failure`
- `button_failure`
- `voltage_difference_failure`
- `charge_switch_failure`
- `discharge_switch_failure`
- `current_limiting_failure`
- `ov_cell_warning`
- `ov_cell_protect`
- `uv_cell_warning`
- `uv_cell_protect`
- `ov_pack_warning`
- `ov_pack_protect`
- `uv_pack_warning`
- `uv_pack_protect`
- `ot_charge_warning`
- `ot_charge_protect`
- `ut_charge_warning`
- `ut_charge_protect`
- `ot_discharge_warning`
- `ot_discharge_protect`
- `ut_discharge_warning`
- `ut_discharge_protect`
- `ot_amb_warning`
- `ot_amb_protect`
- `ut_amb_warning`
- `ut_amb_protect`
- `ot_bms_warning`
- `ot_bms_protect`
- `ut_heating`
- `oc_charge_warning`
- `oc_charge_protect`
- `oc_discharge_warning`
- `oc_discharge_protect`
- `oc_transient_protect`
- `sc_output_current_protect`
- `oc_transient_lock`
- `sc_output_current_lock`
- `ov_charge_protect`
- `power_supply_waiting`
- `remaining_capacity_warning`
- `remaining_capacity_protect`
- `uv_cell_stop_charging_warning`
- `reverse_polarity_protect`
- `output_connection_failure`
- `internal_bit`

```
