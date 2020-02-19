#include "headers.h"

STRUCT_UART	 Uart1;

void UART1_IRQHandler (void) {

	unsigned char irrVal;
	//IIR reset por HW una vez leido
	irrVal = U1IIR;
	int16_t dato ;

	do {

		switch (irrVal&0x0F) {

			//Receive Data Ready
			case UART_IIR_RDA:

				// Guardo el dato
				dato = U1RBR;
				UART1_PushRx( (uint8_t) dato );
				break;

			// THRE, transmit holding register empty
			case UART_IIR_THRE:

					// Tomo el dato a Transmitir
					dato = UART1_PopTx();

				// si hay dato lo Transmito
				if ( dato >= 0 ) {

					U1THR = (uint8_t) dato;
				}

				else {

					Uart1.TxStart = 0;
				}

				break;

			// Error
			case UART_IIR_ERR:
				// se debe analizar el LSR para determinar el error
				break;
		}

		irrVal = U1IIR;
	}

	while( ! ( irrVal & UART_IIR_PEND ) );
}


void UART1_PushRx(uint8_t dato) {

	Uart1.BufferRx[Uart1.IndiceRxIn] = dato;
	Uart1.IndiceRxIn ++;
	Uart1.IndiceRxIn %= TOPE_BUFFER_RX;
}

int32_t UART1_PopTx( void ) {

	int32_t dato = -1;

	if ( Uart1.IndiceTxIn != Uart1.IndiceTxOut ) {

		dato = (unsigned int) Uart1.BufferTx[Uart1.IndiceTxOut];
		Uart1.IndiceTxOut ++;
		Uart1.IndiceTxOut %= TOPE_BUFFER_TX;

	}

	return dato;
}


int16_t UART1_PopRx( void ) {

	int32_t dato = -1;

	if ( Uart1.IndiceRxIn != Uart1.IndiceRxOut ) {

		dato = (unsigned int) Uart1.BufferRx[Uart1.IndiceRxOut];
		Uart1.IndiceRxOut ++;
		Uart1.IndiceRxOut %= TOPE_BUFFER_TX;
	}

	return dato;
}

void UART1_PushTx(uint8_t dato) {

	Uart1.BufferTx[Uart1.IndiceTxIn] = dato;

	Uart1.IndiceTxIn ++;
	Uart1.IndiceTxIn %= TOPE_BUFFER_TX;

	if ( Uart1.TxStart == 0 ) {

		Uart1.TxStart = 1;
		U1THR = (uint8_t) UART1_PopTx();
	}
}

void UART1_SendData (char * string , uint32_t len) {

	uint32_t i;

	// Para envio de datos binarios
	for( i = 0 ; i <= len ; i++ ) {

		UART1_PushTx( string[i] );
	}
}
