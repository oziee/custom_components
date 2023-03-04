import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, text_sensor, uart
from esphome.const import CONF_ID, DEVICE_CLASS_EMPTY
from . import seplos_ns, SeplosComponent, CONF_SEPLOS_ID

# sensors


# text sensors
CONF_CHARGER_TEXT = "charger_text"


CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(CONF_SEPLOS_ID): cv.use_id(SeplosComponent),
    #cv.Optional(CONF_CHARGER_TEXT): text_sensor.TEXT_SENSOR_SCHEMA.extend({cv.GenerateID(): cv.declare_id(text_sensor.TextSensor)}),
})

async def to_code(config):
    seplos = await cg.get_variable(config[CONF_SEPLOS_ID])

    
    if CONF_CHARGER_TEXT in config:
        conf = config[CONF_CHARGER_TEXT]
        sens = cg.new_Pvariable(conf[CONF_ID])
        await text_sensor.register_text_sensor(sens, conf)
        cg.add(seplos.set_charger_text_sensor(sens))
