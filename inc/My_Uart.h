
#ifndef MY_UART_H_
#define MY_UART_H_

#include "Regs.h"

//--- flags de habilitación de interrupciones UART
#define IER_RBR		0x01
#define IER_THRE	0x02
#define IER_ERR		0x04

//--- flags de interrupciones UART
#define UART_IIR_ERR		0x06
#define UART_IIR_RDA		0x04
#define UART_IIR_THRE		0x02
#define UART_IIR_PEND		0x01


#define TOPE_BUFFER_TX 10
#define TOPE_BUFFER_RX 3

void UART1_Init(uint32_t);

void UART1_PushRx(uint8_t dato);
int32_t UART1_PopTx( void );
int16_t UART1_PopRx( void );
void UART1_PushTx(uint8_t dato);
void UART1_SendData (char * string , uint32_t len);
//void UART1_SendData (uint8_t * string , uint32_t len);


typedef struct {

	// Buffer de Transmision
	volatile unsigned char BufferTx[TOPE_BUFFER_TX];

	// Buffer de Recepcion
	unsigned char BufferRx[TOPE_BUFFER_RX];

	// Indices de Transmision
	volatile unsigned char IndiceTxIn,IndiceTxOut;
	// Indices de Recepcion
	volatile unsigned char IndiceRxIn,IndiceRxOut;

	// flag de fin de TX
	volatile char TxStart;

} STRUCT_UART;


#endif /*UART_H_*/
