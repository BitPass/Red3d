/*
* Red3dIO.c
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
#include "valloc/valloc.h"

int DirIndexCounter = 0;

typedef struct vramFileInfo
{
	char *filepath;
	u32 *address;
	u32 blocksize;
}vramFileInfo;

vramFileInfo *DirIndex[1024];

//initialization function for the index of dirs / vmem pointers
vramFileInfo *Red3dInitFileInfo(const char *path, u32 *vmem, u32 blocksize)
{
	vramFileInfo *TempIndex = (vramFileInfo*) malloc(sizeof(vramFileInfo));
	TempIndex->filepath = malloc(strlen(path));
	TempIndex->address = vmem;
	TempIndex->blocksize = blocksize;
	memcpy(TempIndex->filepath, path, strlen(path));
	return TempIndex;
}

void Red3dUnloadAllVramFiles()
{
	int c;
	for(c=0;c<DirIndexCounter;c++)
	{
		vfree(DirIndex[c]->filepath);
		vfree(DirIndex[c]);
	}
	DirIndexCounter = 0;
}

//debug stuff
void Red3dPrintVramFileInfo(float size, int x, int y, u32 fg, u32 bg)
{
	int c;
	for(c=0; c<DirIndexCounter; c++)
		Red3dPrintf("%d: %s, %08x, %d bytes", size, x, y+(c*15), fg, bg, c, DirIndex[c]->filepath, DirIndex[c]->address, DirIndex[c]->blocksize);
}

//check if file is in memory
int Red3dCheckFile(const char *path)
{
	int c;
	for(c=0;c<DirIndexCounter;c++)
	    if(strcmp(DirIndex[c]->filepath, path)==0) return c;
	
	return -1;
}

void *Red3dLoadBuf(void *buf, unsigned int size, int mempart)
{
	void *ptr;
	
	if(mempart)
	{ 
		ptr = vabsptr(valloc(size));
		memcpy(ptr, buf, size);
	}
	else
		ptr = buf;

	DirIndex[DirIndexCounter] = Red3dInitFileInfo(buf, ptr, size);
	
	if(ptr) return ptr;
	else return NULL;
}

void *Red3dLoadFile(const char *path, int mempart)
{
	void *ptr, *readbuffer;
	
	int c = Red3dCheckFile(path);
	if(c >= 0) return DirIndex[c]->address;
	
	int fd = sceIoOpen(path, PSP_O_RDONLY, 0777);
	if(fd >= 0)
	{
		
		u32 size = sceIoLseek(fd, 0, SEEK_END); 
		sceIoLseek(fd, 0, SEEK_SET);
		
		readbuffer = malloc(size);
		sceIoRead(fd, readbuffer, size);
		
		ptr = Red3dLoadBuf(readbuffer, size, mempart);
		
		free(readbuffer);
		sceKernelDcacheWritebackInvalidateAll();
		sceIoClose(fd);
		
		return ptr;

	}
	return NULL;
}

