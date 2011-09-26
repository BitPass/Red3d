/*
* Red3dModel.c
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

void Red3dModelPos(Model *ptr,  float x, float y, float z)
{
	ptr->pos.x = x;
	ptr->pos.y = y;
	ptr->pos.z = z;
}

void Red3dModelRot(Model *ptr,  float x, float y, float z)
{
	ptr->rot.x = x;
	ptr->rot.y = y;
	ptr->rot.z = z;
}

void Red3dDrawModel(Model *ptr, ScePspFVector3 pos, ScePspFVector3 rot, int mode)
{
	sceGuDisable(GU_BLEND);
	sceGumMatrixMode(GU_MODEL);
	sceGumLoadIdentity();
	{
		sceGumPushMatrix();
		sceGumTranslate(&pos);
		sceGumRotateXYZ(&rot);
	}
	sceGumDrawArray(mode, ptr->vtype, ptr->numverts, 0, ptr->vertices);
	sceGumPopMatrix();
	sceGuEnable(GU_TEXTURE_2D);
}

Model *Red3dLoadModel(const char *file, int vtype, int mempart)
{
	int fd = sceIoOpen(file, PSP_O_RDONLY, 0777);
	if(fd >= 0)
	{
		u32 filesize = sceIoLseek(fd, 0, SEEK_END);
		sceIoLseek(fd, 0, SEEK_SET);
		sceIoClose(fd);
		
		Model *model = (Model*) malloc(sizeof(Model));
		
		Red3dModelPos(model, 0.0f, 0.0f, 0.0f);
		Red3dModelRot(model, 0.0f, 0.0f, 0.0f);
		
		switch(vtype)
		{
			case VTYPE_TNV:
				model->vtype = (GU_TEXTURE_32BITF|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D);
				model->numverts = filesize/sizeof(VertexTNV*);
			break;
			
			case VTYPE_TCNV:
				model->vtype = (GU_COLOR_8888|GU_TEXTURE_32BITF|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D);
				model->numverts = filesize/sizeof(VertexTCNV*);
			break;
			
			case VTYPE_TV:
				model->vtype = (GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D);
				model->numverts = filesize/sizeof(VertexTV*);
			break;
			
			case VTYPE_TCV:
				model->vtype = (GU_COLOR_8888|GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D);
				model->numverts = filesize/sizeof(VertexTCV*);
			break;
			
			case VTYPE_NV:
				model->vtype = (GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D);
				model->numverts = filesize/sizeof(VertexNV*);
			break;
			
			case VTYPE_CNV:
				model->vtype = (GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D);
				model->numverts = filesize/sizeof(VertexCNV*);
			break;
			
			case VTYPE_V:
				model->vtype = (GU_VERTEX_32BITF|GU_TRANSFORM_3D);
				model->numverts = filesize/sizeof(VertexV*);
			break;
			
			case VTYPE_CV:
				model->vtype = (GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D);
				model->numverts = filesize/sizeof(VertexCV*);
			break;
		}
		
		model->vertices = Red3dLoadVertex(file,vtype,mempart);
		model->box      = Red3dGetBoundBox(model->vertices, model->numverts);
		
		return model;	
	}
	return NULL;	
}

Model *Red3dLoadModelBuf(void *buf, int numvertices, int vtype, int mempart)
{
		
		Model *model = (Model*) malloc(sizeof(Model));
		
		Red3dModelPos(model, 0.0f, 0.0f, 0.0f);
		Red3dModelRot(model, 0.0f, 0.0f, 0.0f);
		
		switch(vtype)
		{
			case VTYPE_TNV:
				model->vtype = VTYPE_TNV;
				model->numverts = numvertices*sizeof(VertexTNV*);
			break;
			
			case VTYPE_TCNV:
				model->vtype = VTYPE_TCNV;
				model->numverts = numvertices*sizeof(VertexTCNV*);
			break;
			
			case VTYPE_TV:
				model->vtype = VTYPE_TV;
				model->numverts = numvertices*sizeof(VertexTV*);
			break;
			
			case VTYPE_TCV:
				model->vtype = VTYPE_TCV;
				model->numverts = numvertices*sizeof(VertexTCV*);
			break;
			
			case VTYPE_NV:
				model->vtype = VTYPE_NV;
				model->numverts = numvertices*sizeof(VertexNV*);
			break;
			
			case VTYPE_CNV:
				model->vtype = VTYPE_CNV;
				model->numverts = numvertices*sizeof(VertexCNV*);
			break;
			
			case VTYPE_V:
				model->vtype = VTYPE_V;
				model->numverts = numvertices*sizeof(VertexV*);
			break;
			
			case VTYPE_CV:
				model->vtype = VTYPE_CV;
				model->numverts = numvertices*sizeof(VertexCV*);
			break;
		}
		
		model->vertices = (void*) Red3dLoadVertexBuf(buf, numvertices, vtype, mempart);
		model->box      = Red3dGetBoundBox(model->vertices, model->numverts);
		
		if(model->vertices) return model;
		else return NULL;
}

Model *Red3dGenModelCirc(int sides, float diameter)
{
	Model *model = (Model*) malloc(sizeof(Model));
	
	Red3dModelPos(model, 0.0f, 0.0f, 0.0f);
	Red3dModelRot(model, 0.0f, 0.0f, 0.0f);
	
	model->vertices = Red3dGenVertexCirc(sides, diameter);
	model->numverts = sides + 1;
	model->box      = Red3dGetBoundBox(model->vertices, sides);
	
	return model;
}

Model *Red3dGenModelLine(ScePspFVector3 *one, ScePspFVector3 *two)
{
	Model *model = (Model*) malloc(sizeof(Model));
	
	Red3dModelPos(model, 0.0f, 0.0f, 0.0f);
	Red3dModelRot(model, 0.0f, 0.0f, 0.0f);
	
	model->vertices = Red3dGenVertexLine(one, two);
	model->numverts = 2;
	model->box      = Red3dGetBoundBox(model->vertices, 2);
	
	return model;
}


