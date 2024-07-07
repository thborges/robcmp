/*
 * RobCmp linker script for avr5 familly
 */

OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:5)

SECTIONS
{
  .text : {
    _start = .;
    *(__isr)
	  KEEP(*(__isr))
	  . = ALIGN(2);
	  __text_start = .;
    *(__irqs)
    KEEP(*(__irqs))
    *(.progmem*)
    . = ALIGN(2);
    *(.text)
    . = ALIGN(2);
    *(.text.*)
	  . = ALIGN(2);
    __text_end = . ;
  } > text

  .data : {
     __data_start = .;
    *(.data)
    *(.data.*)
    KEEP(*(.rodata))
    KEEP(*(.rodata.*))
    __data_end = .;
  }  > data AT> text

  .bss ADDR(.data) + SIZEOF(.data) : AT (ADDR (.bss)) {
    __bss_start = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    __bss_end = .;
  }  > data

   __data_load_start = LOADADDR(.data);
  
  /* will robcmp emits .noinit data? i.e., global vars uninitialized. 
     this also provides __heap_start, for when we implement malloc.
  */
  .noinit  ADDR(.bss) + SIZEOF(.bss) : AT (ADDR (.noinit)) {
    __noinit_start = .;
    *(.noinit*)
    __noinit_end = .;
    __heap_start = .;
  } > data

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

