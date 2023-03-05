import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor
from . import SeplosBmsComponent, CONF_BMS_SEPLOS_ID

CONF_BMS_STATUS = "bms_status"

TYPES = [
    CONF_BMS_STATUS,
]


CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(CONF_BMS_SEPLOS_ID): cv.use_id(SeplosBmsComponent),
            cv.Optional(CONF_BMS_STATUS): text_sensor.text_sensor_schema(
                icon="mdi:dip-switch"
            ),
        }
    ).extend(cv.COMPONENT_SCHEMA)
)


async def setup_conf(config, key, hub):
    if key in config:
        conf = config[key]
        sens = await text_sensor.new_text_sensor(conf)
        cg.add(getattr(hub, f"set_{key}_text_sensor")(sens))


async def to_code(config):
    hub = await cg.get_variable(config[CONF_BMS_SEPLOS_ID])
    for key in TYPES:
        await setup_conf(config, key, hub)
