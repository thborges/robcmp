/*
 * RobCmp linker script for avr5 familly
 */

OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:5)

SECTIONS
{
  .text : AT (0x0) {
  	_start__vectors = .;
	KEEP(*(.vectors))
	. = ALIGN(2);
	_end_vectors = .;
	_stext = .;
     *(.progmem*)
    . = ALIGN(2);
    *(.text)
    . = ALIGN(2);
    *(.text.*)
	. = ALIGN(2);
     _etext = . ;
  }

  .data : AT (ADDR(.text) + SIZEOF(.text)) {
     PROVIDE (__data_start = .) ;
    *(.data)
    *(.data*)
    *(.rodata)  /* We need to include .rodata here if gcc is used */
    *(.rodata*) /* with -fdata-sections.  */
    . = ALIGN(2);
     PROVIDE (__data_end = .) ;
  }  > data

  .bss : AT (ADDR (.bss)) {
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
  .debug_pubtypes 1 : { *(.debug_pubtypes) }
  .debug_ranges   1 : { *(.debug_ranges) }
  /* DWARF Extension.  */
  .debug_macro    1 : { *(.debug_macro) }
}

