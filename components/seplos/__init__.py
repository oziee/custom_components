import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID

DEPENDENCIES = ['uart']
AUTO_LOAD = ['sensor', 'text_sensor']

seplos_ns = cg.esphome_ns.namespace('seplos')
SeplosComponent = seplos_ns.class_('SeplosComponent', uart.UARTDevice, cg.Component)

CONF_SEPLOS_ID = "seplos_id"

CONFIG_SCHEMA = uart.UART_DEVICE_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(SeplosComponent),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)