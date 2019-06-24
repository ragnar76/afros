#include <osbind.h>
#include <stdio.h>
#include "jpeglib.h"
#include "slb.h"

#define slb_jpeg_std_error(jerr)	(struct jpeg_error_mgr *)(*slbexec)(slb, 0L, (short)3, (short)0, (struct jpeg_error_mgr *)jerr)
#define slb_jpeg_create_compress(cinfo)	(void)(*slbexec)(slb, 1L, (short)3, (short)0, (j_compress_ptr) cinfo)
#define slb_jpeg_stdio_dest(cinfo, handle)	(void)(*slbexec)(slb, 2L, (short)5, (short)0, (j_compress_ptr)cinfo, (long)handle)
#define slb_jpeg_set_defaults(cinfo)	(void)(*slbexec)(slb, 3L, (short)3, (short)0, (j_compress_ptr)cinfo)
#define slb_jpeg_set_quality(cinfo, quality, force_baseline)	(void)(*slbexec)(slb, 4L, (short)7, (short)0, (j_compress_ptr)cinfo, (long)quality, (long)force_baseline)
#define slb_jpeg_start_compress(cinfo, write_all_tables)	(void)(*slbexec)(slb, 5L, (short)5, (short)0, (j_compress_ptr)cinfo, (long)write_all_tables)
#define slb_jpeg_write_scanlines(cinfo, scanlines, num_lines)	(JDIMENSION)(*slbexec)(slb, 6L, (short)7, (short)0, (j_compress_ptr)cinfo, (JSAMPARRAY)scanlines, (long)num_lines)
#define slb_jpeg_finish_compress(cinfo)	(void)(*slbexec)(slb, 7L, (short)3, (short)0, (j_compress_ptr *)cinfo)
#define slb_jpeg_destroy_compress(cinfo)	(void)(*slbexec)(slb, 8L, (short)3, (short)0, (j_compress_ptr)cinfo)
#define slb_jpeg_create_decompress(cinfo)	(void)(*slbexec)(slb, 9L, (short)3, (short)0, (j_compress_ptr)cinfo)
#define slb_jpeg_stdio_src(cinfo, handle)	(void)(*slbexec)(slb, 10L, (short)5, (short)0, (j_decompress_ptr)cinfo, (long)handle)
#define slb_jpeg_read_header(cinfo, require_image)	(int)(*slbexec)(slb, 11L, (short)5, (short)0, (j_decompress_ptr)cinfo, (long)require_image)
#define slb_jpeg_start_decompress(cinfo)	(boolean)(*slbexec)(slb, 12L, (short)3, (short)0, (j_decompress_ptr)cinfo)
#define slb_jpeg_read_scanlines(cinfo, scanlines, max_lines)	(JDIMENSION)(*slbexec)(slb, 13L, (short)7, (short)0, (j_decompress_ptr)cinfo, (JSAMPARRAY)scanlines, (long)max_lines)
#define slb_jpeg_finish_decompress(cinfo)	(boolean)(*slbexec)(slb, 14L, 3L, (short)0, (j_decompress_ptr)cinfo)
#define slb_jpeg_destroy_decompress(cinfo)	(void)(*slbexec)(slb, 15L, (short)3, (short)0, (j_decompress_ptr)cinfo)

SLB_EXEC     slbexec;
SHARED_LIB   slb;

extern JSAMPLE * image_buffer;	/* Points to large array of R,G,B-order data */
extern int image_height;	/* Number of rows in image */
extern int image_width;		/* Number of columns in image */
extern void	put_scanline_someplace(JSAMPARRAY buffer, int row_stride);

void write_JPEG_file (char * filename, int quality)
{
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	long handle;
	JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
	int row_stride;		/* physical row width in image buffer */

	if(Slbopen("JPEG.SLB", ".\\", 1L, &slb, &slbexec) >= 0)
	{  
		if((handle = Fcreate(filename, 0)) >= 0)
  		{
			cinfo.err = slb_jpeg_std_error(&jerr);
			slb_jpeg_create_compress(&cinfo);
			slb_jpeg_stdio_dest(&cinfo, handle);
			cinfo.image_width = image_width; 	/* image width and height, in pixels */
			cinfo.image_height = image_height;
			cinfo.input_components = 3;		/* # of color components per pixel */
			cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
			slb_jpeg_set_defaults(&cinfo);
			slb_jpeg_set_quality(&cinfo, quality, TRUE );
			slb_jpeg_start_compress(&cinfo, TRUE);
			row_stride = image_width * 3;	/* JSAMPLEs per row in image_buffer */
			while(cinfo.next_scanline < cinfo.image_height)
			{
				row_pointer[0] = & image_buffer[cinfo.next_scanline * row_stride];
				(void)slb_jpeg_write_scanlines(&cinfo, row_pointer, 1);
			}
			slb_jpeg_finish_compress(&cinfo);
			slb_jpeg_destroy_compress(&cinfo);
			Fclose(handle);
		}
		Slbclose(slb);		
	}
}

void read_JPEG_file (char * filename)
{
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	long handle;
	JSAMPARRAY buffer;		/* Output row buffer */
	int row_stride;		/* physical row width in output buffer */

	if(Slbopen("JPEG.SLB", ".\\", 1L, &slb, &slbexec) >= 0)
	{  
	  if((handle = Fopen(filename, 0)) >= 0)
	  {
			cinfo.err = slb_jpeg_std_error(&jerr);
			slb_jpeg_create_decompress(&cinfo);
			slb_jpeg_stdio_src(&cinfo, handle);
			(void)slb_jpeg_read_header(&cinfo, TRUE);
			(void)slb_jpeg_start_decompress(&cinfo);
			row_stride = cinfo.output_width * cinfo.output_components;
			buffer = (*cinfo.mem->alloc_sarray) ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
			while(cinfo.output_scanline < cinfo.output_height)
			{
				(void)slb_jpeg_read_scanlines(&cinfo, buffer, 1);
				put_scanline_someplace(buffer, row_stride);
			}
			(void)slb_jpeg_finish_decompress(&cinfo);
			slb_jpeg_destroy_decompress(&cinfo);
			Fclose(handle);
		}
		Slbclose(slb);		
	}
}
