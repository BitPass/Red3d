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
    	
        sprintf(path, "%s.m", file_output);
    	FILE *OUTPUT = fopen(path, "wb");
    	fwrite(obj->vertices, 1, obj->numvertices*sizeof(pgeVertTCV), OUTPUT);
    	fclose(OUTPUT);
    	
    	printf("Drawflag: ");
    	switch(obj->drawflag)
    	{
			
			case GU_COLOR_8888|GU_TEXTURE_32BITF|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D: 
				printf("GU_COLOR_8888|GU_TEXTURE_32BITF|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D\r\n");
			break;
			case GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D: 
				printf("GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D\r\n");
			break;
			case GU_COLOR_8888|GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D: 
				printf("GU_COLOR_8888|GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D\r\n");
			break;
			case GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D: 
				printf("GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D\r\n");
			break;
			case GU_TEXTURE_32BITF|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D: 
				printf("GU_TEXTURE_32BITF|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D\r\n");
			break;
			case GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D: 
				printf("GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D\r\n");
			break;
			case GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D: 
				printf("GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D\r\n");
			break;
			case GU_VERTEX_32BITF|GU_TRANSFORM_3D: 
				printf("GU_VERTEX_32BITF|GU_TRANSFORM_3D\r\n");
			break;

		}
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
