/*
* Red3d.h
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
#ifndef red3d_h
#define red3d_h

#ifdef __cplusplus
extern "C" {
#endif

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <psppower.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <pspctrl.h>
#include <pspgu.h>
#include <pspgum.h>
#include <psprtc.h>
#include <stdarg.h>

#define V_MEM 1
#define U_MEM 0

//supported vertex modes
#define VTYPE_TNV (GU_TEXTURE_32BITF|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D)
#define VTYPE_TCNV (GU_COLOR_8888|GU_TEXTURE_32BITF|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D)
#define VTYPE_TV (GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D)
#define VTYPE_TCV (GU_COLOR_8888|GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D)
#define VTYPE_NV (GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D)
#define VTYPE_CNV (GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D)
#define VTYPE_V (GU_VERTEX_32BITF|GU_TRANSFORM_3D)
#define VTYPE_CV (GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D)


enum colors
{
	RED      = 0xFF0000FF,
	YELLOW   = 0xFF000FFF,
	GREEN    = 0xFF00FF00,
	CYAN     = 0xFFFFF000,
	BLUE     = 0xFFFF0000,
	WHITE    = 0xFFFFFFFF,
	DARKGRAY = 0xFF444444,
	GRAY     = 0xFF888888,
	BLACK    = 0xFF000000
};

typedef struct
{
	int x, y, width, height, psm;
	void *data;
}Texture;

typedef struct
{
	float u, v;
	unsigned int color;
	float nx,ny,nz;
	float x,y,z;
}Vertex;

typedef struct
{
	ScePspFVector3 min, max;
}BoundBox;

typedef struct
{
	BoundBox box;
	ScePspFVector3 pos, rot;
	int vtype;
	int numverts;
	void *vertices;
}Model;

void Red3dInitScreen();

void Red3dFlipGuBuffer();

void Red3dPrintf(const char *message, float font_size, int x, int y, u32 fg_color, u32 bg_color, ...);

void Red3dPrintFPS(float font_size, int x, int y, u32 fg_color, u32 bg_color);

void Red3dCamLook(ScePspFVector3 pos, ScePspFVector3 rot);

void Red3dSetupLight(ScePspFVector3 pos, u32 dif, u32 spec);

void Red3dModelPos(Model *ptr, float x, float y, float z);

void Red3dModelRot(Model *ptr, float x, float y, float z);

void Red3dDrawModel(Model *ptr, ScePspFVector3 pos, ScePspFVector3 rot, int mode);

Model* Red3dLoadModel(const char *file, int vtype, int mempart);

Model* Red3dLoadModelBuf(void *buf, int numverts, int vtype, int mempart);

Model* Red3dGenModelCirc(int sides, float diameter);

Model* Red3dGenModelLine(ScePspFVector3 *one, ScePspFVector3 *two);

void Red3dDrawVertex(Vertex *ptr, unsigned int numverts, ScePspFVector3 pos, ScePspFVector3 rot, int mode);

Vertex* Red3dGenVertexCirc(int sides, float diameter);

Vertex* Red3dGenVertexLine(ScePspFVector3 *one, ScePspFVector3 *two);

void* Red3dLoadVertex(const char *file, int vtype, int mempart);

void* Red3dLoadVertexBuf(void *buf, int numverts, int vtype, int mempart);

void Red3dDrawRect(int x, int y, int width, int height, unsigned int color);

void Red3dTileTexture(Texture *tex);

void Red3dApplyTexture(Texture *tex, int face, int psm);

void Red3dDrawTexture(Texture *tex, int x, int y, int width, int height, int psm);

Texture* Red3dLoadTexture(const char *file, int width, int height, int psm, int mempart);

Texture* Red3dLoadTextureBuf(void *buf, int width, int height, int psm, int mempart);

void* Red3dLoadFile(const char *file, int mempart);

void* Red3dLoadBuffer(void *buf, unsigned int size, int mempart);

int Red3dCollisionX(BoundBox box1, ScePspFVector3 pos1, BoundBox box2, ScePspFVector3 pos2);

int Red3dCollisionY(BoundBox box1, ScePspFVector3 pos1, BoundBox box2, ScePspFVector3 pos2);

int Red3dCollisionZ(BoundBox box1, ScePspFVector3 pos1, BoundBox box2, ScePspFVector3 pos2);

int Red3dCollisionXYZ(BoundBox box1, ScePspFVector3 pos1, BoundBox box2, ScePspFVector3 pos2);

BoundBox Red3dGetBoundBox(Vertex *ptr, int numverts);

#ifdef __cplusplus
}
#endif

#endif
