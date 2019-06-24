;here the SLB calls inside Aniplayer

SLB_AVCODEC_INIT:

 MOVEM.L D1-A6,-(SP)
 CLR -(SP);long word alignment for GCC
 MOVE #1,-(SP);number of the following arguments
 CLR.L -(SP);function 
 MOVE.L SHARED_LIB_AVCODEC,-(SP);descriptor
 MOVE.L SLB_EXEC_AVCODEC,A0
 JSR (A0)
 LEA 12(SP),SP
 MOVEM.L (SP)+,D1-A6
 RTS

SLB_AVCODEC_REGISTER_ALL:

 MOVEM.L D1-A6,-(SP)
 CLR -(SP);long word alignment for GCC
 MOVE #1,-(SP);number of the following arguments
 MOVE.L #1,-(SP);function 
 MOVE.L SHARED_LIB_AVCODEC,-(SP);descriptor
 MOVE.L SLB_EXEC_AVCODEC,A0
 JSR (A0)
 LEA 12(SP),SP
 MOVEM.L (SP)+,D1-A6
 RTS

SLB_AVCODEC_FIND_DECODER:;D0.L CodecID

 MOVEM.L D1-A6,-(SP)
 MOVE.L D0,-(SP);CodecID
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #2,-(SP);function 
 MOVE.L SHARED_LIB_AVCODEC,-(SP);descriptor
 MOVE.L SLB_EXEC_AVCODEC,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_AVCODEC_FIND_ENCODER:;D0.L CodecID

 MOVEM.L D1-A6,-(SP)
 MOVE.L D0,-(SP);CodecID
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #3,-(SP);function 
 MOVE.L SHARED_LIB_AVCODEC,-(SP);descriptor
 MOVE.L SLB_EXEC_AVCODEC,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_AVCODEC_FIND_DECODER_BY_NAME:;A0.L: name

 MOVEM.L D1-A6,-(SP)
 PEA (A0);name
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #4,-(SP);function 
 MOVE.L SHARED_LIB_AVCODEC,-(SP);descriptor
 MOVE.L SLB_EXEC_AVCODEC,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS 
 
SLB_AVCODEC_STRING:;D0.L: buf_size, D1: encode, A0: buf, A1: AVCodecContext

 MOVEM.L D1-A6,-(SP)
 MOVE.L D1,-(SP);encode
 PEA (A1);AVCodecContext
 MOVE.L D0,-(SP);buf_size
 PEA (A0);buf
 CLR -(SP);long word alignment for GCC
 MOVE #9,-(SP);number of the following arguments
 MOVE.L #5,-(SP);function 
 MOVE.L SHARED_LIB_AVCODEC,-(SP);descriptor
 MOVE.L SLB_EXEC_AVCODEC,A0
 JSR (A0)
 LEA 28(SP),SP
 MOVEM.L (SP)+,D1-A6
 RTS 

SLB_AVCODEC_OPEN:;A0: AVCodecContext, A1: AVCodec

 MOVEM.L D1-A6,-(SP)
 PEA (A1);AVCodec
 PEA (A0);AVCodecContext
 CLR -(SP);long word alignment for GCC
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #6,-(SP);function 
 MOVE.L SHARED_LIB_AVCODEC,-(SP);descriptor
 MOVE.L SLB_EXEC_AVCODEC,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS
 
