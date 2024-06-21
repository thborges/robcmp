/*
 * Injections for a SSD1306 SPI display
 * and an Atmega328p mcu
 */

bind avr5mcu to global_instances.mmcu singleton;
bind avr5mcu to ssd1306.mmcu singleton;
bind avr5mcu.b5 to global_instances.led singleton;

// SPI display
bind avr5mcu.b0 to ssd1306.reset singleton;
bind avr5mcu.b1 to ssd1306.datacmd singleton;
bind avr5mcu.b2 to ssd1306.select singleton;
bind avr5mcu.spi to global_instances.dbus singleton;
bind avr5mcu.spi to ssd1306.dbus singleton;

bind ssd1306 to global_instances.oled singleton;
bind ssd1306.framebuffer to canvas8.buffer singleton;