// Header for a "shared library"

	.text
	
	.globl	_slb_init
	.globl	_slb_open
	.globl	_slb_close
	.globl	_slb_close
	.globl	_slb_avcodec_init
	.globl	_slb_avcodec_register_all
	.globl	_slb_avcodec_find_decoder
	.globl	_slb_avcodec_find_encoder
	.globl	_slb_avcodec_find_decoder_by_name
	.globl	_slb_avcodec_string
	.globl	_slb_avcodec_open
	.globl	_slb_avcodec_decode_audio
	.globl	_slb_avcodec_decode_video
	.globl	_slb_avcodec_encode_audio
	.globl	_slb_avcodec_encode_video
	.globl	_slb_avcodec_close
	.globl	_slb_avcodec_version
	.globl	_slb_avcodec_alloc_context
	.globl	_slb_avcodec_alloc_frame

startup:
	
	.long	0x70004afc		// Magical value (5.20: $42674e41)
	.long	name		// Pointer to name of library
	.long	3		// Version number
	.long	0		// Flags, at present 0L
	.long	_slb_init		// Is called after loading
	.long	_slb_exit		// Is called before removing
	.long	_slb_open		// Is called at opening
	.long	_slb_close		// Is called at closing
	.long	0		// Pointer to procedure name (optional)
	.long	0,0,0,0,0,0,0,0	// Unused, always NULL
	.long	15		// Number of functions (5.20: .W)
	.long	_slb_avcodec_init	// Function #0
	.long	_slb_avcodec_register_all	// Function #1
	.long	_slb_avcodec_find_decoder	// Function #2
	.long	_slb_avcodec_find_encoder	// Function #3
	.long	_slb_avcodec_find_decoder_by_name	// Function #4
	.long	_slb_avcodec_string	// Function #5
	.long	_slb_avcodec_open	// Function #6
	.long	_slb_avcodec_decode_audio	// Function #7
	.long	_slb_avcodec_decode_video	// Function #8
	.long	_slb_avcodec_encode_audio	// Function #9
	.long	_slb_avcodec_encode_video	// Function #10
	.long	_slb_avcodec_close	// Function #11
	.long	_slb_avcodec_version	// Function #12
	.long	_slb_avcodec_alloc_context	// Function #13
	.long	_slb_avcodec_alloc_frame	// Function #14

name:	.asciz	"avcodec.slb"

