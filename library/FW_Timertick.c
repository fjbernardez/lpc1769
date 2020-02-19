#include "headers.h"
#include "prototipo.h"


extern char command;

extern int duty;

int counterKeepAlive = 0;

void SysTick_Handler(void) {

	//en conexion
	if (counterKeepAlive) {

		SetPIN(0, 22, 1);

		counterKeepAlive--;

	//fin de conexion
	} else {
		SetPIN(0, 22, 0);
	}
	return;
}
