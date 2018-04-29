/*
 * GPIO.c
 *
 *  Created on: 29 de abr de 2018
 *      Author: Igor G. Custodio
 */

#include <GPIO.h>
#include <stdint.h>
#include <tm4c123gh6pm.h>

/**
 * Returns the bit field in the port
 *
 * Desloca os bits do pino e compara com 0x01, assim garante que vai verificar sempre
 * o valor de apenas um bit
 *
 */
int pinNumber(uint32_t pin) {
    if (pin == 0x01) {
        return 0;
    }
    int i;
    for (i = 1; i <= 7; i++) {
        // desloca os bits do pino para a direita
        pin >>= 1;
        if (pin == 0x01) {
            return i;
        }
    }
    return 0;
}

/**
 * Set the pin direction
 *
 * Utiliza o registrador enviado por parametro e define a direcao dele (INPUT/OUTPUT)
 */
void setPinDirection(uint32_t port, uint32_t pin, int direction, uint32_t *registerAddr) {
	if (direction == OUTPUT) {
		if (readPinDirection(port, pin) == 1)
			return;
		registerAddr ^= pin;
	} else {
		registerAddr &= ~pin;
	}
}

/**
 * Returns the value of register
 *
 * Utiliza o registrador do parametro e verifica o valor do pino
 *
 * @return int value of register
 */
int readRegisterValue(uint32_t port, uint32_t pin, uint32_t *registerAddr) {
	int i = pinNumber(pin);

	return (registerAddr >> i) & 0x01;
}

/**
 * Habilita ou desabilita apenas o bit da porta
 *
 * Isso garante que nenhuma outra porta seja desativada
 */
void enablePort(uint32_t port) {
    SYSCTL_RCGCGPIO_R ^= port;
}


void setPin(uint32_t port, uint32_t pin, int direction) {
    switch (port) {
        case PORT_A:
        	setPinDirection(port, pin, direction, &GPIO_PORTA_DIR_R);
            GPIO_PORTA_DATA_R   ^= 0;
            GPIO_PORTA_DEN_R    ^= pin;
            break;
        case PORT_B:
            setPinDirection(port, pin, direction, &GPIO_PORTB_DIR_R);
            GPIO_PORTB_DATA_R   ^= 0;
            GPIO_PORTB_DEN_R    ^= pin;
            break;
        case PORT_C:
            setPinDirection(port, pin, direction, &GPIO_PORTC_DIR_R);
            GPIO_PORTC_DATA_R   ^= 0;
            GPIO_PORTC_DEN_R    ^= pin;
            break;
        case PORT_D:
        	setPinDirection(port, pin, direction, &GPIO_PORTD_DIR_R);
            GPIO_PORTD_DATA_R   ^= 0;
            GPIO_PORTD_DEN_R    ^= pin;
            break;
        case PORT_E:
        	setPinDirection(port, pin, direction, &GPIO_PORTE_DIR_R);
            GPIO_PORTE_DATA_R   ^= 0;
            GPIO_PORTE_DEN_R    ^= pin;
            break;
        case PORT_F:
        	setPinDirection(port, pin, direction, &GPIO_PORTF_DIR_R);
            GPIO_PORTF_DATA_R   ^= 0;
            GPIO_PORTF_DEN_R    ^= pin;
            break;
    }
}

/**
 * Desloca os bits conforme o numero do pino e compara se este esta
 * ligado ou nao e retorna o resultado da operacao bit-a-bit
 *
 */
int readPin(uint32_t port, uint32_t pin) {
    int i = pinNumber(pin);

    switch (port) {
        case PORT_A:
            return readRegisterValue(port, pin, GPIO_PORTA_DATA_R);
        case PORT_B:
        	return readRegisterValue(port, pin, GPIO_PORTB_DATA_R);
        case PORT_C:
        	return readRegisterValue(port, pin, GPIO_PORTC_DATA_R);
        case PORT_D:
        	return readRegisterValue(port, pin, GPIO_PORTD_DATA_R);
        case PORT_E:
        	return readRegisterValue(port, pin, GPIO_PORTE_DATA_R);
        case PORT_F:
        	return readRegisterValue(port, pin, GPIO_PORTF_DATA_R);
        default:
        	return 0;
    }
}


/**
 * Desloca os bits conforme o numero do pino e compara se este esta
 * ligado ou nao e retorna o resultado da operacao bit-a-bit
 *
 */
int readPinDirection(uint32_t port, uint32_t pin) {
	int i = pinNumber(pin);

	switch (port) {
		case PORT_A:
			return readRegisterValue(port, pin, GPIO_PORTA_DIR_R);
		case PORT_B:
			return readRegisterValue(port, pin, GPIO_PORTB_DIR_R);
		case PORT_C:
			return readRegisterValue(port, pin, GPIO_PORTC_DIR_R);
		case PORT_D:
			return readRegisterValue(port, pin, GPIO_PORTD_DIR_R);
		case PORT_E:
			return readRegisterValue(port, pin, GPIO_PORTE_DIR_R);
		case PORT_F:
			return readRegisterValue(port, pin, GPIO_PORTF_DIR_R);
		default:
			return 0;
	}
}