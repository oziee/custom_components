import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_VOLTAGE,
    CONF_CURRENT,
    CONF_BATTERY_LEVEL,
    DEVICE_CLASS_VOLTAGE,
    DEVICE_CLASS_CURRENT,
    DEVICE_CLASS_BATTERY,
    DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_POWER,
    STATE_CLASS_MEASUREMENT,
    UNIT_VOLT,
    UNIT_WATT,
    UNIT_AMPERE,
    UNIT_PERCENT,
    UNIT_CELSIUS,
    ICON_FLASH,
    ICON_COUNTER,
    ICON_THERMOMETER,
    ICON_GAUGE,
    ICON_EMPTY,
    ENTITY_CATEGORY_DIAGNOSTIC,
    ENTITY_CATEGORY_CONFIG,
)
from . import SeplosBmsComponent, CONF_BMS_SEPLOS_ID

CONF_MAX_CELL_VOLTAGE = "max_cell_voltage"
CONF_MAX_CELL_VOLTAGE_NUMBER = "max_cell_voltage_number"
CONF_MIN_CELL_VOLTAGE = "min_cell_voltage"
CONF_MIN_CELL_VOLTAGE_NUMBER = "min_cell_voltage_number"
CONF_CELLS_NUMBER = "cells_number"

CONF_PACK_CAPACITY = "pack_capacity"
CONF_REMAINING_CAPACITY = "remaining_capacity"
CONF_CYCLE_COUNTER = "cycle_counter"
CONF_PORT_VOLTAGE = "port_voltage"
CONF_CHARGING_POWER = "charging_power"
CONF_DISCHARGING_POWER = "discharging_power"
CONF_POWER = "power"

CONF_TEMPERATURE_1 = "temperature_1"
CONF_TEMPERATURE_2 = "temperature_2"
CONF_TEMPERATURE_3 = "temperature_3"
CONF_TEMPERATURE_4 = "temperature_4"
CONF_TEMPERATURE_AMB = "temperature_amb"
CONF_TEMPERATURE_BMS = "temperature_bms"

CONF_CELL_01_VOLTAGE = "cell_01_voltage"
CONF_CELL_02_VOLTAGE = "cell_02_voltage"
CONF_CELL_03_VOLTAGE = "cell_03_voltage"
CONF_CELL_04_VOLTAGE = "cell_04_voltage"
CONF_CELL_05_VOLTAGE = "cell_05_voltage"
CONF_CELL_06_VOLTAGE = "cell_06_voltage"
CONF_CELL_07_VOLTAGE = "cell_07_voltage"
CONF_CELL_08_VOLTAGE = "cell_08_voltage"
CONF_CELL_09_VOLTAGE = "cell_09_voltage"
CONF_CELL_10_VOLTAGE = "cell_10_voltage"
CONF_CELL_11_VOLTAGE = "cell_11_voltage"
CONF_CELL_12_VOLTAGE = "cell_12_voltage"
CONF_CELL_13_VOLTAGE = "cell_13_voltage"
CONF_CELL_14_VOLTAGE = "cell_14_voltage"
CONF_CELL_15_VOLTAGE = "cell_15_voltage"
CONF_CELL_16_VOLTAGE = "cell_16_voltage"
CONF_CELL_DEVIATION = "cell_deviation"

ICON_CURRENT_DC = "mdi:current-dc"
ICON_BATTERY_OUTLINE = "mdi:battery-outline"
ICON_THERMOMETER_CHEVRON_UP = "mdi:thermometer-chevron-up"
ICON_THERMOMETER_CHEVRON_DOWN = "mdi:thermometer-chevron-down"
ICON_CAR_BATTERY = "mdi:car-battery"

UNIT_AMPERE_HOUR = "Ah"

