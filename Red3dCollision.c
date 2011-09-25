/*
* Red3dCollision.c
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

int Red3dCollisionX(BoundBox box1, ScePspFVector3 pos1, BoundBox box2, ScePspFVector3 pos2)
{
	if(pos1.x + box1.max.x <= pos2.x + box2.min.x) return 0;
	if(pos1.x + box1.min.x >= pos2.x + box2.max.x) return 0;
	return 1;
}

int Red3dCollisionY(BoundBox box1, ScePspFVector3 pos1, BoundBox box2, ScePspFVector3 pos2)
{
	if(pos1.y + box1.max.y <= pos2.y + box2.min.y) return 0;
	if(pos1.y + box1.min.y >= pos2.y + box2.max.y) return 0;
	return 1;
}

int Red3dCollisionZ(BoundBox box1, ScePspFVector3 pos1, BoundBox box2, ScePspFVector3 pos2)
{
	if(pos1.z + box1.max.z <= pos2.z + box2.min.z) return 0;
	if(pos1.z + box1.min.z >= pos2.z + box2.max.z) return 0;
	return 1;
}

int Red3dCollisionXYZ(BoundBox box1, ScePspFVector3 pos1, BoundBox box2, ScePspFVector3 pos2)
{
	if(
	!Red3dCollisionX(box1, pos1, box2, pos2) || 
	!Red3dCollisionY(box1, pos1, box2, pos2) || 
	!Red3dCollisionZ(box1, pos1, box2, pos2)
	)return 0;
	return 1;
};

BoundBox Red3dGetBoundBox(Vertex *ptr, int numverts)
{
	BoundBox box;
	unsigned int i = 0;
	while(i < numverts)
	{
		//get largest Positive nums from struct
		if(ptr[i].x > box.max.x) box.max.x = ptr[i].x;
		if(ptr[i].y > box.max.y) box.max.y = ptr[i].y;
		if(ptr[i].z > box.max.z) box.max.z = ptr[i].z;
		//get largest negative nums from struct
		if(ptr[i].x < box.min.x) box.min.x = ptr[i].x;
		if(ptr[i].y < box.min.y) box.min.y = ptr[i].y;
		if(ptr[i].z < box.min.z) box.min.z = ptr[i].z;
		i++;
	}
	return box;
}
