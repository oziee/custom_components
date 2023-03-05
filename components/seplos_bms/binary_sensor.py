import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from . import SeplosBmsComponent, CONF_BMS_SEPLOS_ID
from esphome.const import ENTITY_CATEGORY_DIAGNOSTIC


CONF_CHARGING_MOS_ENABLED = "charging_mos_enabled"
CONF_DISCHARGING_MOS_ENABLED = "discharging_mos_enabled"
CONF_CURRENT_LIMITING_ENABLED = "current_limiting_enabled"
CONF_HEATING_ENABLED = "heating_enabled"
CONST_VOLTAGE_SENSOR_FAILURE = "voltage_sensor_failure"
CONST_TEMP_SENSOR_FAILURE = "temp_sensor_failure"
CONST_CURRENT_SENSOR_FAILURE = "current_sensor_failure"
CONST_BUTTON_FAILURE = "button_failure"
CONST_VOLTAGE_DIFFERENCE_FAILURE = "voltage_difference_failure"
CONST_CHARGE_SWITCH_FAILURE = "charge_switch_failure"
CONST_DISCHARGE_SWITCH_FAILURE = "discharge_switch_failure"
CONST_CURRENT_LIMITING_FAILURE = "current_limiting_failure"
CONST_OV_CELL_WARNING = "ov_cell_warning"
CONST_OV_CELL_PROTECT = "ov_cell_protect"
CONST_UV_CELL_WARNING = "uv_cell_warning"
CONST_UV_CELL_PROTECT = "uv_cell_protect"
CONST_OV_PACK_WARNING = "ov_pack_warning"
CONST_OV_PACK_PROTECT = "ov_pack_protect"
CONST_UV_PACK_WARNING = "uv_pack_warning"
CONST_UV_PACK_PROTECT = "uv_pack_protect"
CONST_OT_CHARGE_WARNING = "ot_charge_warning"
CONST_OT_CHARGE_PROTECT = "ot_charge_protect"
CONST_UT_CHARGE_WARNING = "ut_charge_warning"
CONST_UT_CHARGE_PROTECT = "ut_charge_protect"
CONST_OT_DISCHARGE_WARNING = "ot_discharge_warning"
CONST_OT_DISCHARGE_PROTECT = "ot_discharge_protect"
CONST_UT_DISCHARGE_WARNING = "ut_discharge_warning"
CONST_UT_DISCHARGE_PROTECT = "ut_discharge_protect"
CONST_OT_AMB_WARNING = "ot_amb_warning"
CONST_OT_AMB_PROTECT = "ot_amb_protect"
CONST_UT_AMB_WARNING = "ut_amb_warning"
CONST_UT_AMB_PROTECT = "ut_amb_protect"
CONST_OT_BMS_WARNING = "ot_bms_warning"
CONST_OT_BMS_PROTECT = "ot_bms_protect"
CONST_UT_HEATING = "ut_heating"
CONST_OC_CHARGE_WARNING = "oc_charge_warning"
CONST_OC_CHARGE_PROTECT = "oc_charge_protect"
CONST_OC_DISCHARGE_WARNING = "oc_discharge_warning"
CONST_OC_DISCHARGE_PROTECT = "oc_discharge_protect"
CONST_OC_TRANSIENT_PROTECT = "oc_transient_protect"
CONST_SC_OUTPUT_CURRENT_PROTECT = "sc_output_current_protect"
CONST_OC_TRANSIENT_LOCK = "oc_transient_lock"
CONST_SC_OUTPUT_CURRENT_LOCK = "sc_output_current_lock"
CONST_OV_CHARGE_PROTECT = "ov_charge_protect"
CONST_POWER_SUPPLY_WAITING = "power_supply_waiting"
CONST_REMAINING_CAPACITY_WARNING = "remaining_capacity_warning"
CONST_REMAINING_CAPACITY_PROTECT = "remaining_capacity_protect"
CONST_UV_CELL_STOP_CHARGING_WARNING = "uv_cell_stop_charging_warning"
CONST_REVERSE_POLARITY_PROTECT = "reverse_polarity_protect"
CONST_OUTPUT_CONNECTION_FAILURE = "output_connection_failure"
CONST_INTERNAL_BIT = "internal_bit"


