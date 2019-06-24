// Header for a "shared library"

	.text
	
	.globl	_slb_init
	.globl	_slb_open
	.globl	_slb_close
	.globl	_slb_close
	.globl	_slb_ov_clear
	.globl	_slb_ov_open
	.globl	_slb_ov_open_callbacks
	.globl	_slb_ov_bitrate
	.globl	_slb_ov_bitrate_instant
	.globl	_slb_ov_streams
	.globl	_slb_ov_seekable
	.globl	_slb_ov_raw_total
	.globl	_slb_ov_pcm_total
	.globl	_slb_ov_time_total
	.globl	_slb_ov_raw_seek
	.globl	_slb_ov_pcm_seek
	.globl	_slb_ov_pcm_seek_page
	.globl	_slb_ov_time_seek
	.globl	_slb_ov_time_seek_page
	.globl	_slb_ov_raw_tell
	.globl	_slb_ov_pcm_tell
	.globl	_slb_ov_time_tell
	.globl	_slb_ov_info
	.globl	_slb_ov_comment
	.globl	_slb_ov_read	

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
	.long	21		// Number of functions (5.20: .W)
	.long	_slb_ov_clear	// Function #0
	.long	_slb_ov_open		// Function #1
	.long	_slb_ov_open_callbacks	// Function #2
	.long	_slb_ov_bitrate	// Function #3
	.long	_slb_ov_bitrate_instant	// Function #4
	.long	_slb_ov_streams	// Function #5
	.long	_slb_ov_seekable	// Function #6
	.long	_slb_ov_raw_total	// Function #7
	.long	_slb_ov_pcm_total	// Function #8
	.long	_slb_ov_time_total	// Function #9
	.long	_slb_ov_raw_seek	// Function #10
	.long	_slb_ov_pcm_seek	// Function #11
	.long	_slb_ov_pcm_seek_page 	// Function #12
	.long	_slb_ov_time_seek	// Function #13
	.long	_slb_ov_time_seek_page	// Function #14
	.long	_slb_ov_raw_tell   	// Function #15
	.long	_slb_ov_pcm_tell        	// Function #16
	.long	_slb_ov_time_tell	// Function #17
	.long	_slb_ov_info		// Function #18
	.long	_slb_ov_comment	// Function #19
	.long	_slb_ov_read		// Function #20

name:	.asciz	"vorbis.slb"

