/*
 * RobCmp linker script for atmega328p
 */

MEMORY
{
  text   (rx)   : ORIGIN = 0, LENGTH = 32K
  data   (rw!x) : ORIGIN = 0x800100, LENGTH = 2K 
  eeprom (rw!x) : ORIGIN = 0x810000, LENGTH = 1K
  fuse      (rw!x) : ORIGIN = 0x820000, LENGTH = 1K
  lock      (rw!x) : ORIGIN = 0x830000, LENGTH = 1K
  signature (rw!x) : ORIGIN = 0x840000, LENGTH = 1K
  user_signatures (rw!x) : ORIGIN = 0x850000, LENGTH = 1K
}

INCLUDE avr5.ld