TYPES = [
    CONF_CHARGING_MOS_ENABLED,
    CONF_DISCHARGING_MOS_ENABLED,
    CONF_CURRENT_LIMITING_ENABLED,
    CONF_HEATING_ENABLED,
    CONST_VOLTAGE_SENSOR_FAILURE,
    CONST_TEMP_SENSOR_FAILURE,
    CONST_CURRENT_SENSOR_FAILURE,
    CONST_BUTTON_FAILURE,
    CONST_VOLTAGE_DIFFERENCE_FAILURE,
    CONST_CHARGE_SWITCH_FAILURE,
    CONST_DISCHARGE_SWITCH_FAILURE,
    CONST_CURRENT_LIMITING_FAILURE,
    CONST_OV_CELL_WARNING,
    CONST_OV_CELL_PROTECT,
    CONST_UV_CELL_WARNING,
    CONST_UV_CELL_PROTECT,
    CONST_OV_PACK_WARNING,
    CONST_OV_PACK_PROTECT,
    CONST_UV_PACK_WARNING,
    CONST_UV_PACK_PROTECT,
    CONST_OT_CHARGE_WARNING,
    CONST_OT_CHARGE_PROTECT,
    CONST_UT_CHARGE_WARNING,
    CONST_UT_CHARGE_PROTECT,
    CONST_OT_DISCHARGE_WARNING,
    CONST_OT_DISCHARGE_PROTECT,
    CONST_UT_DISCHARGE_WARNING,
    CONST_UT_DISCHARGE_PROTECT,
    CONST_OT_AMB_WARNING,
    CONST_OT_AMB_PROTECT,
    CONST_UT_AMB_WARNING,
    CONST_UT_AMB_PROTECT,
    CONST_OT_BMS_WARNING,
    CONST_OT_BMS_PROTECT,
    CONST_UT_HEATING,
    CONST_OC_CHARGE_WARNING,
    CONST_OC_CHARGE_PROTECT,
    CONST_OC_DISCHARGE_WARNING,
    CONST_OC_DISCHARGE_PROTECT,
    CONST_OC_TRANSIENT_PROTECT,
    CONST_SC_OUTPUT_CURRENT_PROTECT,
    CONST_OC_TRANSIENT_LOCK,
    CONST_SC_OUTPUT_CURRENT_LOCK,
    CONST_OV_CHARGE_PROTECT,
    CONST_POWER_SUPPLY_WAITING,
    CONST_REMAINING_CAPACITY_WARNING,
    CONST_REMAINING_CAPACITY_PROTECT,
    CONST_UV_CELL_STOP_CHARGING_WARNING,
    CONST_REVERSE_POLARITY_PROTECT,
    CONST_OUTPUT_CONNECTION_FAILURE,
    CONST_INTERNAL_BIT,
]

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(CONF_BMS_SEPLOS_ID): cv.use_id(SeplosBmsComponent),
            cv.Optional(
                CONF_CHARGING_MOS_ENABLED
            ): binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONF_DISCHARGING_MOS_ENABLED
            ): binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONF_CURRENT_LIMITING_ENABLED
            ): binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONF_HEATING_ENABLED
            ): binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_VOLTAGE_SENSOR_FAILURE
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_TEMP_SENSOR_FAILURE
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_CURRENT_SENSOR_FAILURE
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_BUTTON_FAILURE
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_VOLTAGE_DIFFERENCE_FAILURE
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_CHARGE_SWITCH_FAILURE
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_DISCHARGE_SWITCH_FAILURE
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_CURRENT_LIMITING_FAILURE
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OV_CELL_WARNING
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OV_CELL_PROTECT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_UV_CELL_WARNING
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_UV_CELL_PROTECT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OV_PACK_WARNING
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OV_PACK_PROTECT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_UV_PACK_WARNING
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_UV_PACK_PROTECT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OT_CHARGE_WARNING
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OT_CHARGE_PROTECT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_UT_CHARGE_WARNING
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_UT_CHARGE_PROTECT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OT_DISCHARGE_WARNING
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OT_DISCHARGE_PROTECT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_UT_DISCHARGE_WARNING
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_UT_DISCHARGE_PROTECT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OT_AMB_WARNING
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OT_AMB_PROTECT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_UT_AMB_WARNING
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_UT_AMB_PROTECT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OT_BMS_WARNING
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OT_BMS_PROTECT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_UT_HEATING
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OC_CHARGE_WARNING
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OC_CHARGE_PROTECT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OC_DISCHARGE_WARNING
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OC_DISCHARGE_PROTECT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OC_TRANSIENT_PROTECT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_SC_OUTPUT_CURRENT_PROTECT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OC_TRANSIENT_LOCK
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_SC_OUTPUT_CURRENT_LOCK
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OV_CHARGE_PROTECT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_POWER_SUPPLY_WAITING
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_REMAINING_CAPACITY_WARNING
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_REMAINING_CAPACITY_PROTECT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_UV_CELL_STOP_CHARGING_WARNING
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_REVERSE_POLARITY_PROTECT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_OUTPUT_CONNECTION_FAILURE
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(
                CONST_INTERNAL_BIT
            ):binary_sensor.binary_sensor_schema(
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
        }
    ).extend(cv.COMPONENT_SCHEMA)
)


async def setup_conf(config, key, hub):
    if key in config:
        conf = config[key]
        var = await binary_sensor.new_binary_sensor(conf)
        cg.add(getattr(hub, f"set_{key}_binary_sensor")(var))


async def to_code(config):
    hub = await cg.get_variable(config[CONF_BMS_SEPLOS_ID])
    for key in TYPES:
        await setup_conf(config, key, hub)
