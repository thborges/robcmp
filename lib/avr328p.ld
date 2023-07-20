/*
 * RobCmp linker script for atmega328p
 */

MEMORY
{
  text   (rx)   : ORIGIN = 0, LENGTH = 128K
  data   (rw!x) : ORIGIN = 0x800060, LENGTH = 0xffa0
  eeprom (rw!x) : ORIGIN = 0x810000, LENGTH = 64K
  fuse      (rw!x) : ORIGIN = 0x820000, LENGTH = 1K
  lock      (rw!x) : ORIGIN = 0x830000, LENGTH = 1K
  signature (rw!x) : ORIGIN = 0x840000, LENGTH = 1K
  user_signatures (rw!x) : ORIGIN = 0x850000, LENGTH = 1K
}

__vectors_size = 106; /* should be 104, but llvm ir requires a return at the end of __vectors*/

INCLUDE avr5.ld