TYPES = [
    CONF_VOLTAGE,
    CONF_CURRENT,
    CONF_BATTERY_LEVEL,
    CONF_CYCLE_COUNTER,
    CONF_PORT_VOLTAGE,
    CONF_MAX_CELL_VOLTAGE,
    CONF_MAX_CELL_VOLTAGE_NUMBER,
    CONF_MIN_CELL_VOLTAGE,
    CONF_MIN_CELL_VOLTAGE_NUMBER,
    CONF_POWER,
    CONF_CHARGING_POWER,
    CONF_DISCHARGING_POWER,
    CONF_CELLS_NUMBER,
    CONF_REMAINING_CAPACITY,
    CONF_PACK_CAPACITY,
    CONF_TEMPERATURE_1,
    CONF_TEMPERATURE_2,
    CONF_TEMPERATURE_3,
    CONF_TEMPERATURE_4,
    CONF_TEMPERATURE_AMB,
    CONF_TEMPERATURE_BMS,
    CONF_CELL_01_VOLTAGE,
    CONF_CELL_02_VOLTAGE,
    CONF_CELL_03_VOLTAGE,
    CONF_CELL_04_VOLTAGE,
    CONF_CELL_05_VOLTAGE,
    CONF_CELL_06_VOLTAGE,
    CONF_CELL_07_VOLTAGE,
    CONF_CELL_08_VOLTAGE,
    CONF_CELL_09_VOLTAGE,
    CONF_CELL_10_VOLTAGE,
    CONF_CELL_11_VOLTAGE,
    CONF_CELL_12_VOLTAGE,
    CONF_CELL_13_VOLTAGE,
    CONF_CELL_14_VOLTAGE,
    CONF_CELL_15_VOLTAGE,
    CONF_CELL_16_VOLTAGE,
    CONF_CELL_DEVIATION,
]