SLB_AVCODEC_DECODE_AUDIO:;D0.L: buf_size, A0: AVCodecContext, A1: samples, A2: frame_size_ptr, A3: buf

 MOVEM.L D1-A6,-(SP)
 MOVE.L D0,-(SP);buf_size
 PEA (A3);buf
 PEA (A2);frame_size_ptr
 PEA (A1);samples
 PEA (A0);AVCodecContext
 CLR -(SP);long word alignment for GCC
 MOVE #11,-(SP);number of the following arguments
 MOVE.L #7,-(SP);function 
 MOVE.L SHARED_LIB_AVCODEC,-(SP);descriptor
 MOVE.L SLB_EXEC_AVCODEC,A0
 JSR (A0)
 LEA 32(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS 

SLB_AVCODEC_DECODE_VIDEO:;D0.L: buf_size, A0: AVCodecContext, A1: AVPicture, A2: got_picture_ptr, A3: buf

 MOVEM.L D1-A6,-(SP)
 MOVE.L D0,-(SP);buf_size
 PEA (A3);buf
 PEA (A2);got_picture_ptr
 PEA (A1);AVPicture
 PEA (A0);AVCodecContext
 CLR -(SP);long word alignment for GCC
 MOVE #11,-(SP);number of the following arguments
 MOVE.L #8,-(SP);function 
 MOVE.L SHARED_LIB_AVCODEC,-(SP);descriptor
 MOVE.L SLB_EXEC_AVCODEC,A0
 JSR (A0)
 LEA 32(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS  
 
SLB_AVCODEC_ENCODE_AUDIO:;D0.L: buf_size, A0: AVCodecContext, A1: buf, A2: samples

 MOVEM.L D1-A6,-(SP)
 PEA (A2);samples
 MOVE.L D0,-(SP);buf_size
 PEA (A1);buf
 PEA (A0);AVCodecContext
 CLR -(SP);long word alignment for GCC
 MOVE #9,-(SP);number of the following arguments
 MOVE.L #9,-(SP);function 
 MOVE.L SHARED_LIB_AVCODEC,-(SP);descriptor
 MOVE.L SLB_EXEC_AVCODEC,A0
 JSR (A0)
 LEA 28(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS 

SLB_AVCODEC_ENCODE_VIDEO:;D0.L: buf_size, A0: AVCodecContext, A1: buf, A2: AVPicture

 MOVEM.L D1-A6,-(SP)
 PEA (A2);AVPicture
 MOVE.L D0,-(SP);buf_size 
 PEA (A1);buf
 PEA (A0);AVCodecContext
 CLR -(SP);long word alignment for GCC
 MOVE #9,-(SP);number of the following arguments
 MOVE.L #10,-(SP);function 
 MOVE.L SHARED_LIB_AVCODEC,-(SP);descriptor
 MOVE.L SLB_EXEC_AVCODEC,A0
 JSR (A0)
 LEA 28(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS 

SLB_AVCODEC_CLOSE:;A0: AVCodecContext

 MOVEM.L D1-A6,-(SP)
 PEA (A0);AVCodecContext
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #11,-(SP);function 
 MOVE.L SHARED_LIB_AVCODEC,-(SP);descriptor
 MOVE.L SLB_EXEC_AVCODEC,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS
 
SLB_AVCODEC_VERSION:

 MOVEM.L D1-A6,-(SP)
 CLR -(SP);long word alignment for GCC
 MOVE #1,-(SP);number of the following arguments
 MOVE.L #12,-(SP);function 
 MOVE.L SHARED_LIB_AVCODEC,-(SP);descriptor
 MOVE.L SLB_EXEC_AVCODEC,A0
 JSR (A0)
 LEA 12(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS
 
SLB_AVCODEC_ALLOC_CONTEXT:

 MOVEM.L D1-A6,-(SP)
 CLR -(SP);long word alignment for GCC
 MOVE #1,-(SP);number of the following arguments
 MOVE.L #13,-(SP);function 
 MOVE.L SHARED_LIB_AVCODEC,-(SP);descriptor
 MOVE.L SLB_EXEC_AVCODEC,A0
 JSR (A0)
 LEA 12(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_AVCODEC_ALLOC_FRAME:

 MOVEM.L D1-A6,-(SP)
 CLR -(SP);long word alignment for GCC
 MOVE #1,-(SP);number of the following arguments
 MOVE.L #14,-(SP);function 
 MOVE.L SHARED_LIB_AVCODEC,-(SP);descriptor
 MOVE.L SLB_EXEC_AVCODEC,A0
 JSR (A0)
 LEA 12(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS
 
SLB_VORBIS_INFO_INIT:; A0: vi

 MOVEM.L D1-A6,-(SP)
 PEA (A0);vi
 CLR -(SP);number of the following arguments
 MOVE #3,-(SP);number of the following arguments
 CLR.L -(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 RTS

SLB_VORBIS_INFO_CLEAR:; A0: vi

 MOVEM.L D1-A6,-(SP)
 PEA (A0);vi
 CLR -(SP);number of the following arguments
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #1,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 :RTS

SLB_VORBIS_COMMENT_INIT:; A0: vc

 MOVEM.L D1-A6,-(SP)
 PEA (A0);vc
 CLR -(SP);number of the following arguments
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #2,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 RTS

SLB_VORBIS_COMMENT_ADD:; A0: vc, A1: comment

 MOVEM.L D1-A6,-(SP)
 PEA (A1);comment
 PEA (A0);vc
 CLR -(SP);number of the following arguments
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #3,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 RTS

SLB_VORBIS_COMMENT_ADD_TAG:; A0: vc, A1: tag, A2: contents

 MOVEM.L D1-A6,-(SP)
 PEA (A2);contents
 PEA (A1);tag
 PEA (A0);vc
 CLR -(SP);number of the following arguments
 MOVE #7,-(SP);number of the following arguments
 MOVE.L #4,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 24(SP),SP
 MOVEM.L (SP)+,D1-A6
 RTS
 
SLB_VORBIS_COMMENT_CLEAR:; A0: vc

 MOVEM.L D1-A6,-(SP)
 PEA (A0);vc
 CLR -(SP);number of the following arguments
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #5,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 RTS 

SLB_VORBIS_BLOCK_INIT:; A0: v, A1: vb

 MOVEM.L D1-A6,-(SP)
 PEA (A1);vb
 PEA (A0);v
 CLR -(SP);number of the following arguments
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #6,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS 
 
SLB_VORBIS_BLOCK_CLEAR:; A0: vb

 MOVEM.L D1-A6,-(SP)
 PEA (A0);vb
 CLR -(SP);number of the following arguments
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #7,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS 
 
SLB_VORBIS_DSP_CLEAR:; A0: v

 MOVEM.L D1-A6,-(SP)
 PEA (A0);v
 CLR -(SP);number of the following arguments
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #8,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 RTS 

SLB_VORBIS_ENCODE_INIT:; A0: vi, D0.L: channels, D1.L: rate, D2.L: max_bitrate, D3.L: nominal_bitrate, D4.L: min_bitrate

 MOVEM.L D1-A6,-(SP)
 MOVE.L D4,-(SP);min_bitrate
 MOVE.L D3,-(SP);nominal_bitrate
 MOVE.L D2,-(SP);max_bitrate
 MOVE.L D1,-(SP);rate
 MOVE.L D0,-(SP);channels
 PEA (A0);vi
 CLR -(SP);number of the following arguments
 MOVE #13,-(SP);number of the following arguments
 MOVE.L #9,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 36(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_VORBIS_ENCODE_INIT_VBR:; A0: vi, D0.L: channels, D1.L: rate, D2.L: quality

 MOVEM.L D1-A6,-(SP)
 MOVE.L D2,-(SP);quality
 MOVE.L D1,-(SP);rate
 MOVE.L D0,-(SP);channels
 PEA (A0);vi
 CLR -(SP);number of the following arguments
 MOVE #9,-(SP);number of the following arguments
 MOVE.L #10,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 28(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_VORBIS_ANALYSIS_INIT:; A0: v, A1: vi

 MOVEM.L D1-A6,-(SP)
 PEA (A1);vi
 PEA (A0);v
 CLR -(SP);number of the following arguments
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #11,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS 

SLB_VORBIS_ANALYSIS_HEADEROUT:; A0: v, A1: vc, A2: op, A3: op_mode, A4: op_code

 MOVEM.L D1-A6,-(SP)
 PEA (A4);op_code
 PEA (A3);op_mode
 PEA (A2);op
 PEA (A1);vc
 PEA (A0);v
 CLR -(SP);number of the following arguments
 MOVE #11,-(SP);number of the following arguments
 MOVE.L #12,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 32(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS 
 
SLB_VORBIS_ANALYSIS_BUFFER:; A0: v, D0.L: vals

 MOVEM.L D1-A6,-(SP)
 MOVE.L D0,-(SP);vals
 PEA (A0);v
 CLR -(SP);number of the following arguments
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #13,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS 
  
SLB_VORBIS_ANALYSIS_WROTE:; A0: v, D0.L: vals

 MOVEM.L D1-A6,-(SP)
 MOVE.L D0,-(SP);vals
 PEA (A0);v
 CLR -(SP);number of the following arguments
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #14,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS 
 
SLB_VORBIS_ANALYSIS_BLOCKOUT:; A0: v, A1: vb

 MOVEM.L D1-A6,-(SP)
 PEA (A1);vb
 PEA (A0);v
 CLR -(SP);number of the following arguments
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #15,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS 
 
SLB_VORBIS_ANALYSIS:; A0: vb, A1: op

 MOVEM.L D1-A6,-(SP)
 PEA (A1);op
 PEA (A0);vb
 CLR -(SP);number of the following arguments
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #16,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS 

SLB_OGG_STREAM_INIT:; A0: os, D0.L: serialno

 MOVEM.L D1-A6,-(SP)
 MOVE.L D0,-(SP);serialno
 PEA (A0);os
 CLR -(SP);number of the following arguments
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #17,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS 
 
SLB_OGG_STREAM_CLEAR:; A0: os

 MOVEM.L D1-A6,-(SP)
 PEA (A0);os
 CLR -(SP);number of the following arguments
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #18,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS  

SLB_OGG_PAGE_EOS:; A0: og

 MOVEM.L D1-A6,-(SP)
 PEA (A0);og
 CLR -(SP);number of the following arguments
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #19,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS   
 
SLB_OGG_STREAM_PACKETIN:; A0: os, A1: og

 MOVEM.L D1-A6,-(SP)
 PEA (A1);og
 PEA (A0);os
 CLR -(SP);number of the following arguments
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #20,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS  

SLB_OGG_STREAM_PAGEOUT:; A0: os, A1: og

 MOVEM.L D1-A6,-(SP)
 PEA (A1);og
 PEA (A0);os
 CLR -(SP);number of the following arguments
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #21,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS 
 
SLB_OGG_STREAM_FLUSH; A0: os, A1: og

 MOVEM.L D1-A6,-(SP)
 PEA (A1);og
 PEA (A0);os
 CLR -(SP);number of the following arguments
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #22,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS_ENC,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS_ENC,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS 
 
SLB_OV_CLEAR:; A0: vf

 MOVEM.L D1-A6,-(SP)
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 CLR.L -(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_OV_OPEN:; D0.L: handle, A0: vf, A1: initial, D1.L: ibytes

 MOVEM.L D1-A6,-(SP)
 MOVE.L D1,-(SP);ibytes
 PEA (A1);initial
 PEA (A0);vf
 MOVE.L D0,-(SP);handle
 CLR -(SP);long word alignment for GCC
 MOVE #9,-(SP);number of the following arguments
 MOVE.L #1,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 28(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_OV_OPEN_CALLBACKS:; D0.L: handle, A0: vf, A1: initial, D1.L: ibytes, A2: callbacks

 MOVEM.L D1-A6,-(SP)
 LEA -16(SP),SP
 MOVE.L (A2)+,(SP);callbacks
 MOVE.L (A2)+,4(SP)
 MOVE.L (A2)+,8(SP)
 MOVE.L (A2)+,12(SP)
 MOVE.L D1,-(SP);ibytes
 PEA (A1);initial
 PEA (A0);vf
 MOVE.L D0,-(SP);handle
 CLR -(SP);long word alignment for GCC
 MOVE #17,-(SP);number of the following arguments
 MOVE.L #2,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 44(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS
 
SLB_OV_BITRATE:; A0: vf, D0.L: i

 MOVEM.L D1-A6,-(SP)
 MOVE.L D0,-(SP);i
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #3,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_OV_BITRATE_INSTANT:; A0: vf

 MOVEM.L D1-A6,-(SP)
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #4,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_OV_STREAMS:; A0: vf

 MOVEM.L D1-A6,-(SP)
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #5,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_OV_SEEKABLE:; A0: vf

 MOVEM.L D1-A6,-(SP)
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #6,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_OV_RAW_TOTAL:; A0: vf, D0.L: i

 MOVEM.L D1-A6,-(SP)
 MOVE.L D0,-(SP);i
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #7,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS
 
SLB_OV_PCM_TOTAL:; A0: vf, D0.L: i

 MOVEM.L D1-A6,-(SP)
 MOVE.L D0,-(SP);i
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #8,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_OV_TIME_TOTAL:; A0: vf, D0.L: i

 MOVEM.L D1-A6,-(SP)
 MOVE.L D0,-(SP);i
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #9,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_OV_RAW_SEEK:; A0: vf, D0.L: pos

 MOVEM.L D1-A6,-(SP)
 MOVE.L D0,-(SP);pos
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #10,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_OV_PCM_SEEK:; A0: vf, D0.L: pos

 MOVEM.L D1-A6,-(SP)
 MOVE.L D0,-(SP);pos
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #11,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_OV_PCM_SEEK_PAGE:; A0: vf, D0.L: pos

 MOVEM.L D1-A6,-(SP)
 MOVE.L D0,-(SP);pos
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #12,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_OV_PCM_TIME_SEEK:; A0: vf, D0.L: pos en secondes

 MOVEM.L D1-A6,-(SP)
 MOVE.L D0,-(SP);pos
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #13,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_OV_PCM_TIME_SEEK_PAGE:; A0: vf, D0.L: pos en secondes

 MOVEM.L D1-A6,-(SP)
 MOVE.L D0,-(SP);pos
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #14,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_OV_RAW_TELL:; A0: vf

 MOVEM.L D1-A6,-(SP)
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #15,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_OV_PCM_TELL:; A0: vf

 MOVEM.L D1-A6,-(SP)
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #16,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_OV_PCM_TIME_TELL:; A0: vf

 MOVEM.L D1-A6,-(SP)
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #17,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 16(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_VORBIS_INFO:; A0: vf, D0.L: link

 MOVEM.L D1-A6,-(SP)
 MOVE.L D0,-(SP);link
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #18,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_VORBIS_COMMENT:; A0: vf, D0.L: link

 MOVEM.L D1-A6,-(SP)
 MOVE.L D0,-(SP);link
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #19,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 20(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS

SLB_OV_READ:; A0: vf, A1: buffer, D0: length, A2: bitstream

 MOVEM.L D1-A6,-(SP)
 PEA (A2);bitstream
 MOVE.L #1,-(SP);signed
 MOVE.L #2,-(SP);word (16 bits)
 MOVE.L #1,-(SP);bigendianp
 MOVE.L D0,-(SP);length
 PEA (A1);buffer
 PEA (A0);vf
 CLR -(SP);long word alignment for GCC
 MOVE #15,-(SP);number of the following arguments
 MOVE.L #20,-(SP);function 
 MOVE.L SHARED_LIB_VORBIS,-(SP);descriptor
 MOVE.L SLB_EXEC_VORBIS,A0
 JSR (A0)
 LEA 40(SP),SP
 MOVEM.L (SP)+,D1-A6
 TST.L D0
 RTS
 
SLB_JPEG_STD_ERROR:; A0: err

 PEA (A0);err
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 CLR.L -(SP);function 
 MOVE.L SHARED_LIB_JPEG,-(SP);descriptor
 MOVE.L SLB_EXEC_JPEG,A0
 JSR (A0)
 LEA 16(SP),SP
 TST.L D0
 RTS
 
SLB_JPEG_CREATE_COMPRESS:; A0: cinfo

 PEA (A0);cinfo
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #1,-(SP);function 
 MOVE.L SHARED_LIB_JPEG,-(SP);descriptor
 MOVE.L SLB_EXEC_JPEG,A0
 JSR (A0)
 LEA 16(SP),SP
 RTS
 
SLB_JPEG_STDIO_DEST:; A0: cinfo, D0.L: handle

 MOVE.L D0,-(SP);handle
 PEA (A0);cinfo
 CLR -(SP);long word alignment for GCC
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #2,-(SP);function 
 MOVE.L SHARED_LIB_JPEG,-(SP);descriptor
 MOVE.L SLB_EXEC_JPEG,A0
 JSR (A0)
 LEA 20(SP),SP
 RTS

SLB_JPEG_SET_DEFAULTS:; A0: cinfo

 PEA (A0);cinfo
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #3,-(SP);function 
 MOVE.L SHARED_LIB_JPEG,-(SP);descriptor
 MOVE.L SLB_EXEC_JPEG,A0
 JSR (A0)
 LEA 16(SP),SP
 RTS 
 
SLB_JPEG_SET_QUALITY:; A0: cinfo, D0.L: quality, D1.L: force_baseline 

 MOVE.L D1,-(SP);force_baseline
 MOVE.L D0,-(SP);quality
 PEA (A0);cinfo
 CLR -(SP);long word alignment for GCC
 MOVE #7,-(SP);number of the following arguments
 MOVE.L #4,-(SP);function 
 MOVE.L SHARED_LIB_JPEG,-(SP);descriptor
 MOVE.L SLB_EXEC_JPEG,A0
 JSR (A0)
 LEA 24(SP),SP
 RTS  

SLB_JPEG_START_COMPRESS:; A0: cinfo, D0.L: write_all_tables

 MOVE.L D0,-(SP);write_all_tables
 PEA (A0);cinfo
 CLR -(SP);long word alignment for GCC
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #5,-(SP);function 
 MOVE.L SHARED_LIB_JPEG,-(SP);descriptor
 MOVE.L SLB_EXEC_JPEG,A0
 JSR (A0)
 LEA 20(SP),SP
 RTS  

SLB_JPEG_WRITE_SCANLINES:; A0: cinfo, A1: scanlines, D0.L: numlines

 MOVE.L D0,-(SP);numlines
 PEA (A1);scanlines
 PEA (A0);cinfo
 CLR -(SP);long word alignment for GCC
 MOVE #7,-(SP);number of the following arguments
 MOVE.L #6,-(SP);function 
 MOVE.L SHARED_LIB_JPEG,-(SP);descriptor
 MOVE.L SLB_EXEC_JPEG,A0
 JSR (A0)
 LEA 24(SP),SP
 TST.L D0
 RTS

SLB_JPEG_FINISH_COMPRESS:; A0: cinfo

 PEA (A0);cinfo
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #7,-(SP);function 
 MOVE.L SHARED_LIB_JPEG,-(SP);descriptor
 MOVE.L SLB_EXEC_JPEG,A0
 JSR (A0)
 LEA 16(SP),SP
 RTS
 
SLB_JPEG_DESTROY_COMPRESS:; A0: cinfo

 PEA (A0);cinfo
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #8,-(SP);function 
 MOVE.L SHARED_LIB_JPEG,-(SP);descriptor
 MOVE.L SLB_EXEC_JPEG,A0
 JSR (A0)
 LEA 16(SP),SP
 RTS
 
SLB_JPEG_CREATE_DECOMPRESS:; A0: cinfo

 PEA (A0);cinfo
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #9,-(SP);function 
 MOVE.L SHARED_LIB_JPEG,-(SP);descriptor
 MOVE.L SLB_EXEC_JPEG,A0
 JSR (A0)
 LEA 16(SP),SP
 TST.L D0
 RTS

SLB_JPEG_STDIO_SRC:; A0: cinfo, D0.L: handle

 MOVE.L D0,-(SP);handle
 PEA (A0);cinfo
 CLR -(SP);long word alignment for GCC
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #10,-(SP);function 
 MOVE.L SHARED_LIB_JPEG,-(SP);descriptor
 MOVE.L SLB_EXEC_JPEG,A0
 JSR (A0)
 LEA 20(SP),SP
 RTS

SLB_JPEG_READ_HEADER:; A0: cinfo, D0.L: require_image

 MOVE.L D0,-(SP);require_image
 PEA (A0);cinfo
 CLR -(SP);long word alignment for GCC
 MOVE #5,-(SP);number of the following arguments
 MOVE.L #11,-(SP);function 
 MOVE.L SHARED_LIB_JPEG,-(SP);descriptor
 MOVE.L SLB_EXEC_JPEG,A0
 JSR (A0)
 LEA 20(SP),SP
 TST.L D0
 RTS
 
SLB_JPEG_START_DECOMPRESS:; A0: cinfo

 PEA (A0);cinfo
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #12,-(SP);function 
 MOVE.L SHARED_LIB_JPEG,-(SP);descriptor
 MOVE.L SLB_EXEC_JPEG,A0
 JSR (A0)
 LEA 16(SP),SP
 TST.L D0
 RTS  

SLB_JPEG_READ_SCANLINES:; A0: cinfo, A1: scanlines, D0.L: max_lines

 MOVE.L D0,-(SP);max_lines
 PEA (A1);scanlines
 PEA (A0);cinfo
 CLR -(SP);long word alignment for GCC
 MOVE #7,-(SP);number of the following arguments
 MOVE.L #13,-(SP);function 
 MOVE.L SHARED_LIB_JPEG,-(SP);descriptor
 MOVE.L SLB_EXEC_JPEG,A0
 JSR (A0)
 LEA 24(SP),SP
 TST.L D0
 RTS

SLB_JPEG_FINISH_DECOMPRESS:; A0: cinfo

 PEA (A0);cinfo
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #14,-(SP);function 
 MOVE.L SHARED_LIB_JPEG,-(SP);descriptor
 MOVE.L SLB_EXEC_JPEG,A0
 JSR (A0)
 LEA 16(SP),SP
 TST.L D0
 RTS
 
SLB_JPEG_DESTROY_DECOMPRESS:; A0: cinfo

 PEA (A0);cinfo
 CLR -(SP);long word alignment for GCC
 MOVE #3,-(SP);number of the following arguments
 MOVE.L #15,-(SP);function 
 MOVE.L SHARED_LIB_JPEG,-(SP);descriptor
 MOVE.L SLB_EXEC_JPEG,A0
 JSR (A0)
 LEA 16(SP),SP
 RTS

SLB_DECORE:; D0.L: handle, D1.L: dec_opt, A0: param1, A1: param2

 PEA (A1);param2
 PEA (A0);param1
 MOVE.L D1,-(SP);dec_opt
 MOVE.L D0,-(SP);handle
 CLR -(SP);long word alignment for GCC
 MOVE #9,-(SP);number of the following arguments
 CLR.L -(SP);function 
 MOVE.L SHARED_LIB_OPENDIVX,-(SP);descriptor
 MOVE.L SLB_EXEC_OPENDIVX,A0
 JSR (A0)
 LEA 28(SP),SP
 EXT.L D0
 RTS

 