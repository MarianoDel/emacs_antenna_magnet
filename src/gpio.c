//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F030
// ##
// #### GPIO.C ################################
//---------------------------------------------

// Includes --------------------------------------------------------------------
#include "gpio.h"
#include "stm32f0xx.h"
#include "hard.h"

// Ports Configs ---------------------------------------------------------------
#define GPIOA_ENABLE
//#define GPIOB_ENABLE
//#define GPIOF_ENABLE

// #define WITH_EXTI


// Module Functions ------------------------------------------------------------
void GPIO_Config (void)
{
    unsigned long temp;

    //--- MODER ---//
    //00: Input mode (reset state)
    //01: General purpose output mode
    //10: Alternate function mode
    //11: Analog mode

    //--- OTYPER ---//
    //These bits are written by software to configure the I/O output type.
    //0: Output push-pull (reset state)
    //1: Output open-drain

    //--- ORSPEEDR ---//
    //These bits are written by software to configure the I/O output speed.
    //x0: Low speed.
    //01: Medium speed.
    //11: High speed.
    //Note: Refer to the device datasheet for the frequency.

    //--- PUPDR ---//
    //These bits are written by software to configure the I/O pull-up or pull-down
    //00: No pull-up, pull-down
    //01: Pull-up
    //10: Pull-down
    //11: Reserved


#ifdef GPIOA_ENABLE

    //--- GPIO A ---//
    if (!GPIOA_CLK)
        GPIOA_CLK_ON;

#ifdef VER_1_1
    temp = GPIOA->MODER;
    temp &= 0xFFFFC00F;	//PA2 PA3 alternative PIN 4 5 y 6 out, 7 in
    temp |= 0x000015A0; //Cada 2 bits un pin.
    GPIOA->MODER = temp;

    temp = GPIOA->OTYPER;
    temp &= 0xFFFFC0FF;
    temp |= 0x00001500;
    GPIOA->OTYPER = temp;

    temp = GPIOA->OSPEEDR;
    temp &= 0xFFFFC0FF;
    temp |= 0x00000000;
    GPIOA->OSPEEDR = temp;

    temp = GPIOA->PUPDR;
    temp &= 0xFFFFFFFF;
    temp |= 0x00000000;
    GPIOA->PUPDR = temp;
#endif

#if ((defined VER_2_0) || (defined VER_1_2) || (defined VER_1_3))
    temp = GPIOA->MODER;
    temp &= 0xFFFFFC03;	//PA1 analog; PA2 PA3 alternative; PA4 output
    temp |= 0x000001AC;
    GPIOA->MODER = temp;

    temp = GPIOA->OTYPER;
    temp &= 0xFFFFFFFF;
    temp |= 0x00000000;
    GPIOA->OTYPER = temp;

    temp = GPIOA->OSPEEDR;
    temp &= 0xFFFFFCFF;
    temp |= 0x00000000;
    GPIOA->OSPEEDR = temp;

    temp = GPIOA->PUPDR;
    temp &= 0xFFFFFFFF;
    temp |= 0x00000000;
    GPIOA->PUPDR = temp;
#endif

    //Alternate Fuction
    //GPIOA->AFR[0] = 0x11000000;	//PA7 -> AF1; PA6 -> AF1


#endif

#ifdef GPIOB_ENABLE

    //--- GPIO B ---//
    if (!GPIOB_CLK)
        GPIOB_CLK_ON;

    temp = GPIOB->MODER;	//2 bits por pin
    temp &= 0xFFFFC330;		//PB0 PB1 PB3 PB5 (alternative) PB6 out
    temp |= 0x0000188A;
    GPIOB->MODER = temp;

    temp = GPIOB->OTYPER;	//1 bit por pin
    temp &= 0xFFFFFFBC;
    temp |= 0x00000000;		//PB1 push pull
    GPIOB->OTYPER = temp;

    temp = GPIOB->OSPEEDR;	//2 bits por pin
    temp &= 0xFFFFCFF0;
    temp |= 0x00000000;		//low speed
    GPIOB->OSPEEDR = temp;

    temp = GPIOB->PUPDR;	//2 bits por pin
    temp &= 0xFFFFCFF0;
    temp |= 0x00000000;
    GPIOB->PUPDR = temp;

    //Alternate Fuction
    //GPIOB->AFR[0] = 0x11000000;	//PA7 -> AF1; PA6 -> AF1

#endif

#ifdef GPIOF_ENABLE

    //--- GPIO F ---//
    if (!GPIOF_CLK)
        GPIOF_CLK_ON;

    temp = GPIOF->MODER;
    temp &= 0xFFFFFFFF;
    temp |= 0x00000000;
    GPIOF->MODER = temp;

    temp = GPIOF->OTYPER;
    temp &= 0xFFFFFFFF;
    temp |= 0x00000000;
    GPIOF->OTYPER = temp;

    temp = GPIOF->OSPEEDR;
    temp &= 0xFFFFFFFF;
    temp |= 0x00000000;
    GPIOF->OSPEEDR = temp;

    temp = GPIOF->PUPDR;
    temp &= 0xFFFFFFFF;
    temp |= 0x00000000;
    GPIOF->PUPDR = temp;

#endif

#ifdef WITH_EXTI
    //Interrupt en PA8
    if (!SYSCFG_CLK)
        SYSCFG_CLK_ON;

    SYSCFG->EXTICR[0] = 0x00000000; //Select Port A
    SYSCFG->EXTICR[1] = 0x00000000; //Select Port A
    EXTI->IMR |= 0x0100; 			//Corresponding mask bit for interrupts PA8
    EXTI->EMR |= 0x0000; 			//Corresponding mask bit for events
    EXTI->RTSR |= 0x0100; 			//Pin Interrupt line on rising edge PA8
    EXTI->FTSR |= 0x0100; 			//Pin Interrupt line on falling edge PA8

    NVIC_EnableIRQ(EXTI4_15_IRQn);
    NVIC_SetPriority(EXTI4_15_IRQn, 2);
#endif
}

inline void EXTIOff (void)
{
	EXTI->IMR &= ~0x00000100;
}

inline void EXTIOn (void)
{
	EXTI->IMR |= 0x00000100;
}

//--- end of file ---//