CELL_VOLTAGE_SCHEMA = sensor.sensor_schema(
    unit_of_measurement=UNIT_VOLT,
    device_class=DEVICE_CLASS_VOLTAGE,
    state_class=STATE_CLASS_MEASUREMENT,
    icon="mdi:car-battery",
    accuracy_decimals=3,
)

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(CONF_BMS_SEPLOS_ID): cv.use_id(SeplosBmsComponent),
            cv.Optional(CONF_VOLTAGE): sensor.sensor_schema(
                unit_of_measurement=UNIT_VOLT,
                icon=ICON_FLASH,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_VOLTAGE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_CURRENT): sensor.sensor_schema(
                unit_of_measurement=UNIT_AMPERE,
                icon=ICON_CURRENT_DC,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_CURRENT,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_POWER): sensor.sensor_schema(
                unit_of_measurement=UNIT_WATT,
                icon=ICON_EMPTY,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_POWER,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_CHARGING_POWER): sensor.sensor_schema(
                unit_of_measurement=UNIT_WATT,
                icon=ICON_EMPTY,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_POWER,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_DISCHARGING_POWER): sensor.sensor_schema(
                unit_of_measurement=UNIT_WATT,
                icon=ICON_EMPTY,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_POWER,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_BATTERY_LEVEL): sensor.sensor_schema(
                unit_of_measurement=UNIT_PERCENT,
                icon="mdi:battery-plus-variant",
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_BATTERY,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PORT_VOLTAGE): sensor.sensor_schema(
                unit_of_measurement=UNIT_VOLT,
                icon=ICON_FLASH,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_VOLTAGE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_MAX_CELL_VOLTAGE): sensor.sensor_schema(
                unit_of_measurement=UNIT_VOLT,
                icon="mdi:battery-high",
                accuracy_decimals=3,
                device_class=DEVICE_CLASS_VOLTAGE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_MAX_CELL_VOLTAGE_NUMBER): sensor.sensor_schema(
                icon=ICON_COUNTER,
                accuracy_decimals=0,
            ),
            cv.Optional(CONF_CYCLE_COUNTER): sensor.sensor_schema(
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(CONF_MIN_CELL_VOLTAGE): sensor.sensor_schema(
                unit_of_measurement=UNIT_VOLT,
                icon="mdi:battery-low",
                accuracy_decimals=3,
                device_class=DEVICE_CLASS_VOLTAGE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_MIN_CELL_VOLTAGE_NUMBER): sensor.sensor_schema(
                icon=ICON_COUNTER,
                accuracy_decimals=0,
            ),
            cv.Optional(CONF_REMAINING_CAPACITY): sensor.sensor_schema(
                unit_of_measurement=UNIT_AMPERE_HOUR,
                icon=ICON_GAUGE,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_VOLTAGE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PACK_CAPACITY): sensor.sensor_schema(
                unit_of_measurement=UNIT_AMPERE_HOUR,
                icon=ICON_GAUGE,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_VOLTAGE,
                state_class=STATE_CLASS_MEASUREMENT,
                entity_category=ENTITY_CATEGORY_CONFIG,
            ),
            cv.Optional(CONF_CELLS_NUMBER): sensor.sensor_schema(
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                entity_category=ENTITY_CATEGORY_CONFIG,
            ),
            cv.Optional(CONF_TEMPERATURE_1): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(CONF_TEMPERATURE_2): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(CONF_TEMPERATURE_3): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(CONF_TEMPERATURE_4): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(CONF_TEMPERATURE_AMB): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(CONF_TEMPERATURE_BMS): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(CONF_CELL_01_VOLTAGE): CELL_VOLTAGE_SCHEMA,
            cv.Optional(CONF_CELL_02_VOLTAGE): CELL_VOLTAGE_SCHEMA,
            cv.Optional(CONF_CELL_03_VOLTAGE): CELL_VOLTAGE_SCHEMA,
            cv.Optional(CONF_CELL_04_VOLTAGE): CELL_VOLTAGE_SCHEMA,
            cv.Optional(CONF_CELL_05_VOLTAGE): CELL_VOLTAGE_SCHEMA,
            cv.Optional(CONF_CELL_06_VOLTAGE): CELL_VOLTAGE_SCHEMA,
            cv.Optional(CONF_CELL_07_VOLTAGE): CELL_VOLTAGE_SCHEMA,
            cv.Optional(CONF_CELL_08_VOLTAGE): CELL_VOLTAGE_SCHEMA,
            cv.Optional(CONF_CELL_09_VOLTAGE): CELL_VOLTAGE_SCHEMA,
            cv.Optional(CONF_CELL_10_VOLTAGE): CELL_VOLTAGE_SCHEMA,
            cv.Optional(CONF_CELL_11_VOLTAGE): CELL_VOLTAGE_SCHEMA,
            cv.Optional(CONF_CELL_12_VOLTAGE): CELL_VOLTAGE_SCHEMA,
            cv.Optional(CONF_CELL_13_VOLTAGE): CELL_VOLTAGE_SCHEMA,
            cv.Optional(CONF_CELL_14_VOLTAGE): CELL_VOLTAGE_SCHEMA,
            cv.Optional(CONF_CELL_15_VOLTAGE): CELL_VOLTAGE_SCHEMA,
            cv.Optional(CONF_CELL_16_VOLTAGE): CELL_VOLTAGE_SCHEMA,
            cv.Optional(CONF_CELL_DEVIATION): sensor.sensor_schema(
                unit_of_measurement=UNIT_VOLT,
                icon="mdi:battery-low",
                accuracy_decimals=3,
                device_class=DEVICE_CLASS_VOLTAGE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
        }
    ).extend(cv.COMPONENT_SCHEMA)
)


async def setup_conf(config, key, hub):
    if key in config:
        conf = config[key]
        sens = await sensor.new_sensor(conf)
        cg.add(getattr(hub, f"set_{key}_sensor")(sens))


async def to_code(config):
    hub = await cg.get_variable(config[CONF_BMS_SEPLOS_ID])
    for key in TYPES:
        await setup_conf(config, key, hub)
