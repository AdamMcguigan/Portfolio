#include <stdbool.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <uzebox.h>
#include <defines.h>

#include "data/font-6x12-full.inc"
#include "StarterKit.h"

int main(){
	//Set font and tiles to be used, and call prior to ClearVram();
	SetFontTable(font);

	//Clear the screen (fills Vram with tile zero)
	ClearVram();

	PrintChar(10,10,'H');
	PrintChar(11,10,'a');
	PrintChar(12,10,'r');
	PrintChar(13,10,'d');
	PrintChar(14,10,'w');
	PrintChar(15,10,'a');
	PrintChar(16,10,'r');
	PrintChar(17,10,'e');
	PrintChar(18,10,' ');
	PrintChar(19,10,'W');
	PrintChar(20,10,'o');
	PrintChar(21,10,'r');
	PrintChar(22,10,'k');
	PrintChar(23,10,'s');
	PrintChar(24,10,'h');
	PrintChar(25,10,'o');
	PrintChar(26,10,'p');

	while(1)
	{
		startgame();
	}
}
