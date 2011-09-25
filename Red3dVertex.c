/*
* Red3dVertex.c
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
#include "Red3dVertex.h"

void Red3dDrawVertex(Vertex *ptr, unsigned int numverts, ScePspFVector3 pos, ScePspFVector3 rot, int mode)
{
	sceGuDisable(GU_BLEND);
	sceGumMatrixMode(GU_MODEL);
	sceGumLoadIdentity();
	{
		sceGumPushMatrix();
		sceGumTranslate(&pos);
		sceGumRotateXYZ(&rot);
	}
	sceGumDrawArray(mode, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, numverts, 0, ptr);
	sceGumPopMatrix();
	sceGuEnable(GU_TEXTURE_2D);
}

void *Red3dLoadVertex(const char *file, int vtype, int mempart)
{
	switch(vtype)
	{
		case VTYPE_TCNV: 
			return (VertexTCNV*)Red3dLoadFile(file,mempart);
		break;
		
		case VTYPE_CNV: 
			return (VertexCNV*)Red3dLoadFile(file,mempart);
		break;
		
		case VTYPE_TCV: 
			return (VertexTCV*)Red3dLoadFile(file,mempart);
		break;
		
		case VTYPE_CV: 
			return (VertexCV*)Red3dLoadFile(file,mempart);
		break;
		
		case VTYPE_TNV: 
			return (VertexTNV*)Red3dLoadFile(file,mempart);
		break;
		
		case VTYPE_TV: 
			return (VertexTV*)Red3dLoadFile(file,mempart);
		break;
		
		case VTYPE_NV: 
			return (VertexNV*)Red3dLoadFile(file,mempart);
		break;
		
		case VTYPE_V: 
			return (VertexV*)Red3dLoadFile(file,mempart);
		break;
	}
	return NULL;
}

void *Red3dLoadVertexBuf(void *buf, int numvertices, int vtype, int mempart)
{
	switch(vtype)
	{
		case VTYPE_TCNV: 
			return (void*)Red3dLoadBuffer(buf, sizeof(VertexTCNV)*numvertices, mempart);
		break;
		
		case VTYPE_CNV: 
			return (void*)Red3dLoadBuffer(buf, sizeof(VertexCNV)*numvertices, mempart);
		break;
		
		case VTYPE_TCV: 
			return (void*)Red3dLoadBuffer(buf, sizeof(VertexTCV)*numvertices, mempart);
		break;
		
		case VTYPE_CV: 
			return (void*)Red3dLoadBuffer(buf, sizeof(VertexCV)*numvertices, mempart);
		break;
		
		case VTYPE_TNV: 
			return (void*)Red3dLoadBuffer(buf, sizeof(VertexTNV)*numvertices, mempart);
		break;
		
		case VTYPE_TV: 
			return (void*)Red3dLoadBuffer(buf, sizeof(VertexTV)*numvertices, mempart);
		break;
		
		case VTYPE_NV: 
			return (void*)Red3dLoadBuffer(buf, sizeof(VertexNV)*numvertices, mempart);
		break;
		
		case VTYPE_V: 
			return (void*)Red3dLoadBuffer(buf, sizeof(VertexV)*numvertices, mempart);
		break;
	}
	return NULL;
}

Vertex *Red3dGenVertexCirc(int sides, float diameter)
{
	Vertex *vertices = (Vertex*)malloc(sizeof(Vertex) * (sides * 3));
	Vertex *ptr = (Vertex*)vertices;
	
	int j;
	for(j=0; j<=sides; j++)
	{
		float i = j*(360.0f/sides);
		ptr[j].u = 0;
		ptr[j].v = i;
		ptr[j].color = 0xFFFFFFFF;
		ptr[j].x = sin(i*GU_PI/180.0f)*diameter;
		ptr[j].y = cos(i*GU_PI/180.0f)*diameter; 
		ptr[j].z = 0;
	}
	
	return vertices;
}

Vertex *Red3dGenVertexLine(ScePspFVector3 *one, ScePspFVector3 *two)
{
	Vertex *vertices = (Vertex*)malloc(sizeof(Vertex) * 2 * 3);
	Vertex *ptr = (Vertex*)vertices;
	
	ptr[0].u = 0;
	ptr[0].v = 0; 
	ptr[0].color = 0xFFFFFFFF;
	ptr[0].x = one->x; 
	ptr[0].y = one->y; 
	ptr[0].z = one->z;
	
	ptr[1].u = 0;
	ptr[1].v = 1; 
	ptr[1].color = 0xFFFFFFFF;
	ptr[1].x = two->x; 
	ptr[1].y = two->y; 
	ptr[1].z = two->z;

	return vertices;
}
