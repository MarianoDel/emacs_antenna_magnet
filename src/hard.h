/*
 * hard.h
 *
 *  Created on: 28/11/2013
 *      Author: Mariano
 */

#ifndef HARD_H_
#define HARD_H_

#include "stm32f0xx.h"

//-- Defines For Configuration -------------------
//---- Configuration for Hardware Versions -------
//#define VER_2_0		//juego de 2 placas chicas
#define VER_1_1		//placa rectangular larga

//-- End Of Defines For Configuration ---------------

#ifdef VER_2_0
//GPIOA pin0	adc LM335 input

//GPIOA pin1
#define LED ((GPIOA->ODR & 0x0002) != 0)
#define LED_ON	GPIOA->BSRR = 0x00000002
#define LED_OFF GPIOA->BSRR = 0x00020000

//GPIOA pin2
#define S1_PIN ((GPIOA->IDR & 0x0004) == 0)

//GPIOA pin3
#define S2_PIN ((GPIOA->IDR & 0x0008) == 0)

//GPIOA pin4
#define CTRL_FAN ((GPIOA->ODR & 0x0010) != 0)
#define CTRL_FAN_ON GPIOA->BSRR = 0x00000010
#define CTRL_FAN_OFF GPIOA->BSRR = 0x00100000

//GPIOA pin5
#define PWR_DS3 ((GPIOA->ODR & 0x0020) != 0)
#define PWR_DS3_ON GPIOA->BSRR = 0x00000020
#define PWR_DS3_OFF GPIOA->BSRR = 0x00200000

//GPIOA pin6
//GPIOA pin7
//GPIOB pin0
//GPIOB pin1	TIM3 CH1 CH2 CH3 CH4

//GPIOA pin8
//GPIOA pin9	TIM1 CH1 CH2

//GPIOA pin10	USART1 rx Input

//GPIOA pin11
#define PWR_DS2 ((GPIOA->ODR & 0x0800) != 0)
#define PWR_DS2_ON GPIOA->BSRR = 0x00000800
#define PWR_DS2_OFF GPIOA->BSRR = 0x08000000

//GPIOA pin12
#define PWR_DS1 ((GPIOA->ODR & 0x1000) != 0)
#define PWR_DS1_ON GPIOA->BSRR = 0x00001000
#define PWR_DS1_OFF GPIOA->BSRR = 0x10000000

//GPIOA pin13
//GPIOA pin14	NC

//GPIOA pin15
#define DMX_INPUT ((GPIOA->IDR & 0x8000) != 0)

//GPIOB pin3	SPI clk

//GPIOB pin4
#define PWR_DS4 ((GPIOB->ODR & 0x0010) != 0)
#define PWR_DS4_ON GPIOB->BSRR = 0x00000010
#define PWR_DS4_OFF GPIOB->BSRR = 0x00100000

//GPIOB pin5	SPI Mosi

//GPIOB pin6
#define OE ((GPIOB->ODR & 0x0040) != 0)
#define OE_OFF GPIOB->BSRR = 0x00000040
#define OE_ON GPIOB->BSRR = 0x00400000

//GPIOB pin7 NC

#define CH_IN_TEMP ADC_Channel_0
#endif

#ifdef VER_1_1

//pines de enable para la serial y el lcd
#define ENA_SERIAL_LCD GPIOA->BSRR = 0x00000001
#define DISA_SERIAL_LCD GPIOA->BSRR = 0x00010000

#define ENA_SERIAL GPIOA->BSRR = 0x00000002
#define DISA_SERIAL GPIOA->BSRR = 0x00020000

#define TXD_IN				((GPIOA->ODR & 0x0080) != 0)
#define TX_LCD_OFF		GPIOA->BSRR = 0x00400000
#define TX_LCD_ON			GPIOA->BSRR = 0x00000040
#define TX_SERIE_OFF		GPIOA->BSRR = 0x00200000
#define TX_SERIE_ON		GPIOA->BSRR = 0x00000020

//GPIOA pin4
#define LED_COMM			((GPIOA->ODR & 0x0010) != 0)
#define LED_COMM_ON		GPIOA->BSRR = 0x00000010
#define LED_COMM_OFF		GPIOA->BSRR = 0x00100000

//GPIOA pin0	adc LM335 input

//GPIOA pin1
#define LED ((GPIOA->ODR & 0x0002) != 0)
#define LED_ON	GPIOA->BSRR = 0x00000002
#define LED_OFF GPIOA->BSRR = 0x00020000

//GPIOA pin2
#define S1_PIN ((GPIOA->IDR & 0x0004) == 0)

//GPIOA pin3
#define S2_PIN ((GPIOA->IDR & 0x0008) == 0)

//GPIOA pin4
#define CTRL_FAN ((GPIOA->ODR & 0x0010) != 0)
#define CTRL_FAN_ON GPIOA->BSRR = 0x00000010
#define CTRL_FAN_OFF GPIOA->BSRR = 0x00100000

//GPIOA pin5
#define PWR_DS3 ((GPIOA->ODR & 0x0020) != 0)
#define PWR_DS3_ON GPIOA->BSRR = 0x00000020
#define PWR_DS3_OFF GPIOA->BSRR = 0x00200000

//GPIOA pin6
//GPIOA pin7
//GPIOB pin0
//GPIOB pin1	TIM3 CH1 CH2 CH3 CH4

//GPIOA pin8
//GPIOA pin9	TIM1 CH1 CH2

//GPIOA pin10	USART1 rx Input

//GPIOA pin11
#define PWR_DS2 ((GPIOA->ODR & 0x0800) != 0)
#define PWR_DS2_ON GPIOA->BSRR = 0x00000800
#define PWR_DS2_OFF GPIOA->BSRR = 0x08000000

//GPIOA pin12
#define PWR_DS1 ((GPIOA->ODR & 0x1000) != 0)
#define PWR_DS1_ON GPIOA->BSRR = 0x00001000
#define PWR_DS1_OFF GPIOA->BSRR = 0x10000000

//GPIOA pin13
//GPIOA pin14	NC

//GPIOA pin15
#define DMX_INPUT ((GPIOA->IDR & 0x8000) != 0)

//GPIOB pin3	SPI clk

//GPIOB pin4
#define PWR_DS4 ((GPIOB->ODR & 0x0010) != 0)
#define PWR_DS4_ON GPIOB->BSRR = 0x00000010
#define PWR_DS4_OFF GPIOB->BSRR = 0x00100000

//GPIOB pin5	SPI Mosi

//GPIOB pin6
#define OE ((GPIOB->ODR & 0x0040) != 0)
#define OE_OFF GPIOB->BSRR = 0x00000040
#define OE_ON GPIOB->BSRR = 0x00400000

//GPIOB pin7 NC

#define CH_IN_TEMP ADC_Channel_0
#endif

// #define LAST_NUMBER_SPEAK		5
//
// #define DOOR_ROOF	200
// #define DOOR_THRESH	180

//--- Exported macro ---//
enum end_states
{
	WORKING = 1,
	END_OK,
	END_ERROR,
	END_TIMEOUT
};
//--- Exported functions ---//

//ESTADOS DEL PROGRAMA PRINCIPAL
#define STAND_BY	0
#define TX_LCD		1
#define TX_LCD2		2
#define TX_SERIE	3
#define TX_SERIE2	4
#define RX_SERIE	5
#define TEMP_SENSE	6
#define TX_SERIE_NC		7
#define TX_SERIE2_NC	8
#define CONNECT	9

#endif /* HARD_H_ */
