/**
  ******************************************************************************
  * @file    Template_2/stm32f0_uart.c
  * @author  Nahuel
  * @version V1.0
  * @date    22-August-2014
  * @brief   UART functions.
  ******************************************************************************
  * @attention
  *
  * Use this functions to configure serial comunication interface (UART).
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hard.h"
#include "stm32f0xx.h"
#include "uart.h"

#include <string.h>

//#define SIZEOF_DATA	64


//--- Private typedef ---//
//--- Private define ---//
//--- Private macro ---//
#define BUFFRX_DIM 64
#define BUFFTX_DIM 64


//--- Externals variables ---//

#ifdef USE_USART1
extern volatile unsigned char buffrx_ready;
extern volatile unsigned char *pbuffrx;
extern volatile unsigned char *pbuffrx_cpy;
#endif

#ifdef USE_USART2
extern volatile unsigned char usart2_pckt_ready;
extern volatile unsigned char usart2_have_data;
//extern volatile unsigned char usart2_mini_timeout;
extern volatile unsigned char tx2buff[];
extern volatile unsigned char rx2buff[];
#endif


//--- Private variables ---//
#ifdef USE_USART1
volatile unsigned char * ptx1;
volatile unsigned char * ptx1_pckt_index;
volatile unsigned char * prx1;

//Reception buffer.
unsigned char buffrx[BUFFRX_DIM];
unsigned char buffrx_cpy[BUFFRX_DIM];


//Transmission buffer.
unsigned char bufftx[BUFFTX_DIM];
unsigned char * pbufftx;
unsigned char * pbufftx2;

#endif

#ifdef USE_USART2
volatile unsigned char * ptx2;
volatile unsigned char * ptx2_pckt_index;
volatile unsigned char * prx2;
#endif

//--- Private function prototypes ---//

//--- Module functions ---//
#ifdef USE_USART1
void USART1Config(void)
{
	if (!USART1_CLK)
		USART1_CLK_ON;

	// ptx1 = tx1buff;
	// ptx1_pckt_index = tx1buff;
	// prx1 = rx1buff;

	USART1->BRR = USART_9600;
	//USART1->CR2 |= USART_CR2_STOP_1;	//2 bits stop
//	USART1->CR1 = USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
//	USART1->CR1 = USART_CR1_RXNEIE | USART_CR1_RE | USART_CR1_UE;	//SIN TX
	USART1->CR1 = USART_CR1_RXNEIE | USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;	//para pruebas TX

	//habilito el pin
	GPIOA->AFR[0] = 0x00001100;	//PA2 -> AF1 PA3 -> AF1

	//seteo punteros
	pbuffrx = buffrx;
	pbufftx = bufftx;
	pbufftx2 = bufftx;

	NVIC_EnableIRQ(USART1_IRQn);
	NVIC_SetPriority(USART1_IRQn, 5);
}

void USART1_IRQHandler(void)
{
	unsigned short i;
	unsigned char dummy;

	// if (LED)
	// 	LED_OFF;
	// else
	// 	LED_ON;

	/* USART in mode Receiver --------------------------------------------------*/
	if (USART1->ISR & USART_ISR_RXNE)
	{
		dummy = USART1->RDR & 0x0FF;


		//Saving incoming data.
		*pbuffrx = dummy;

		if (pbuffrx < &buffrx[BUFFRX_DIM])
		{
			if (*pbuffrx == '\n')
			{

				*pbuffrx = 0;

				strcpy((char*)&buffrx_cpy[0], (const char *)&buffrx[0]);

				buffrx_ready = 1;
				pbuffrx = buffrx;
			}
			else
			{
				pbuffrx++;

				if (pbuffrx == &buffrx[BUFFRX_DIM])
					pbuffrx = buffrx;
			}


		}
		else
			pbuffrx = buffrx;
	}
	// else
	// 	USARTx->RQR |= 0x08;


	/* USART in mode Transmitter -------------------------------------------------*/
	if (USART1->CR1 & USART_CR1_TXEIE)
	{
		if (pbufftx2 < pbufftx)
		{
			USART1->TDR = *pbufftx2 & 0x0FF;
			pbufftx2++;
		}
		else
		{
			USART1->CR1 &= ~USART_CR1_TXEIE;

			pbufftx2 = bufftx;
			pbufftx = bufftx;
		}

//		USARTx->RQR |= 0x08;
	}

	if ((USART1->ISR & USART_ISR_ORE) || (USART1->ISR & USART_ISR_NE) || (USART1->ISR & USART_ISR_FE))
	{
		USART1->ICR |= 0x0e;
		dummy = USART1->RDR;
	}
}

// void USARTx_receive (void)
// {
//
// 	if (buffrx_ready)
// 	{
//
// 		//USARTx_Send((char *)&buffrx_cpy[0]);
//
// 		if (strncmp((char *)&buffrx_cpy[0], "keepalive", sizeof("keepalive") - 1) == 0)
// 		{
// 			Wait_ms(30);
// 			USARTx_Send("ant4,003.44,023.00,004.50,065.00\r\n");
// 			Wait_ms(30);
// 		}
//
//
//
// 		buffrx_ready = 0;
// 	}
//
// #ifdef USE_USARTx_TIMEOUT
// 	if (buffrx_timeout == 1)
// 	{
// 		buffrx_timeout = 0;
//
// 		pbuffrx = buffrx;
// 	}
//
// 	if (bufftx_timeout == 1)
// 	{
// 		bufftx_timeout = 0;
//
// 		pbufftx = bufftx;
// 	}
// #endif
// }

