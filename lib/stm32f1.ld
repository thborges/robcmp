MEMORY
{
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128K
	RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

__reset_stack_pointer = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
	.isr_vector : {
		_start = .;
		LONG(__reset_stack_pointer);		
		LONG(__isr_reset | 1);
		LONG(__isr_nmi | 1);
		/* The interrupt table is 332 bytes long. Advance to that position. */
		. = ORIGIN(FLASH) + 332;
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
