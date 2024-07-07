
use arch.avr.avr5mcu;
use display.ssd1306;
use graphic.canvas8;

bind avr5mcu to globals.mmcu singleton;
bind avr5mcu to ssd1306.mmcu singleton;

bind avr5mcu.uart0 to globals.dbus_uart singleton;

// SPI display
bind avr5mcu.b0 to ssd1306.reset singleton;
bind avr5mcu.b1 to ssd1306.datacmd singleton;
bind avr5mcu.b2 to ssd1306.select singleton;
bind avr5mcu.spi to globals.dbus_display singleton;
bind avr5mcu.spi to ssd1306.dbus singleton;

bind ssd1306 to globals.oled singleton;
bind ssd1306.framebuffer to canvas8.buffer singleton;
