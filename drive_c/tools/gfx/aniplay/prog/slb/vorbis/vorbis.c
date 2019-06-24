#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>
#include <mint/mintbind.h>
#include <mint/basepage.h>

int slb_ov_clear(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf);
int slb_ov_open(BASEPAGE *base, long fn, short nargs,int f,OggVorbis_File *vf,char *initial,long ibytes);
int slb_ov_open_callbacks(BASEPAGE *base, long fn, short nargs,int f,OggVorbis_File *vf,char *initial,long ibytes,ov_callbacks callbacks);
long slb_ov_bitrate(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,int i);
long slb_ov_bitrate_instant(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf);
long slb_ov_streams(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf);
long slb_ov_seekable(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf);
long slb_ov_raw_total(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,int i);
long slb_ov_pcm_total(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,int i);
long slb_ov_time_total(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,int i);
int slb_ov_raw_seek(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,long pos);
int slb_ov_pcm_seek(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,long pos);
int slb_ov_pcm_seek_page(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,long pos);
int slb_ov_time_seek(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,long pos);
int slb_ov_time_seek_page(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,long pos);
long slb_ov_raw_tell(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf);
long slb_ov_pcm_tell(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf);
long slb_ov_time_tell(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf);
vorbis_info *slb_ov_info(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,int link);
vorbis_comment *slb_ov_comment(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,int link);
long slb_ov_read(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,char *buffer,int length,int bigendianp,int word,int sgned,int *bitstream);

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

int slb_ov_clear(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf)
{
	return(ov_clear(vf));
}

int slb_ov_open(BASEPAGE *base, long fn, short nargs,int f,OggVorbis_File *vf,char *initial,long ibytes)
{
	return(ov_open(f,vf,initial,ibytes));
}

int slb_ov_open_callbacks(BASEPAGE *base, long fn, short nargs,int f, OggVorbis_File *vf, char *initial, long ibytes, ov_callbacks callbacks)
{
	return(ov_open_callbacks(f,vf,initial,ibytes,callbacks));
}

long slb_ov_bitrate(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,int i)
{
	return(ov_bitrate(vf,i));
}

long slb_ov_bitrate_instant(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf)
{
	return(ov_bitrate_instant(vf));
}

long slb_ov_streams(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf)
{
	return(ov_streams(vf));
}

long slb_ov_seekable(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf)
{
	return(ov_seekable(vf));
}

long slb_ov_raw_total(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,int i)
{
	return((long)ov_raw_total(vf,i));
}

long slb_ov_pcm_total(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,int i)
{
	return((long)ov_pcm_total(vf,i));
}

long slb_ov_time_total(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,int i)
{
	return((long)ov_time_total(vf,i));
}

int slb_ov_raw_seek(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,long pos)
{
	return(ov_raw_seek(vf,pos));
}

int slb_ov_pcm_seek(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,long pos)
{
	return(ov_pcm_seek(vf,(ogg_int64_t)pos));
}

int slb_ov_pcm_seek_page(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,long pos)
{
	return(ov_pcm_seek_page(vf,(ogg_int64_t)pos));
}

int slb_ov_time_seek(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,long pos)
{
	return(ov_time_seek(vf,(double)pos));
}

int slb_ov_time_seek_page(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,long pos)
{
	return(ov_time_seek_page(vf,(double)pos));
}

long slb_ov_raw_tell(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf)
{
	return((long)ov_raw_tell(vf));
}

long slb_ov_pcm_tell(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf)
{
	return((long)ov_pcm_tell(vf));
}

long slb_ov_time_tell(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf)
{
	return((long)ov_time_tell(vf));
}

vorbis_info *slb_ov_info(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,int link)
{
	return(ov_info(vf,link));
}

vorbis_comment *slb_ov_comment(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,int link)
{
	return(ov_comment(vf,link));
}

long slb_ov_read(BASEPAGE *base, long fn, short nargs,OggVorbis_File *vf,char *buffer,int length,int bigendianp,int word,int sgned,int *bitstream)
{
	return(ov_read(vf,buffer,length,bigendianp,word,sgned,bitstream));
}
