/*
* Red3dSprite.c
* 
* Copyright 2011 RedHate RedHate@ymail.com
* 
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
* MA 02110-1301, USA.
*/

#include "Red3d.h"

typedef struct Sprite
{
	int x, y;
	int numverts;
	Vertex *verts;
}Sprite;

void Red3dDrawSprite(int x, int y, int width, int height, unsigned int color)
{
	sceGuEnable(GU_BLEND);
	sceGuDrawArray(GU_SPRITES, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_2D, 2, 0, vertices);
	sceGuDisable(GU_BLEND);
	sceGuDisable(GU_TEXTURE_2D);
}

Sprite *Red3dLoadSprite(const char *file, int width, int height, int psm)
{
	//load our sprite image from file
	Texture *tex_ptr = (Texture*) malloc(sizeof(Texture));
	tex_ptr->data    = (void*) Red3dLoadFile(file, U_MEM);
	tex_ptr->height  = height;
	tex_ptr->width   = width;
	tex_ptr->psm	 = psm;
	
	//alloc some memory for our sprite info
	Sprite *sprite_ptr = (Sprite*) sceGuGetMemory(sizeof(Sprite)); //meshes draw fast from umem.
	sprite_ptr->vertices = (Vertex*) sceGuGetMemory(sizeof(Vertex)*(tex_ptr->width*tex_ptr->height));
	
	//set co-ordinates not yet implemented
	sprite_ptr->x = 0;
	sprite_ptr->y = 0;
	
	//generate the vertex array using the color data from the image
	for(y=0; y<tex_ptr->height; y++)
	{
		for(x=0; x<tex_ptr->width; x++)
		{
			sprite_ptr->vertices[0].u = x;
			sprite_ptr->vertices[0].v = 0;
			sprite_ptr->vertices[0].color = (unsigned int*) tex_ptr->data[y*x];
			sprite_ptr->vertices[0].x = x;
			sprite_ptr->vertices[0].y = y;
			sprite_ptr->vertices[0].z = 0;
		}
	}
	
	//free our image data
	free(tex_ptr);
	
	return sprite_ptr;
}
