/*
* Red3dGuInit.c
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
#include "intrafont/intrafont.h"
#include "valloc/valloc.h"

#define FRAMEBUFFER_WIDTH 512
#define SCREEN_HEIGHT 272
#define SCREEN_WIDTH  480

//vram and framebuffer globals
static unsigned int __attribute__((aligned(16))) list[262144];
void *framebuffer;
int dispBufferNumber;

//fps globals
u64 last_tick;
u32 tick_res;
int frame_count = 0;
int FPS_Setup = 0;
float curr_ms = 1.0f;
float curr_fps = 0.0f;
char fps_buf[64];

//camera globals
ScePspFVector3 CameraPosition = {0.0f, 0.0f, 0.0f};
ScePspFVector3 CameraRotation = {0.0f, 0.0f, 0.0f};

//intrafont globals
intraFont* ltn;

void Red3dPrintf(const char *message, float font_size, int x, int y, u32 fg_color, u32 bg_color, ...)
{
	sceGuEnable(GU_TEXTURE_2D);
	sceGuEnable(GU_BLEND);
	char buffer[256];
	va_list ap;
	
	va_start(ap, message);
	vsnprintf(buffer, 256, message, ap);
	va_end(ap);
	buffer[255] = 0;
	
	intraFontSetStyle(ltn, font_size, fg_color, bg_color, 0);
	intraFontPrint(ltn, x, y, buffer);
	sceGuDisable(GU_BLEND);
	sceGuDisable(GU_TEXTURE_2D);
}

/*
	float x_scroll1 = 80, x_scroll2 = 225, x_scroll3 = 370,  x_scroll4 = 390;
	intraFontSetStyle(ltn[8], 1.0f,WHITE,DARKGRAY,INTRAFONT_SCROLL_LEFT);
	x_scroll1 = intraFontPrintColumn(ltn[8], x_scroll1, y, 80, "This text is scrolled to the left.");
	intraFontSetStyle(ltn[8], 1.0f,WHITE,DARKGRAY,INTRAFONT_SCROLL_SEESAW);
	x_scroll2 = intraFontPrintColumn(ltn[8], x_scroll2, y, 90, "Back & forth like a seesaw.");
	intraFontSetStyle(ltn[8], 1.0f,WHITE,DARKGRAY,INTRAFONT_SCROLL_RIGHT);
	x_scroll3 = intraFontPrintColumn(ltn[8], x_scroll3, y, 80, "Scrolling to the right...");
	intraFontSetStyle(ltn[8], 1.0f,WHITE,DARKGRAY,INTRAFONT_SCROLL_THROUGH);
	x_scroll4 = intraFontPrintColumn(ltn[8], x_scroll4, y, 80, "This text is scrolled through.");
	intraFontSetStyle(ltn[8], 1.0f,WHITE,DARKGRAY,0);
*/

void Red3dPrintFPS(float font_size, int x, int y, u32 fg_color, u32 bg_color)
{
	
	if(FPS_Setup == 0)
	{
		sceRtcGetCurrentTick(&last_tick);
		tick_res = sceRtcGetTickResolution();
		FPS_Setup = 1;
	}
	
	frame_count++;
	
	u64 curr_tick;
	sceRtcGetCurrentTick(&curr_tick);
	
	if((curr_tick-last_tick) >= tick_res)
	{
		curr_fps = 1.0f / curr_ms;
		sprintf(fps_buf, "Framerate: %d.%03d",(int)curr_fps,(int)((curr_fps-(int)curr_fps) * 1000.0f)); // debug
		Red3dPrintf(fps_buf, font_size, x, y, fg_color, bg_color);
		curr_ms = (((curr_tick-last_tick)) / (float)tick_res) / frame_count;
		frame_count = 0;
		sceRtcGetCurrentTick(&last_tick);
	}
	else
	{
		sprintf(fps_buf, "Framerate: %d.%03d",(int)curr_fps,(int)((curr_fps-(int)curr_fps) * 1000.0f)); // debug
		Red3dPrintf(fps_buf, font_size, x, y, fg_color, bg_color);
	}
	
}

