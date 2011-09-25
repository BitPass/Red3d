#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgeObj.h"
#include "pspgu.h"

void convert(const char *file_input, const char *file_output)
{
	pgeObj *obj = pgeObjLoad(file_input);
    if(obj->vertices)
    {
    	unsigned int c;
    	
    	char buffer[128];
    	char path[1024];
    	
        sprintf(path, "%s.h", file_output);
    	FILE *OUTPUT = fopen(path, "wb");
    	
    	fputs("/* object exported by obj2gu */ \r\n\r\n", OUTPUT);
    	
    	sprintf(buffer, "#ifndef %s_h \r\n", file_output);
        fputs(buffer, OUTPUT);
        sprintf(buffer, "#define %s_h \r\n", file_output);
        fputs(buffer, OUTPUT);
        
        fputs("#ifdef __cplusplus\r\nextern \"C\" {\r\n#endif\r\n\r\n", OUTPUT);
    	
        sprintf(buffer, "unsigned int %s_size = %d; \r\n", file_output, obj->numvertices);
        fputs(buffer, OUTPUT);
        
        sprintf(buffer, "Vertex __attribute__((aligned(16))) %s[%d] = { \r\n", file_output, obj->numvertices);
        fputs(buffer, OUTPUT);
        
		if(obj->drawflag == (GU_COLOR_8888|GU_TEXTURE_32BITF|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D))
		{
			pgeVertTCNV *ptr = (pgeVertTCNV *)obj->vertices;
			for(c = 0; c < obj->numvertices; c++)
			{	
				sprintf(buffer, "    {%1.0f, %1.0f, %3.6f, %3.6f, %3.6f, 0x%08lX, %3.6f, %3.6f, %3.6f}, \r\n", ptr[c].u, ptr[c].v, ptr[c].nx, ptr[c].ny, ptr[c].nz, ptr[c].color, ptr[c].x, ptr[c].y, ptr[c].z);
				fputs(buffer, OUTPUT);
			}
			printf("GU_COLOR_8888|GU_TEXTURE_32BITF|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D\r\n");
		}
		else if(obj->drawflag == (GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D))
		{
			pgeVertCNV *ptr = (pgeVertCNV *)obj->vertices;
			for(c = 0; c < obj->numvertices; c++)
			{	
				sprintf(buffer, "    {%3.6f, %3.6f, %3.6f, 0x%08lX, %3.6f, %3.6f, %3.6f}, \r\n", ptr[c].nx, ptr[c].ny, ptr[c].nz, ptr[c].color, ptr[c].x, ptr[c].y, ptr[c].z);
				fputs(buffer, OUTPUT);
			}
			printf("GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D\r\n");
		}
		else if(obj->drawflag == (GU_COLOR_8888|GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D))
		{
			pgeVertTCV *ptr = (pgeVertTCV *)obj->vertices;
			for(c = 0; c < obj->numvertices; c++)
			{	
				sprintf(buffer, "    {%1.0f, %1.0f, 0x%08lX, %3.6f, %3.6f, %3.6f}, \r\n", ptr[c].u, ptr[c].v, ptr[c].color, ptr[c].x, ptr[c].y, ptr[c].z);
				fputs(buffer, OUTPUT);
			}
			printf("GU_COLOR_8888|GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D\r\n");
		}
		else if(obj->drawflag == (GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D))
		{
			pgeVertCV *ptr = (pgeVertCV *)obj->vertices;
			for(c = 0; c < obj->numvertices; c++)
			{	
				sprintf(buffer, "    {0x%08lX, %3.6f, %3.6f, %3.6f}, \r\n", ptr[c].color, ptr[c].x, ptr[c].y, ptr[c].z);
				fputs(buffer, OUTPUT);
			}
			printf("GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D\r\n");
		}
		else if(obj->drawflag == (GU_TEXTURE_32BITF|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D))
		{
			pgeVertTNV *ptr = (pgeVertTNV *)obj->vertices;
			for(c = 0; c < obj->numvertices; c++)
			{	
				sprintf(buffer, "    {%1.0f, %1.0f, %3.6f, %3.6f, %3.6f,, %3.6f, %3.6f, %3.6f}, \r\n", ptr[c].u, ptr[c].v, ptr[c].nx, ptr[c].ny, ptr[c].nz, ptr[c].x, ptr[c].y, ptr[c].z);
				fputs(buffer, OUTPUT);
			}
			printf("GU_TEXTURE_32BITF|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D\r\n");
		}
		else if(obj->drawflag == (GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D))
		{
			pgeVertTV *ptr = (pgeVertTV *)obj->vertices;
			for(c = 0; c < obj->numvertices; c++)
			{	
				sprintf(buffer, "    {%1.0f, %1.0f, %3.6f, %3.6f, %3.6f}, \r\n", ptr[c].u, ptr[c].v, ptr[c].x, ptr[c].y, ptr[c].z);
				fputs(buffer, OUTPUT);
			}
			printf("GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D\r\n");
		}
		else if(obj->drawflag == (GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D))
		{
			pgeVertNV *ptr = (pgeVertNV *)obj->vertices;
			for(c = 0; c < obj->numvertices; c++)
			{	
				sprintf(buffer, "    {%3.6f, %3.6f, %3.6f, %3.6f, %3.6f, %3.6f}, \r\n", ptr[c].nx, ptr[c].ny, ptr[c].nz, ptr[c].x, ptr[c].y, ptr[c].z);
				fputs(buffer, OUTPUT);
			}
			printf("GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D\r\n");
		}
		else if(obj->drawflag == (GU_VERTEX_32BITF|GU_TRANSFORM_3D))
		{
			pgeVertV *ptr = (pgeVertV *)obj->vertices;
			for(c = 0; c < obj->numvertices; c++)
			{	
				sprintf(buffer, "    {%3.6f, %3.6f, %3.6f}, \r\n", ptr[c].x, ptr[c].y, ptr[c].z);
				fputs(buffer, OUTPUT);
			}
			printf("GU_VERTEX_32BITF|GU_TRANSFORM_3D\r\n");
		}

        
        sprintf(buffer, "}; \r\n");
        fputs(buffer, OUTPUT);
        
       	fputs("#ifdef __cplusplus\r\n}\r\n#endif\r\n#endif\r\n", OUTPUT);
        
        
    }
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("usage: %s <infile> <name>\r\n", argv[0]);
		return 0;
	}
    else convert(argv[1], argv[2]);
	return 0;
}