// void Usart1Send (char * send)
// {
// 	unsigned char i;
//
// 	i = strlen(send);
// 	Usart1SendUnsigned((unsigned char *) send, i);
// }
//
// void Usart1SendUnsigned(unsigned char * send, unsigned char size)
// {
// 	if ((ptx1_pckt_index + size) < &tx1buff[SIZEOF_DATA])
// 	{
// 		memcpy((unsigned char *)ptx1_pckt_index, send, size);
// 		ptx1_pckt_index += size;
// 		USART1->CR1 |= USART_CR1_TXEIE;
// 	}
// }
//
// void Usart1SendSingle(unsigned char tosend)
// {
// 	Usart1SendUnsigned(&tosend, 1);
// }
//
// unsigned char ReadUsart1Buffer (unsigned char * bout, unsigned short max_len)
// {
// 	unsigned int len;
//
// 	len = prx1 - rx1buff;
//
// 	if (len < max_len)
// 		memcpy(bout, (unsigned char *) rx1buff, len);
// 	else
// 	{
// 		len = max_len;
// 		memcpy(bout, (unsigned char *) rx1buff, len);
// 	}
//
// 	//ajusto punteros de rx luego de la copia
// 	prx1 = rx1buff;
//
// 	return (unsigned char) len;
// }
unsigned char USART1Send(char * send)
{
	unsigned char i;

	i = strlen(send);

	if ((pbufftx + i) < &bufftx[BUFFTX_DIM])
	{

		strcpy((char*)pbufftx, (const char *)send);
		pbufftx += i;

		USART1->CR1 |= USART_CR1_TXEIE;

	}
	else
		return END_ERROR;


	return WORKING;
}

#endif	//USE_USART1

#ifdef USE_USART2
void USART2Config(void)
{
	if (!USART2_CLK)
		USART2_CLK_ON;

	GPIOA->AFR[0] |= 0x0001100;	//PA2 -> AF1 PA3 -> AF1

	ptx2 = tx2buff;
	ptx2_pckt_index = tx2buff;
	prx2 = rx2buff;

	USART2->BRR = USART_115200;
	USART2->CR1 = USART_CR1_RXNEIE | USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;

	NVIC_EnableIRQ(USART2_IRQn);
	NVIC_SetPriority(USART2_IRQn, 7);
}

void USART2_IRQHandler(void)
{
	unsigned char dummy;

	/* USART in mode Receiver --------------------------------------------------*/
	if (USART2->ISR & USART_ISR_RXNE)
	{
		//RX WIFI
		dummy = USART2->RDR & 0x0FF;

#ifdef USE_GSM_GATEWAY
		if (prx2 < &rx2buff[SIZEOF_DATA])
		{
			*prx2 = dummy;
			prx2++;
			usart2_have_data = 1;
		}
			usart2_mini_timeout = TT_GPS_MINI;
#endif

	}

	/* USART in mode Transmitter -------------------------------------------------*/

	if (USART2->CR1 & USART_CR1_TXEIE)
	{
		if (USART2->ISR & USART_ISR_TXE)
		{
			if ((ptx2 < &tx2buff[SIZEOF_DATA]) && (ptx2 < ptx2_pckt_index))
			{
				USART2->TDR = *ptx2;
				ptx2++;
			}
			else
			{
				ptx2 = tx2buff;
				ptx2_pckt_index = tx2buff;
				USART2->CR1 &= ~USART_CR1_TXEIE;
			}
		}
	}

	if ((USART2->ISR & USART_ISR_ORE) || (USART2->ISR & USART_ISR_NE) || (USART2->ISR & USART_ISR_FE))
	{
		USART2->ICR |= 0x0e;
		dummy = USART2->RDR;
	}
}

void Usart2Send (char * send)
{
	unsigned char i;

	i = strlen(send);
	Usart2SendUnsigned((unsigned char *) send, i);
}

void Usart2SendUnsigned(unsigned char * send, unsigned char size)
{
	if ((ptx2_pckt_index + size) < &tx2buff[SIZEOF_DATA])
	{
		memcpy((unsigned char *)ptx2_pckt_index, send, size);
		ptx2_pckt_index += size;
		USART2->CR1 |= USART_CR1_TXEIE;
	}
}

void Usart2SendSingle(unsigned char tosend)
{
	Usart2SendUnsigned(&tosend, 1);
}

unsigned char ReadUsart2Buffer (unsigned char * bout, unsigned short max_len)
{
	unsigned int len;

	len = prx2 - rx2buff;

	if (len < max_len)
		memcpy(bout, (unsigned char *) rx2buff, len);
	else
	{
		len = max_len;
		memcpy(bout, (unsigned char *) rx2buff, len);
	}

	//ajusto punteros de rx luego de la copia
	prx2 = rx2buff;

	return (unsigned char) len;
}

#endif	///USE_USART2

//--- end of file ---//
