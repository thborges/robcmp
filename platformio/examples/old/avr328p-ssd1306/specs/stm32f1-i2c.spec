/*
 * Injections for a SSD1306 I2C display
 * and an stm32f103 mcu
 */

 bind stm32f1 to global_instances.mmcu singleton;
 bind stm32f1 to ssd1306.mmcu singleton;
 bind stm32f1.c13 to global_instances.led singleton;

 // I2C display
 bind null_digitalport to ssd1306.reset singleton;
 bind null_digitalport to ssd1306.datacmd singleton;
 bind null_digitalport to ssd1306.select singleton;
 bind stm32f1.i2c1 to global_instances.dbus singleton;
 bind stm32f1.i2c1 to ssd1306.dbus singleton;
 
 bind ssd1306 to global_instances.oled singleton;
 bind ssd1306.framebuffer to canvas8.buffer singleton;
 