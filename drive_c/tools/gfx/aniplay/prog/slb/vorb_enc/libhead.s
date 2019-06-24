// Header for a "shared library"

	.text
	
	.globl	_slb_init
	.globl	_slb_open
	.globl	_slb_close
	.globl	_slb_close
	.globl	_slb_vorbis_info_init	// Function #0
	.globl	_slb_vorbis_info_clear	// Function #1
	.globl	_slb_vorbis_comment_init	// Function #2
	.globl	_slb_vorbis_comment_add	// Function #3
	.globl	_slb_vorbis_comment_add_tag	// Function #4
	.globl	_slb_vorbis_comment_clear	// Function #5
	.globl	_slb_vorbis_block_init	// Function #6
	.globl	_slb_vorbis_block_clear	// Function #7
	.globl	_slb_vorbis_dsp_clear	// Function #8
	.globl	_slb_vorbis_encode_init	// Function #9
	.globl	_slb_vorbis_encode_init_vbr	// Function #10
	.globl	_slb_vorbis_analysis_init	// Function #11
	.globl	_slb_vorbis_analysis_headerout	// Function #12
	.globl	_slb_vorbis_analysis_buffer	// Function #13
	.globl	_slb_vorbis_analysis_wrote 	// Function #14
	.globl	_slb_vorbis_analysis_blockout	// Function #15
	.globl	_slb_vorbis_analysis	// Function #16
	.globl	_slb_ogg_stream_init   	// Function #17
	.globl	_slb_ogg_stream_clear    	// Function #18
	.globl	_slb_ogg_page_eos	// Function #19
	.globl	_slb_ogg_stream_packetin	// Function #20
	.globl	_slb_ogg_stream_pageout	// Function #21
	.globl	_slb_ogg_stream_flush	// Function #22

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
	.long	23		// Number of functions (5.20: .W)
	.long	_slb_vorbis_info_init	// Function #0
	.long	_slb_vorbis_info_clear	// Function #1
	.long	_slb_vorbis_comment_init	// Function #2
	.long	_slb_vorbis_comment_add	// Function #3
	.long	_slb_vorbis_comment_add_tag	// Function #4
	.long	_slb_vorbis_comment_clear	// Function #5
	.long	_slb_vorbis_block_init	// Function #6
	.long	_slb_vorbis_block_clear	// Function #7
	.long	_slb_vorbis_dsp_clear	// Function #8
	.long	_slb_vorbis_encode_init	// Function #9
	.long	_slb_vorbis_encode_init_vbr	// Function #10
	.long	_slb_vorbis_analysis_init	// Function #11
	.long	_slb_vorbis_analysis_headerout	// Function #12
	.long	_slb_vorbis_analysis_buffer	// Function #13
	.long	_slb_vorbis_analysis_wrote 	// Function #14
	.long	_slb_vorbis_analysis_blockout	// Function #15
	.long	_slb_vorbis_analysis	// Function #16
	.long	_slb_ogg_stream_init   	// Function #17         
	.long	_slb_ogg_stream_clear    	// Function #18
	.long	_slb_ogg_page_eos	// Function #19
	.long	_slb_ogg_stream_packetin	// Function #20
	.long	_slb_ogg_stream_pageout	// Function #21
	.long	_slb_ogg_stream_flush	// Function #22

name:	.asciz	"vorb_enc.slb"

