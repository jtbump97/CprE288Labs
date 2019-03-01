/*
 * uart.h
 *
 *  Created on: Feb 20, 2019
 *      Author: burnett
 */

#ifndef UART_H_
#define UART_H_

void uart_init(void);

void uart_sendChar(char data);

char uart_receive(void);

void uart_sendStr(const char *data);

void init_UART1();

void My_UART1_Handler();

#endif /* UART_H_ */
