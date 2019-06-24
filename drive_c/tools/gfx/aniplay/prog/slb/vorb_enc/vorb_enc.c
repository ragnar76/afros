#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <mint/mintbind.h>
#include <mint/basepage.h>

void slb_vorbis_info_init(BASEPAGE *base, long fn, short nargs, vorbis_info *vi);
void slb_vorbis_info_clear(BASEPAGE *base, long fn, short nargs, vorbis_info *vi);
void slb_vorbis_comment_init(BASEPAGE *base, long fn, short nargs, vorbis_comment *vc);
void slb_vorbis_comment_add(BASEPAGE *base, long fn, short nargs, vorbis_comment *vc, char *comment); 
void slb_vorbis_comment_add_tag(BASEPAGE *base, long fn, short nargs, vorbis_comment *vc, char *tag, char *contents);
void slb_vorbis_comment_clear(BASEPAGE *base, long fn, short nargs, vorbis_comment *vc);
int slb_vorbis_block_init(BASEPAGE *base, long fn, short nargs, vorbis_dsp_state *v, vorbis_block *vb);
int slb_vorbis_block_clear(BASEPAGE *base, long fn, short nargs, vorbis_block *vb);
void slb_vorbis_dsp_clear(BASEPAGE *base, long fn, short nargs, vorbis_dsp_state *v);
int slb_vorbis_encode_init(BASEPAGE *base, long fn, short nargs, vorbis_info *vi, long channels, long rate, long max_bitrate, long nominal_bitrate, long min_bitrate);
int slb_vorbis_encode_init_vbr(BASEPAGE *base, long fn, short nargs, vorbis_info *vi, long channels, long rate, long quality);
int slb_vorbis_analysis_init(BASEPAGE *base, long fn, short nargs, vorbis_dsp_state *v, vorbis_info *vi);
int slb_vorbis_analysis_headerout(BASEPAGE *base, long fn, short nargs, vorbis_dsp_state *v, vorbis_comment *vc, ogg_packet *op, ogg_packet *op_comm, ogg_packet *op_code);
float **slb_vorbis_analysis_buffer(BASEPAGE *base, long fn, short nargs, vorbis_dsp_state *v,int vals);
int slb_vorbis_analysis_wrote(BASEPAGE *base, long fn, short nargs, vorbis_dsp_state *v,int vals);
int slb_vorbis_analysis_blockout(BASEPAGE *base, long fn, short nargs, vorbis_dsp_state *v, vorbis_block *vb);
int slb_vorbis_analysis(BASEPAGE *base, long fn, short nargs, vorbis_block *vb, ogg_packet *op);
int slb_ogg_stream_init(BASEPAGE *base, long fn, short nargs, ogg_stream_state *os, int serialno);
int slb_ogg_stream_clear(BASEPAGE *base, long fn, short nargs, ogg_stream_state *os);
int slb_ogg_page_eos(BASEPAGE *base, long fn, short nargs, ogg_page *og);
int slb_ogg_stream_packetin(BASEPAGE *base, long fn, short nargs, ogg_stream_state *os, ogg_packet *op);
int slb_ogg_stream_pageout(BASEPAGE *base, long fn, short nargs, ogg_stream_state *os, ogg_page *og);
int slb_ogg_stream_flush(BASEPAGE *base, long fn, short nargs, ogg_stream_state *os, ogg_page *og);

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

void slb_vorbis_info_init(BASEPAGE *base, long fn, short nargs, vorbis_info *vi)
{
	vorbis_info_init(vi);
}

void slb_vorbis_info_clear(BASEPAGE *base, long fn, short nargs, vorbis_info *vi)
{
	vorbis_info_clear(vi);
}

void slb_vorbis_comment_init(BASEPAGE *base, long fn, short nargs, vorbis_comment *vc)
{
	vorbis_comment_init(vc);
}

void slb_vorbis_comment_add(BASEPAGE *base, long fn, short nargs, vorbis_comment *vc, char *comment)
{
	vorbis_comment_add(vc, comment);
}

