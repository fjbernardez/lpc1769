#include "headers.h"

void init() {

	InitPLL();
	InitSystick();
	UART1_Init(9600);
	TIMER0_Init();
	initGPIO();
}

// inicia GPIO para el control de motores
void initGPIO(void) {

	// P0.2 - motor1 cc
	SetDIR(0, 2, SALIDA);
	SetPINSEL(0, 2, 0);
	SetPIN(0, 2, 0);

	// P0.3 - motor1 cc
	SetDIR(0, 3, SALIDA);
	SetPINSEL(0, 3, 0);
	SetPIN(0, 3, 0);

	// P2.6 - motor2 cc
	SetDIR(2, 6, SALIDA);
	SetPINSEL(2, 6, 0);
	SetPIN(2, 6, 0);

	// P2.7 - motor2 cc
	SetDIR(2, 7, SALIDA);
	SetPINSEL(2, 7, 0);
	SetPIN(2, 7, 0);

	// P0.21 - servoMotor
	SetDIR(0, 21, SALIDA);
	SetPINSEL(0, 21, 0);
	SetPIN(0, 21, 0);

	//P0.22 - Led keepAlive
	SetDIR(0, 22, SALIDA);
	SetPINSEL(0, 22, 0);
	SetPIN(0, 22, 0);

	// P2.7
	SetDIR(2, 7, SALIDA);
	SetPINSEL(2, 7, 0);
	SetPIN(2, 7, 0);

}



void InitSystick(void) {

	//	The default value gives a 10 millisecond interrupt rate if the CPU clock is set to 100 MHz.
	STRELOAD= ( STCALIB / 2 ) - 1; //2,5 millisecond

	STCURR = 0;

	STCTRL = 0x00000007;// 3 bit mas significativos en 1. Activa el timer, la interrupcion y elije el CPU clok (el que no es externo)
}

void TIMER0_Init(void) {

	//Enciendo el timer 0.
	PCONP|= (0X01 << 1);

	//Configuro Entrada de clock
	PCLKSEL0 &= ~(0x03 << 2);
	PCLKSEL0 |= (0x01 << 2);

	//Periferico como timer
	T0CTCR &= ~0x03;
	T0CTCR |= 0;

	//Cero los registros TC, PC y PR
	T0TC = 0;
	T0PC = 0;
	T0PR = 0;

	// Borro registros de cuenta
	T0TCR |= 0x02;
	T0TCR &= ~(0x02);

	// Configuro el PreScaler
//	T0PR = (STCALIB/100)-1;// frecuencia de 10.000Hz
	T0PR = 1;

	// Borro flags de interrupcion
	T0IR = 0xFFFFFFFF;

	// Valor de MATCH
	T0MR0 = (STCALIB/100)-1;// frecuencia de 10.000Hz
//  T0MR0 = STCALIB/10 ;	//PWM de 0.001 segundo
	// Configuro que se resetee cuando se llega al valor de match1
	T0MCR &= ~(0x07 << 0);
	T0MCR |= (0x03 << 0);

	ISER0 |= (0x1<<1);

	//Habilito el Timer.
	T0TCR |= 0x01;

}

void UART1_Init(uint32_t baudrate) {

	int pclk;
	unsigned long int Fdiv;

	// PCLK_UART1 is being set to 1/4 of SystemCoreClock
	pclk = CORE_CLK / 4;
	//1.- Registro PCONP (0x400FC0C4) - bit 4 en 1 prende la UART:
	PCONP|= 0x00000010;
	//2.- Registro PCLKSEL0 (0x400FC1A8) - bits 8 y 9 en 0 seleccionan que el clk de la UART1 sea 1MHz:
	PCLKSEL0&= ~(0x03<<6);
	//3.- Registro U1LCR (0x4001000C) - transmision de 8 bits, 1 bit de stop, sin paridad, sin break cond, DLAB = 1:
	U1LCR=0x0083;

	//4.- Registros U1DLL (0x40010000) y U1DLM (0x40010004) en 0xA2:
	Fdiv = (pclk / 16) / baudrate;		// Set baud rate
	U1DLM= Fdiv / 256;
	U1DLL= Fdiv % 256;

	//5.- Registro U1LCR, pongo DLAB en 0:
	U1LCR&= 0xFFFFFF7F;

	//6.- Registros PINSEL0 (0x4002C000) y PINSEL1 (0x4002C004) - habilitan las funciones especiales de los pines:
	SetPINSEL(0, 15, 1);
	//	SetDIR    ( 0, 15, SALIDA ); No es necesario
	SetPINSEL(0, 16, 1);
	//	SetDIR    ( 0, 16, ENTRADA );No es necesario

	ISER|= (1 << 6);// Habilito la interrupcion de la UART1 global. -> Interrupciones en LPC

	U1IER= IER_RBR | IER_THRE;// /* Enable UART1 interrupt*/ -> Interrupcion de la uart1
}
