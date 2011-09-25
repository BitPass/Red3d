/*
* Red3dTexture.c
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

typedef struct
{
	float u,v;
	unsigned int color;
	float x,y,z;
}TextureVertex;

void Red3dDrawRect(int x, int y, int width, int height, unsigned int color)
{
	sceGuEnable(GU_BLEND);
	TextureVertex* vertices = (TextureVertex*) sceGuGetMemory(2 * sizeof(TextureVertex));
	
	vertices[0].u = x;
	vertices[0].v = 0;
	vertices[0].color = color;
	vertices[0].x = x;
	vertices[0].y = y;
	vertices[0].z = 0;
	
	vertices[1].u = width;
	vertices[1].v = height;
	vertices[1].color = color;
	vertices[1].x = x + width;
	vertices[1].y = y + height;
	vertices[1].z = 0;
	
	sceGuDrawArray(GU_SPRITES, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_2D, 2, 0, vertices);
	
	sceGuDisable(GU_BLEND);
	sceGuDisable(GU_TEXTURE_2D);
}

void Red3dApplyTexture(Texture *tex, int face, int psm)
{
	sceGuFrontFace(face);
	sceGuDisable(GU_BLEND);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuTexMode(psm, 0, 0, GU_TRUE);
	sceGuTexOffset(0,0);
	sceGuTexFilter(GU_LINEAR,GU_LINEAR);
	sceGuTexFunc(GU_TFX_ADD,GU_TCC_RGBA);
	sceGuTexImage(0,tex->width,tex->height,tex->width,tex->data);
}

void Red3dDrawTexture(Texture *tex, int x, int y, int width, int height, int psm)
{
	Red3dApplyTexture(tex, GU_CCW, psm);
	Red3dDrawRect(x, y, width, height, 0xFF000000);
}

void Red3dTileTexture(Texture *tex)
{
	int x,y;
	for(x=0; x<480; x+=tex->height) for(y=0; y<272; y+=tex->height) Red3dDrawTexture(tex, x, y, tex->width, tex->height, tex->psm);
}

Texture *Red3dLoadTextureBuf(void *buf, int width, int height, int psm, int mode)
{
	Texture *tex_ptr = (Texture*) malloc(sizeof(Texture));
	tex_ptr->data    = (void*) Red3dLoadBuffer(buf, (width*sizeof(unsigned int))*height, mode);
	tex_ptr->height  = height;
	tex_ptr->width   = width;
	tex_ptr->psm	 = psm;
	return tex_ptr;
}

Texture *Red3dLoadTexture(const char *file, int width, int height, int psm, int mode)
{
	Texture *tex_ptr = (Texture*) malloc(sizeof(Texture));
	tex_ptr->data    = (void*) Red3dLoadFile(file, mode);
	tex_ptr->height  = height;
	tex_ptr->width   = width;
	tex_ptr->psm	 = psm;
	return tex_ptr;
}
