#include "headers.h"

extern volatile char command;
static int count = 0;
int duty=11;

int MAX = 200;

void TIMER0_IRQHandler(void) {

	if (count >= 0 && count < duty) {
		SetPIN(0, 21, 1);
	}
	else {

		SetPIN(0, 21, 0);
	}

	count++;
	//limpio interrupciones
	T0IR= 0xFFFFFFFF;

	if (count == MAX) {//250
		 count = 0;
	}

}
