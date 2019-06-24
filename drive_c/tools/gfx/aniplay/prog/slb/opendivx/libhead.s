// Header for a "shared library"

	.text
	
	.globl	_slb_init
	.globl	_slb_open
	.globl	_slb_close
	.globl	_slb_close
	.globl	_slb_decore

startup:
	
	.long	0x70004afc		// Magical value (5.20: $42674e41)
	.long	name		// Pointer to name of library
	.long	2		// Version number
	.long	0		// Flags, at present 0L
	.long	_slb_init		// Is called after loading
	.long	_slb_exit		// Is called before removing
	.long	_slb_open		// Is called at opening
	.long	_slb_close		// Is called at closing
	.long	0		// Pointer to procedure name (optional)
	.long	0,0,0,0,0,0,0,0	// Unused, always NULL
	.long	1		// Number of functions (5.20: .W)
	.long	_slb_decore		// Function #0

name:	.asciz	"opendivx.slb"

