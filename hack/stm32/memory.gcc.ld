MEMORY
{
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128K
	RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

__reset_stack_pointer = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
	.text : {
		/* Set the initial address to 0 */
		. = 0x0;
		LONG(__reset_stack_pointer);
		LONG(main | 1);
		/* The whole interrupt table is 332 bytes long. Advance to that position. */
		. = 332;
		/* And here comes the rest of the code */
		*(.text*)
	} > FLASH /* Put this in the flash memory region */
}

