/*
 ===============================================================================
 Name        : TPO2019.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
 ===============================================================================
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include "headers.h"
#include "prototipo.h"

void poolFlagGPS(void);
int calculaChekSum (void);
unsigned char sumaLogica (unsigned char a, unsigned char b) ;

volatile char command = 0;
char auxCommand = 0;
extern int commandBuffer[6];
extern int counterKeepAlive;
extern int duty;
char tramaValida = 0;
char comandList[] = { 'w', 's', 'e', 'a', 'd', '?' };
int comandLen = 6;

typedef struct {

	// Buffer para recepcion
	unsigned char Buffer[39];
	//buffer Latitud
	unsigned int latitud[10];
	//buffer Longitud
	unsigned int longitud[11];

} TRAMA_GPS;

TRAMA_GPS tramaGPS;

int main(void) {

	init();

	while (1) {

		poolFlagComunication();
		instruction();

		//Descomentar y comentar las demas funciones dentro del loop para probar con la UART1 la funcionalidad de recepcion de datos GPS
		//poolFlagGPS();
	}

	return 0;
}

//Recibo la trama GPS
void poolFlagGPS() {

	static int cursor = 0;

	unsigned char data = UART1_PopRx();

	if (data >= 0) {

		tramaGPS.Buffer[cursor] = data;
		cursor++;

	}

	if (cursor==39) {

		cursor = 0;
	}

}

void instruction() {

	if (!tramaValida)
		return;

	tramaValida = 0;

	switch (command) {

	// avanzar
	case ADVANCE:
		avanzar();
		break;

		// frenar
	case BRAKE:
		frenar();
		break;

		// retroceder
	case MOVEBACK:
		retroceder();
		break;

		// derecha
	case TURN_RIGHT:
		servoMotor(command);
		break;

		// izquierda
	case TURN_LEFT:
		servoMotor(command);
		break;

		// keepAlive
	case KEEP_ALIVE:
		keepAlive();
		break;
	}
}

void poolFlagComunication() {

	static char estadoRX = 0;

	int16_t data = UART1_PopRx();

	// data recibido
	if (data >= 0) {

		switch (estadoRX) {

		case 0:

			if (data == '#') {
				estadoRX = 1;
			}
			break;

		case 1:

			if (charInList(data, comandLen)) {

				command = data;
				estadoRX = 2;
			}
			break;

		case 2:

			if (data == '$') {
				estadoRX = 0;
				//trama validada
				tramaValida = 1;
			}
			break;

		default:
			//reinicio maquina de estado
			estadoRX = 0;
			break;
		}

	}
}

void keepAlive() {

	restartCounterKeepAlive();

	return;

}

void restartCounterKeepAlive() {

	counterKeepAlive = 400;

}

/*validacion de instruccion dentro de trama recibida*/
int charInList(char c, int len) {

	int i;
	int flag = 0;

	for (i = 0; i < len; i++) {

		if (comandList[i] == c) {
			flag = 1;
			break;
		}
	}
	return flag;
}