void Red3dCamLook(ScePspFVector3 pos, ScePspFVector3 rot)
{
	CameraPosition.x = pos.x;
	CameraPosition.y = pos.y;
	CameraPosition.z = pos.z;
	
	CameraRotation.x = rot.x;
	CameraRotation.y = rot.y;
	CameraRotation.z = rot.z;
}

void Red3dSetupScreen()
{
	sceGuDisplay(GU_TRUE);
	sceGuStart(GU_DIRECT,list);

	sceGuClearColor(GRAY);
	sceGuClearDepth(0);
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
	
	sceGumMatrixMode(GU_VIEW);
	sceGumLoadIdentity();
	{
		sceGumTranslate(&CameraPosition);
		sceGumRotateXYZ(&CameraRotation);
	}
	
	sceGumMatrixMode(GU_PROJECTION);
	sceGumLoadIdentity();
	sceGumPerspective(25.0f,16.0f/9.0f,0.5f,1000.0f);
}

void Red3dInitScreen()
{
	
	intraFontInit();
    
	ltn = intraFontLoad("flash0:/font/ltn8.pgf", 0);
	if(!ltn) sceKernelExitGame();
	intraFontSetStyle(ltn, 1.0f, 0xFFFFFFFF, 0xBFBFBFBF, 0);
	
	void *fbp0 = vrelptr(valloc((FRAMEBUFFER_WIDTH * sizeof(unsigned int))   * SCREEN_HEIGHT));
	void *fbp1 = vrelptr(valloc((FRAMEBUFFER_WIDTH * sizeof(unsigned int))   * SCREEN_HEIGHT));
	void *zbp  = vrelptr(valloc((FRAMEBUFFER_WIDTH * sizeof(unsigned short)) * SCREEN_HEIGHT));
	
	pspDebugScreenInit();
	sceGuInit();
	sceGuStart(GU_DIRECT,list);

	sceGuDrawBuffer(GU_PSM_8888, fbp0, FRAMEBUFFER_WIDTH);
	sceGuDispBuffer(SCREEN_WIDTH, SCREEN_HEIGHT, fbp1, FRAMEBUFFER_WIDTH);
	sceGuDepthBuffer(zbp, FRAMEBUFFER_WIDTH);
	sceGuOffset(2048 - (SCREEN_WIDTH/2),2048 - (SCREEN_HEIGHT/2));
	sceGuViewport(2048, 2048, SCREEN_WIDTH, SCREEN_HEIGHT);
	sceGuDepthRange(65535, 0);
    sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    sceGuDepthFunc(GU_GEQUAL);
    sceGuEnable(GU_DEPTH_TEST);
	sceGuEnable(GU_SCISSOR_TEST);
	
	sceGuFrontFace(GU_CCW);
	sceGuShadeModel(GU_SMOOTH);
	sceGuEnable(GU_CULL_FACE);
	sceGuEnable(GU_CLIP_PLANES);
	
	sceGuEnable(GU_BLEND);
	sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
	
	sceGuEnable(GU_TEXTURE_2D);
	sceGuTexFunc(GU_TFX_ADD,GU_TCC_RGBA);
	sceGuTexFilter(GU_LINEAR,GU_LINEAR);
	
	sceGuFinish();
	sceGuSync(0,0);
	
	Red3dSetupScreen();
	
}

void Red3dSetupLight(ScePspFVector3 pos, u32 dif, u32 spec)
{
	
	sceGuEnable(GU_LIGHTING);
	sceGuEnable(GU_LIGHT0);
	sceGuEnable(GU_LIGHT1);
	sceGuEnable(GU_LIGHT2);
	sceGuEnable(GU_LIGHT3);
	
	int lightnumber = 0;
	sceGuLight(lightnumber,GU_POINTLIGHT,GU_DIFFUSE_AND_SPECULAR,&pos);
	sceGuLightColor(lightnumber,GU_DIFFUSE,dif);
	sceGuLightColor(lightnumber,GU_SPECULAR,spec);
	sceGuLightAtt(lightnumber,0.0f,1.0f,0.0f);
	sceGuSpecular(12.0f);
	sceGuAmbient(0x00222222);
}

void Red3dFlipGuBuffer()
{
	sceGuFinish();
	sceGuSync(0,0);
	sceDisplayWaitVblankStart();
	framebuffer = sceGuSwapBuffers();
	dispBufferNumber ^= 1;
	Red3dSetupScreen();
}
