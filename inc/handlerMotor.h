#ifndef MOTORES_H_
#define MOTORES_H_

void avanzar ();
void retroceder ();
void frenar ();
void motorDerechoAvanzar();
void motorDerechoRetroceder();
void motorDerechoFrenar();
void motorIzquierdoAvanzar();
void motorIzquierdoRetroceder();
void motorIzquierdoFrenar();

void servoMotor(char direction);

void notCommand(void);

void izquierdaCC ();
void derechaCC ();


#endif /* MOTORES_H_ */