void slb_vorbis_comment_add_tag(BASEPAGE *base, long fn, short nargs, vorbis_comment *vc, char *tag, char *contents)
{
	vorbis_comment_add_tag(vc, tag, contents);
}

void slb_vorbis_comment_clear(BASEPAGE *base, long fn, short nargs, vorbis_comment *vc)
{
	vorbis_comment_clear(vc);
}

int slb_vorbis_block_init(BASEPAGE *base, long fn, short nargs, vorbis_dsp_state *v, vorbis_block *vb)
{
	return(vorbis_block_init(v, vb));
}

int slb_vorbis_block_clear(BASEPAGE *base, long fn, short nargs, vorbis_block *vb)
{
	return(vorbis_block_clear(vb));
}

void slb_vorbis_dsp_clear(BASEPAGE *base, long fn, short nargs, vorbis_dsp_state *v)
{
	vorbis_dsp_clear(v);
}

int slb_vorbis_encode_init(BASEPAGE *base, long fn, short nargs, vorbis_info *vi, long channels, long rate, long max_bitrate, long nominal_bitrate, long min_bitrate)
{
	return(vorbis_encode_init(vi, channels, rate, max_bitrate, nominal_bitrate, min_bitrate));
}

int slb_vorbis_encode_init_vbr(BASEPAGE *base, long fn, short nargs, vorbis_info *vi, long channels, long rate, long quality)
{
	return(vorbis_encode_init_vbr(vi, channels, rate, (float)quality/10.0));
}

int slb_vorbis_analysis_init(BASEPAGE *base, long fn, short nargs, vorbis_dsp_state *v, vorbis_info *vi)
{
	return(vorbis_analysis_init(v, vi));
}

int slb_vorbis_analysis_headerout(BASEPAGE *base, long fn, short nargs, vorbis_dsp_state *v, vorbis_comment *vc, ogg_packet *op, ogg_packet *op_comm, ogg_packet *op_code)
{
	return(vorbis_analysis_headerout(v, vc, op, op_comm, op_code));
}

float **slb_vorbis_analysis_buffer(BASEPAGE *base, long fn, short nargs, vorbis_dsp_state *v, int vals)
{
	return(vorbis_analysis_buffer(v, vals));
}

int slb_vorbis_analysis_wrote(BASEPAGE *base, long fn, short nargs, vorbis_dsp_state *v, int vals)
{
	return(vorbis_analysis_wrote(v, vals));
}

int slb_vorbis_analysis_blockout(BASEPAGE *base, long fn, short nargs, vorbis_dsp_state *v, vorbis_block *vb)
{
	return(vorbis_analysis_blockout(v, vb));
}

int slb_vorbis_analysis(BASEPAGE *base, long fn, short nargs, vorbis_block *vb, ogg_packet *op)
{
	return(vorbis_analysis(vb, op));
}

int slb_ogg_stream_init(BASEPAGE *base, long fn, short nargs, ogg_stream_state *os,int serialno)
{
	return(ogg_stream_init(os, serialno));
}

int slb_ogg_stream_clear(BASEPAGE *base, long fn, short nargs, ogg_stream_state *os)
{
	return(ogg_stream_clear(os));
}

int slb_ogg_page_eos(BASEPAGE *base, long fn, short nargs, ogg_page *og)
{
	return(ogg_page_eos(og));
}

int slb_ogg_stream_packetin(BASEPAGE *base, long fn, short nargs, ogg_stream_state *os, ogg_packet *op)
{
	return(ogg_stream_packetin(os, op));
}

int slb_ogg_stream_pageout(BASEPAGE *base, long fn, short nargs, ogg_stream_state *os, ogg_page *og)
{
	return(ogg_stream_pageout(os, og));
}

int slb_ogg_stream_flush(BASEPAGE *base, long fn, short nargs, ogg_stream_state *os, ogg_page *og)
{
	return(ogg_stream_flush(os, og));
}
