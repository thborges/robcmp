/*
 * Injections for a SSD1306 I2C display
 * and an stm32f103 mcu
 */
 
use arch.stm32.stm32f1;
use display.ssd1306;
use graphic.canvas8;

bind stm32f1 to globals.mmcu singleton;
bind stm32f1 to ssd1306.mmcu singleton;
bind stm32f1.uart2 to globals.dbus_uart singleton;

// I2C display
bind void_digitalport to ssd1306.reset singleton;
bind void_digitalport to ssd1306.datacmd singleton;
bind void_digitalport to ssd1306.select singleton;
bind stm32f1.i2c1 to globals.dbus_display singleton;
bind stm32f1.i2c1 to ssd1306.dbus singleton;

bind ssd1306 to globals.oled singleton;
bind ssd1306.framebuffer to canvas8.buffer singleton;
