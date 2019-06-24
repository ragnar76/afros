#include "jinclude.h"
#include "jpeglib.h"
#include <mint/mintbind.h>
#include <mint/basepage.h>

struct jpeg_error_mgr * slb_jpeg_std_error(BASEPAGE *base, long fn, short nargs, struct jpeg_error_mgr * err);
void slb_jpeg_create_compress(BASEPAGE *base, long fn, short nargs, j_compress_ptr cinfo);
void slb_jpeg_stdio_dest(BASEPAGE *base, long fn, short nargs, j_compress_ptr cinfo, long handle);
void slb_jpeg_set_defaults(BASEPAGE *base, long fn, short nargs, j_compress_ptr cinfo);
void slb_jpeg_set_quality(BASEPAGE *base, long fn, short nargs, j_compress_ptr cinfo, int quality, boolean force_baseline);
void slb_jpeg_start_compress(BASEPAGE *base, long fn, short nargs, j_compress_ptr cinfo, boolean write_all_tables);
JDIMENSION slb_jpeg_write_scanlines(BASEPAGE *base, long fn, short nargs, j_compress_ptr cinfo, JSAMPARRAY scanlines, JDIMENSION num_lines);
void slb_jpeg_finish_compress(BASEPAGE *base, long fn, short nargs, j_compress_ptr cinfo);
void slb_jpeg_destroy_compress(BASEPAGE *base, long fn, short nargs, j_compress_ptr cinfo);
void slb_jpeg_create_decompress(BASEPAGE *base, long fn, short nargs, j_decompress_ptr cinfo);
void slb_jpeg_stdio_src(BASEPAGE *base, long fn, short nargs, j_decompress_ptr cinfo, long handle);
int slb_jpeg_read_header(BASEPAGE *base, long fn, short nargs, j_decompress_ptr cinfo, boolean require_image);
boolean slb_jpeg_start_decompress(BASEPAGE *base, long fn, short nargs, j_decompress_ptr cinfo);
JDIMENSION slb_jpeg_read_scanlines(BASEPAGE *base, long fn, short nargs, j_decompress_ptr cinfo, JSAMPARRAY scanlines, JDIMENSION max_lines);
boolean	slb_jpeg_finish_decompress(BASEPAGE *base, long fn, short nargs, j_decompress_ptr cinfo);
void slb_jpeg_destroy_decompress(BASEPAGE *base, long fn, short nargs, j_decompress_ptr cinfo);

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

struct jpeg_error_mgr * slb_jpeg_std_error(BASEPAGE *base, long fn, short nargs, struct jpeg_error_mgr * err)
{
		return(jpeg_std_error(err));
}

void slb_jpeg_create_compress(BASEPAGE *base, long fn, short nargs, j_compress_ptr cinfo)
{
	jpeg_create_compress(cinfo);
}

void slb_jpeg_stdio_dest(BASEPAGE *base, long fn, short nargs, j_compress_ptr cinfo, long handle)
{
	jpeg_stdio_dest(cinfo,(FILE *)handle);
}

void slb_jpeg_set_defaults(BASEPAGE *base, long fn, short nargs, j_compress_ptr cinfo)
{
	jpeg_set_defaults(cinfo);
}

void slb_jpeg_set_quality(BASEPAGE *base, long fn, short nargs, j_compress_ptr cinfo, int quality, boolean force_baseline)
{
	jpeg_set_quality(cinfo,quality,force_baseline);
}

void slb_jpeg_start_compress(BASEPAGE *base, long fn, short nargs, j_compress_ptr cinfo, boolean write_all_tables)
{
	jpeg_start_compress(cinfo,write_all_tables);
}

JDIMENSION slb_jpeg_write_scanlines(BASEPAGE *base, long fn, short nargs, j_compress_ptr cinfo, JSAMPARRAY scanlines, JDIMENSION num_lines)
{
	return(jpeg_write_scanlines(cinfo,scanlines,num_lines));
}

void slb_jpeg_finish_compress(BASEPAGE *base, long fn, short nargs, j_compress_ptr cinfo)
{
	jpeg_finish_compress(cinfo);
}

void slb_jpeg_destroy_compress(BASEPAGE *base, long fn, short nargs, j_compress_ptr cinfo)
{
	jpeg_destroy_compress(cinfo);
}

void slb_jpeg_create_decompress(BASEPAGE *base, long fn, short nargs, j_decompress_ptr cinfo)
{
	jpeg_create_decompress(cinfo);
}

void slb_jpeg_stdio_src(BASEPAGE *base, long fn, short nargs, j_decompress_ptr cinfo, long handle)
{
	jpeg_stdio_src(cinfo,(FILE *)handle);
}

int slb_jpeg_read_header(BASEPAGE *base, long fn, short nargs, j_decompress_ptr cinfo, boolean require_image)
{
	return(jpeg_read_header(cinfo,require_image));
}

boolean slb_jpeg_start_decompress(BASEPAGE *base, long fn, short nargs, j_decompress_ptr cinfo)
{
	return(jpeg_start_decompress(cinfo));
}

JDIMENSION slb_jpeg_read_scanlines(BASEPAGE *base, long fn, short nargs, j_decompress_ptr cinfo, JSAMPARRAY scanlines, JDIMENSION max_lines)
{
	return(jpeg_read_scanlines(cinfo,scanlines,max_lines));
}

boolean	slb_jpeg_finish_decompress(BASEPAGE *base, long fn, short nargs, j_decompress_ptr cinfo)
{
	return(jpeg_finish_decompress(cinfo));
}

void slb_jpeg_destroy_decompress(BASEPAGE *base, long fn, short nargs, j_decompress_ptr cinfo)
{
	jpeg_destroy_decompress(cinfo);
}
