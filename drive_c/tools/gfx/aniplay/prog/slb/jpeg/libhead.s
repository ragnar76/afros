// Header for a "shared library"

	.text
	
	.globl	_slb_init
	.globl	_slb_open
	.globl	_slb_close
	.globl	_slb_close
	.globl	_slb_jpeg_std_error
	.globl	_slb_jpeg_create_compress
	.globl	_slb_jpeg_stdio_dest
	.globl	_slb_jpeg_set_defaults
	.globl	_slb_jpeg_set_quality
	.globl	_slb_jpeg_start_compress		
	.globl	_slb_jpeg_write_scanlines
	.globl	_slb_jpeg_finish_compress
	.globl	_slb_jpeg_destroy_compress
	.globl	_slb_jpeg_create_decompress
	.globl	_slb_jpeg_stdio_src
	.globl	_slb_jpeg_read_header
	.globl	_slb_jpeg_start_decompress
	.globl	_slb_jpeg_read_scanlines
	.globl	_slb_jpeg_finish_decompress
	.globl	_slb_jpeg_destroy_decompress

startup:
	
	.long	0x70004afc		// Magical value (5.20: $42674e41)
	.long	name		// Pointer to name of library
	.long	1		// Version number
	.long	0		// Flags, at present 0L
	.long	_slb_init		// Is called after loading
	.long	_slb_exit		// Is called before removing
	.long	_slb_open		// Is called at opening
	.long	_slb_close		// Is called at closing
	.long	0		// Pointer to procedure name (optional)
	.long	0,0,0,0,0,0,0,0	// Unused, always NULL
	.long	16		// Number of functions (5.20: .W)
	.long	_slb_jpeg_std_error	// Function #0
	.long	_slb_jpeg_create_compress	// Function #1
	.long	_slb_jpeg_stdio_dest	// Function #2
	.long	_slb_jpeg_set_defaults	// Function #3
	.long	_slb_jpeg_set_quality	// Function #4
	.long	_slb_jpeg_start_compress	// Function #5
	.long	_slb_jpeg_write_scanlines	// Function #6
	.long	_slb_jpeg_finish_compress	// Function #7
	.long	_slb_jpeg_destroy_compress// Function #8
	.long	_slb_jpeg_create_decompress  // Function #9
	.long	_slb_jpeg_stdio_src	// Function #10
	.long	_slb_jpeg_read_header	// Function #11
	.long	_slb_jpeg_start_decompress// Function #12
	.long	_slb_jpeg_read_scanlines	// Function #13
	.long	_slb_jpeg_finish_decompress  // Function #14
	.long	_slb_jpeg_destroy_decompress // Function #15

name:	.asciz	"jpeg.slb"

