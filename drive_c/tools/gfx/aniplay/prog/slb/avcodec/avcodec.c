#include "avcodec.h"
#include <mint/mintbind.h>
#include <mint/basepage.h>

void slb_avcodec_init(BASEPAGE *base, long fn, short nargs);
void slb_avcodec_register_all(BASEPAGE *base, long fn, short nargs);
AVCodec *slb_avcodec_find_decoder(BASEPAGE *base, long fn, short nargs, enum CodecID id);
AVCodec *slb_avcodec_find_encoder(BASEPAGE *base, long fn, short nargs, enum CodecID id);
AVCodec *slb_avcodec_find_decoder_by_name(BASEPAGE *base, long fn, short nargs, const char *name);
void slb_avcodec_string(BASEPAGE *base, long fn, short nargs, char *buf, int buf_size, AVCodecContext *enc, int encode);
int slb_avcodec_open(BASEPAGE *base, long fn, short nargs, AVCodecContext *avctx, AVCodec *codec);
int slb_avcodec_decode_audio(BASEPAGE *base, long fn, short nargs, AVCodecContext *avctx, int16_t *samples, int *frame_size_ptr, uint8_t *buf, int buf_size);
int slb_avcodec_decode_video(BASEPAGE *base, long fn, short nargs, AVCodecContext *avctx, AVFrame *picture, int *got_picture_ptr, uint8_t *buf, int buf_size);
int slb_avcodec_encode_audio(BASEPAGE *base, long fn, short nargs, AVCodecContext *avctx, uint8_t *buf, int buf_size, const short *samples);
int slb_avcodec_encode_video(BASEPAGE *base, long fn, short nargs, AVCodecContext *avctx, uint8_t *buf, int buf_size, const AVFrame *pict);
int slb_avcodec_close(BASEPAGE *base, long fn, short nargs, AVCodecContext *avctx);
int slb_avcodec_version(BASEPAGE *base, long fn, short nargs);
AVCodecContext *slb_avcodec_alloc_context(BASEPAGE *base, long fn, short nargs);
AVFrame *slb_avcodec_alloc_frame(BASEPAGE *base, long fn, short nargs);

static long open_count = 0 ;

long slb_init(void)
{
	return(0L);
}

void slb_exit(void)
{
}

long slb_open(BASEPAGE *base)
{
	if(base);
	open_count++;
	return(0L);
}

void slb_close(BASEPAGE *base)
{
	if(base);
	open_count--;
}

void slb_avcodec_init(BASEPAGE *base, long fn, short nargs)
{
	avcodec_init();
}

void slb_avcodec_register_all(BASEPAGE *base, long fn, short nargs)
{
	avcodec_register_all();
}

AVCodec *slb_avcodec_find_decoder(BASEPAGE *base, long fn, short nargs, enum CodecID id)
{
	return(avcodec_find_decoder(id));
}

AVCodec *slb_avcodec_find_encoder(BASEPAGE *base, long fn, short nargs, enum CodecID id)
{
	return(avcodec_find_encoder(id));
}

AVCodec *slb_avcodec_find_decoder_by_name(BASEPAGE *base, long fn, short nargs, const char *name)
{
	return(avcodec_find_decoder_by_name(name));
}

void slb_avcodec_string(BASEPAGE *base, long fn, short nargs, char *buf, int buf_size, AVCodecContext *enc, int encode)
{
	avcodec_string(buf,buf_size,enc,encode);
}

int slb_avcodec_open(BASEPAGE *base, long fn, short nargs, AVCodecContext *avctx, AVCodec *codec)
{
	return(avcodec_open(avctx,codec));
}

int slb_avcodec_decode_audio(BASEPAGE *base, long fn, short nargs, AVCodecContext *avctx, int16_t *samples, int *frame_size_ptr, uint8_t *buf, int buf_size)
{
	return(avcodec_decode_audio(avctx,samples,frame_size_ptr,buf,buf_size));
}

int slb_avcodec_decode_video(BASEPAGE *base, long fn, short nargs, AVCodecContext *avctx, AVFrame *picture, int *got_picture_ptr, uint8_t *buf, int buf_size)
{
	return(avcodec_decode_video(avctx,picture,got_picture_ptr,buf,buf_size));
}

int slb_avcodec_encode_audio(BASEPAGE *base, long fn, short nargs, AVCodecContext *avctx, uint8_t *buf, int buf_size, const short *samples)
{
	return(avcodec_encode_audio(avctx,buf,buf_size,samples));
}

int slb_avcodec_encode_video(BASEPAGE *base, long fn, short nargs, AVCodecContext *avctx, uint8_t *buf, int buf_size, const AVFrame *pict)
{
	return(avcodec_encode_video(avctx,buf,buf_size,pict));
}

int slb_avcodec_close(BASEPAGE *base, long fn, short nargs, AVCodecContext *avctx)
{
	return(avcodec_close(avctx));
}

int slb_avcodec_version(BASEPAGE *base, long fn, short nargs)
{
#ifdef LIBAVCODEC_VERSION_INT
	return(LIBAVCODEC_VERSION_INT);
#else
	return(0);
#endif
}

AVCodecContext *slb_avcodec_alloc_context(BASEPAGE *base, long fn, short nargs)
{
	return(avcodec_alloc_context());
}

AVFrame *slb_avcodec_alloc_frame(BASEPAGE *base, long fn, short nargs)
{
	return(avcodec_alloc_frame());
}
