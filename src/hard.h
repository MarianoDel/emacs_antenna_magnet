//----------------------------------------------------
// #### PROJECT: Magnet Antennas - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### HARD.H #######################################
//----------------------------------------------------

// Define to prevent recursive inclusion ---------------------------------------
#ifndef HARD_H_
#define HARD_H_

#include "stm32f0xx.h"

//-- Defines For Configuration -------------------
//---- Configuration for Hardware Versions -------
// #define VER_2_0		//juego de 2 placas chicas
#define VER_1_1		//placa rectangular larga


//-- End Of Defines For Configuration ---------------

#ifdef VER_2_0
//GPIOA pin0
//GPIOA pin1	adc Hall

//GPIOA pin2
//GPIOA pin3	tx - rx usart

//GPIOA pin4
#define LED_COMM    ((GPIOA->ODR & 0x0010) != 0)
#define LED_COMM_ON    (GPIOA->BSRR = 0x00000010)
#define LED_COMM_OFF    (GPIOA->BSRR = 0x00100000)


//GPIOA pin5
//GPIOA pin6
//GPIOA pin7
//GPIOB pin1
//GPIOA pin9
//GPIOA pin10

//GPIOA pin13
//GPIOA pin14	NC

#endif    //VER_2_0

#ifdef VER_1_1

//pines de enable para la serial y el lcd
#define ENA_SERIAL_LCD    (GPIOA->BSRR = 0x00000001)
#define DISA_SERIAL_LCD    (GPIOA->BSRR = 0x00010000)

#define ENA_SERIAL    (GPIOA->BSRR = 0x00000002)
#define DISA_SERIAL    (GPIOA->BSRR = 0x00020000)


//GPIOA pin0    NC
//GPIOA pin1    NC

//GPIOA pin2    Usart1 Tx
//GPIOA pin3    Usart1 Rx

//GPIOA pin4
#define LED_COMM    ((GPIOA->ODR & 0x0010) != 0)
#define LED_COMM_ON    (GPIOA->BSRR = 0x00000010)
#define LED_COMM_OFF    (GPIOA->BSRR = 0x00100000)

//GPIOA pin5    Tx Serie as Gpio
#define TX_SERIE_OFF    (GPIOA->BSRR = 0x00200000)
#define TX_SERIE_ON    (GPIOA->BSRR = 0x00000020)

//GPIOA pin6    Tx Lcd as Gpio
#define TX_LCD_OFF    (GPIOA->BSRR = 0x00400000)
#define TX_LCD_ON    (GPIOA->BSRR = 0x00000040)

//GPIOA pin7    Input to do the Serial Matrix - Gpio
#define TXD_IN    ((GPIOA->IDR & 0x0080) != 0)

//GPIOB pin1    NC

//GPIOA pin9    NC
//GPIOA pin10    NC
//GPIOA pin13    NC
//GPIOA pin14    NC


#define CH_IN_TEMP ADC_Channel_0
#endif    //VER_1_1

// Exported Types Constants & Macros  ------------------------------------------
enum end_states
{
	WORKING = 1,
	END_OK,
	END_ERROR,
	END_TIMEOUT
};

// MAIN PROGRAM STATES
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
