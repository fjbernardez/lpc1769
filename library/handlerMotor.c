#include "headers.h"

extern int duty;

/*instrucciones para direccion - PWM*/
void servoMotor(char direction) {

	if (direction != 'a' && direction != 'd') {

		duty = 11;//8

	} else if (direction == 'd') {

		duty = 12;//5
	} else if (direction == 'a') {

		duty = 10;//11

	}
}

void izquierdaCC () {

	motorIzquierdoRetroceder();
	motorDerechoAvanzar();

}

void derechaCC () {

	motorDerechoRetroceder();
	motorIzquierdoAvanzar();

}

// avanzar
void avanzar () {

  motorDerechoAvanzar();
  motorIzquierdoAvanzar();

  servoMotor(ADVANCE);

}

// retroceder
void retroceder () {

  motorDerechoRetroceder();
  motorIzquierdoRetroceder();

  servoMotor(MOVEBACK);

}

// frenar
void frenar () {

  motorDerechoFrenar();
  motorIzquierdoFrenar();

  servoMotor(BRAKE);

}

// rueda derecha
void motorDerechoAvanzar(){

  // P0.2
  SetPIN(0, 2, 1);

  // P0.3
  SetPIN(0, 3, 0);

}

void motorDerechoRetroceder(){

  // P0.2
  SetPIN(0, 2, 0);

  // P0.3
  SetPIN(0, 3, 1);

}

void motorDerechoFrenar(){

  // P0.2
  SetPIN(0, 2, 0);

  // P0.3
  SetPIN(0, 3, 0);

}


// rueda izquierda
void motorIzquierdoAvanzar(){

  // P2.6
  SetPIN(2, 6, 1);

  // P2.7
  SetPIN(2, 7, 0);

}

void motorIzquierdoRetroceder(){

  // P2.6
  SetPIN(2, 6, 0);

  // P2.7
  SetPIN(2, 7, 1);

}

void motorIzquierdoFrenar(){

  // P2.6
  SetPIN(2, 6, 0);

  // P2.7
  SetPIN(2, 7, 0);

}

void notCommand(void) {

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

	servoMotor(MOVEBACK);
}
