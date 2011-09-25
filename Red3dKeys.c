#include "Red3d.h"

int KEY_COORDINATE_X=0; //left to right
int KEY_COORDINATE_Y=3; //top to bottom
char *KB_BUFFER;
int CHAR_COUNTER=0;
int CHAR_COUNTER_MAX=0;
int CAPS_LOCK=0;
int SELECTOR_ROW=3;
int SELECTOR_KEY=0;
int done = 0;

#define SPACE 36
#define KEY_HEIGHT (KEY_COORDINATE_Y+counter) * SPACE
#define KEY_WIDTH (KEY_COORDINATE_X+scounter) * SPACE
#define ROW_AMNT 4
#define KEY_AMNT 13
#define CHAR_MAX 38

static char UPPER_CASE[ROW_AMNT][KEY_AMNT]={
  { '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+' },
  { 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '|' },
  { 0x20, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', 0x20 },
  { 0x20, 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0x20, 0x20 }
};

static char LOWER_CASE[ROW_AMNT][KEY_AMNT]={
  { '`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=' },
  { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '{', '}', '\\' },
  { 0x20, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', 0x20 },
  { 0x20, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0x20, 0x20 }
};

void Red3dKbDraw(u32 color_a, u32 color_b)
{
	int counter=0;
	int scounter=0;
	
	Red3dPrintMSG((strlen(KB_BUFFER) >= CHAR_MAX)? &KB_BUFFER[CHAR_COUNTER-CHAR_MAX] :KB_BUFFER, 0.8f, KEY_WIDTH+16, KEY_HEIGHT, color_b, color_a);
	
	for(counter=0; counter<ROW_AMNT; counter++)
	{
		for(scounter=0; scounter<KEY_AMNT; scounter++)
		{
			Red3dDrawRect(6+KEY_WIDTH, 6+KEY_HEIGHT, 36,36, color_b);
			Red3dPrintMSG("%c", 0.8f, KEY_WIDTH+16, KEY_HEIGHT+24, ((SELECTOR_ROW == counter) && (SELECTOR_KEY == scounter))? color_b : color_a, ((SELECTOR_ROW == counter) && (SELECTOR_KEY == scounter))? color_a : color_b, (CAPS_LOCK)? UPPER_CASE[counter][scounter] : LOWER_CASE[counter][scounter]);
		}
	}
	
}

int Red3dKbControls(char *a_buf, u32 size_a_buf, SceCtrlData pad, SceCtrlData last)
{
	
	if(!done)
	{
		KB_BUFFER = malloc(sizeof(char)*size_a_buf);
		done = 1;
	}
	
	while(1)
	{
		sceCtrlReadBufferPositive(&pad, 1);
		CHAR_COUNTER_MAX=size_a_buf;
		
		if (pad.Buttons != last.Buttons)
		{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				if(SELECTOR_ROW > 0)
					SELECTOR_ROW--;
				else if(SELECTOR_ROW == 0)
					SELECTOR_ROW=ROW_AMNT-1;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				if(SELECTOR_ROW < ROW_AMNT-1)
					SELECTOR_ROW++; 
				else if(SELECTOR_ROW == ROW_AMNT-1)
					SELECTOR_ROW=0;
			}
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				if(SELECTOR_KEY > 0)
					SELECTOR_KEY--;
				else if(SELECTOR_KEY == 0)
					SELECTOR_KEY=KEY_AMNT-1;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				if(SELECTOR_KEY < KEY_AMNT-1)
					SELECTOR_KEY++;
				else if(SELECTOR_KEY == KEY_AMNT-1)
					SELECTOR_KEY=0;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(CHAR_COUNTER < CHAR_COUNTER_MAX)
				{
					if((SELECTOR_ROW == 2) && ((SELECTOR_KEY == 0) || (SELECTOR_KEY == 12)));
					else if((SELECTOR_ROW == 3) && ((SELECTOR_KEY == 0) || (SELECTOR_KEY == 11) || (SELECTOR_KEY == 12)));
					else
					{
						if(CAPS_LOCK)
							sprintf(&KB_BUFFER[CHAR_COUNTER], "%c", UPPER_CASE[SELECTOR_ROW][SELECTOR_KEY]);
						else
							sprintf(&KB_BUFFER[CHAR_COUNTER], "%c", LOWER_CASE[SELECTOR_ROW][SELECTOR_KEY]);
						CHAR_COUNTER++;
					}
				}
			}
			if(pad.Buttons & PSP_CTRL_SQUARE)
			{
				if(CHAR_COUNTER > 0)
					CHAR_COUNTER--;
				KB_BUFFER[CHAR_COUNTER]=0x00;
			}
			if(pad.Buttons & PSP_CTRL_RTRIGGER)
			{
				KB_BUFFER[CHAR_COUNTER]=0x20;
				if(CHAR_COUNTER < CHAR_COUNTER_MAX)
					CHAR_COUNTER++;
			}
			if(pad.Buttons & PSP_CTRL_TRIANGLE)
			{
				strcpy(a_buf, KB_BUFFER);
				free(KB_BUFFER);
				done = 0;
				CHAR_COUNTER=0;
				return 0;
			}
			if(pad.Buttons & PSP_CTRL_CIRCLE)
			{
				return 0;
			}
			if(pad.Buttons & PSP_CTRL_LTRIGGER)
			{
				if(!CAPS_LOCK)CAPS_LOCK=1;
				else CAPS_LOCK=0;
			}
		}

	}

	return 1;
		
}
