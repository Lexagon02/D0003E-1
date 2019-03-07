#include <avr/io.h>
#include "GUI.h"
#include "pwmGenerator.h"
#include "TinyTimber.h"

int main(void)
{
	PwmGenerator pwmGenerator1 = PWMGENERATOR_INIT;
	initPwmGenerator(&pwmGenerator1, 4, 99);
	
	PwmGenerator pwmGenerator2 = PWMGENERATOR_INIT;
	initPwmGenerator(&pwmGenerator2, 6, 80);
	
	GUI gui = GUI_INIT;
	setPwmGenerators(&gui, &pwmGenerator1, &pwmGenerator2);
	initGUI(&gui);
	
    return TINYTIMBER(&gui, &run, NULL);
}

