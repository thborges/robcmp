/* Default linker script, for normal executables */
/* Copyright (C) 2014 Free Software Foundation, Inc.
   Copying and distribution of this script, with or without modification,
   are permitted in any medium without royalty provided the copyright
   notice and this notice are preserved.  */

OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")

OUTPUT_ARCH(avr:5)

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

SECTIONS
{
  .text : {
  	_start__vectors = .;
	KEEP(*(.vectors))
	. = 106; /* should be 104, but llvm requires a return at the end of __vectors*/
	_end_vectors = .;
	. = ALIGN(2);
	_stext = .;
     *(.progmem*)
    . = ALIGN(2);
    *(.text)
    . = ALIGN(2);
    *(.text.*)
     _etext = . ;
  }  > text

  .data : {
     PROVIDE (__data_start = .) ;
    *(.data)
    *(.data*)
    *(.rodata)  /* We need to include .rodata here if gcc is used */
    *(.rodata*) /* with -fdata-sections.  */
    . = ALIGN(2);
     _edata = . ;
     PROVIDE (__data_end = .) ;
  }  > data AT> text

  .bss  ADDR(.data) + SIZEOF (.data)   : AT (ADDR (.bss)) {
     PROVIDE (__bss_start = .) ;
    *(.bss)
     *(.bss*)
    *(COMMON)
     PROVIDE (__bss_end = .) ;
  }  > data

   __data_load_start = LOADADDR(.data);
   __data_load_end = __data_load_start + SIZEOF(.data);
  
  /* Global data not cleared after reset.  */
  .eeprom  : {
    KEEP(*(.eeprom*))
     __eeprom_end = . ;
  } > eeprom

  .fuse  : {
    KEEP(*(.fuse))
    KEEP(*(.lfuse))
    KEEP(*(.hfuse))
    KEEP(*(.efuse))
  } > fuse

  .lock  : {
    KEEP(*(.lock*))
  } > lock

  .signature  : {
    KEEP(*(.signature*))
  } > signature

  .user_signatures  : {
    KEEP(*(.user_signatures*))
  } > user_signatures

  /* DWARF 3 */
  .debug_pubtypes 0 : { *(.debug_pubtypes) }
  .debug_ranges   0 : { *(.debug_ranges) }
  /* DWARF Extension.  */
  .debug_macro    0 : { *(.debug_macro) }
}
