MEMORY
{
	FLASH (rx) : ORIGIN = 0x10000000, LENGTH = 2M
	RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 264K
}

__reset_stack_pointer = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
    .boot2 : {
        __boot2_start__ = .;
        KEEP (*(.boot2))
        __boot2_end__ = .;
    } > FLASH
    
	ASSERT(__boot2_end__ - __boot2_start__ == 256,
        "ERROR: Pico second stage bootloader must be 256 bytes in size")

	.isr_vector : {
		__isr_start = .;
		LONG(__reset_stack_pointer);		
		LONG(__isr_reset | 1);
		LONG(__error_handler | 1); /*isr nmi */
		LONG(__error_handler | 1); /*HardFault_Handler*/
		LONG(0);
		LONG(0);
		LONG(0);
		LONG(0);
		LONG(0);
		LONG(__error_handler | 1); /*SVCall_Handler*/
		LONG(0);
		LONG(0);
		LONG(__error_handler | 1); /*PendSV_Handler*/
		LONG(__error_handler | 1); /*SysTick_Handler*/

		/* The interrupt table is 192 bytes long. Advance to that position. */
		. = __isr_start + 192;
	} > FLASH


	.text : {
		. = ALIGN(4);
		*(.text)
		*(.text.*)
		*(.rodata)
		*(.rodata.*)
		. = ALIGN(4);
	} > FLASH

	__data_init = LOADADDR(.data);

    .data : {
		__data_start = .;
		*(.data)
		*(.data.*)
		. = ALIGN(4);
		__data_end = .;
	} > RAM AT> FLASH
	
	.bss : 
	{
		__bss_start = .;
		*(.bss)
		*(.bss.*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end = .;
	} > RAM

	.ARM.attributes 0 : { *(.ARM.attributes) }
}
