/* 
 * png2raw 
 * Decompresses 32bit png data to raw.
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <zlib.h>
#include <png.h>

typedef struct
{
	int  Width;
	int  Height; 
	unsigned int __attribute__((aligned(16))) *data;
}Tex;

typedef struct 
{ 
   char *file; 
   png_size_t pos; 
   png_size_t size; 
}MemPng; 

int getNextPower2(int width)
{
	int b = width;
	int n;
	for (n = 0; b != 0; n++) b >>= 1;
	b = 1 << n;
	if (b == 2 * width) b >>= 1;
	return b;
}

void user_read_fn(png_structp png_ptr, png_bytep buffer, png_size_t size)
{ 
	MemPng *data = (MemPng*)png_ptr->io_ptr; 
	if( data->size && (data->pos + size) > data->size ) 
	{ 
		png_error(png_ptr, "Error reading data from PNG file."); 
		return; 
	} 

	memcpy(buffer, data->file + data->pos, size); 
	data->pos += size; 
};

void swizzle_fast(unsigned char* out, unsigned char* in, unsigned int width, unsigned int height) 
{ 
   unsigned int i,j; 
   unsigned int rowblocks = (width / 16); 

   for (j = 0; j < height; ++j) 
   { 
      for (i = 0; i < width; ++i) 
      { 
         unsigned int blockx = i / 16; 
         unsigned int blocky = j / 8; 

         unsigned int x = (i - blockx*16); 
         unsigned int y = (j - blocky*8); 
         unsigned int block_index = blockx + ((blocky) * rowblocks); 
         unsigned int block_address = block_index * 16 * 8; 

         out[block_address + x + y * 16] = in[i+j*width]; 
      } 
   } 
} 

int LoadPngBuf(const unsigned char *tex_data, unsigned int size_tex, const char *output_file) 
{ 

	png_structp png_ptr; 
	png_infop info_ptr; 
	unsigned int sig_read = 0; 
	png_uint_32 width, height; 
	int bit_depth, color_type, interlace_type;
	unsigned int x, y;
	unsigned int* line; 
	Tex *image = (Tex*) malloc(sizeof(Tex)); 
	if (!image) return 0; 

	MemPng file; 
	file.file = (char*)tex_data; 
	file.pos = 0; 
	file.size = size_tex; 

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL); 
	if (png_ptr == NULL)
	{ 
		free(image); 
		return 0;
	}

	png_set_error_fn(png_ptr, (png_voidp) NULL, (png_error_ptr) NULL, 0); 
	png_set_read_fn(png_ptr, (png_voidp)&file, user_read_fn); 

	info_ptr = png_create_info_struct(png_ptr); 
	if (info_ptr == NULL)
	{ 
		free(image); 
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL); 
		return 0; 
	}

	png_init_io(png_ptr, (FILE*)&file); 
	png_set_sig_bytes(png_ptr, sig_read); 
	png_read_info(png_ptr, info_ptr); 
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, int_p_NULL, int_p_NULL); 

/*
	if (width > 512 || height > 512)
	{ 
		free(image); 
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL); 
		printf("Error: Texture to large. Maximum texture size: 512x512");
		return 0; 
	}
*/
	image->Width = getNextPower2(width); 
	image->Height = getNextPower2(height); 

	png_set_strip_16(png_ptr); 
	png_set_packing(png_ptr); 

	if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png_ptr); 
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_gray_1_2_4_to_8(png_ptr); 
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png_ptr); 

	png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
	
	image->data = (unsigned int*) malloc((image->Width * sizeof(unsigned int)) * image->Height); 
	if (!image->data)
	{ 
		free(image); 
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL); 
		return 0; 
	}
	
	line = (unsigned int*) malloc(width * sizeof(unsigned int)); 
	if (!line)
	{
		free(image->data); 
		free(image); 
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL); 
		return 0; 
	}
	for (y = 0; y < height; y++)
	{
		png_read_row(png_ptr, (unsigned char*) line, png_bytep_NULL); 
		for (x = 0; x < width; x++)
		{
			unsigned int color = line[x]; 
			image->data[x + y * image->Width] =  color; 
		}
	}

	free(line); 

	png_read_end(png_ptr, info_ptr); 
	png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);

	unsigned int *data = (unsigned int*)image->data;
    unsigned int *temp = (unsigned int*) malloc((width * sizeof(unsigned int)) * height);
	swizzle_fast((void*)temp, (void*)data, (width * sizeof(unsigned int)), height);
	
	char filename[1024];
	
	sprintf(filename, "%s.t", output_file);
	FILE *fpO = fopen(filename, "wb");
    fwrite((void*)temp, 1, (width * sizeof(unsigned int)) * height, fpO);
	fclose(fpO);
    
    free(image->data);
	return 1; 
}

int LoadPngFile(const char *in_file, const char *out_file)
{
	FILE *fp = fopen(in_file, "rb");
	if(fp > 0)
	{
    	fseek(fp, 0, SEEK_END);
    	unsigned int filesize = ftell(fp);
    	fseek(fp, 0, SEEK_SET);
		
		unsigned char *data = (unsigned char*) malloc(filesize);
		if(data)
		{
			fread(data, sizeof(unsigned char), filesize*sizeof(unsigned char), fp);
			fclose(fp);
			LoadPngBuf(data, filesize, out_file);
			free(data);
			return 1;
		}
	}
	return 0;
}



int main(int argc, char **argv)
{
    if(argc < 3) printf("Usage: %s <file_in> <file_out> \r\n", argv[0]);
    else LoadPngFile(argv[1], argv[2]);
    return 0;
}
