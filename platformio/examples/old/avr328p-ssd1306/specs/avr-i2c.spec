/*
 * Injections for a SSD1306 I2C display
 * and an Atmega328p mcu
 */

bind avr5mcu to global_instances.mmcu singleton;
bind avr5mcu to ssd1306.mmcu singleton;
bind avr5mcu.b5 to global_instances.led singleton;

// I2C display
bind null_digitalport to ssd1306.reset singleton;
bind null_digitalport to ssd1306.datacmd singleton;
bind null_digitalport to ssd1306.select singleton;
bind avr5mcu.i2c to global_instances.dbus singleton;
bind avr5mcu.i2c to ssd1306.dbus singleton;

bind ssd1306 to global_instances.oled singleton;
bind ssd1306.framebuffer to canvas8.buffer singleton;
