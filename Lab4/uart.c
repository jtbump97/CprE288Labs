/*
 * uart.c
 *
 *  Created on: Feb 20, 2019
 *      Author: burnett
 */

#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

void uart_init()
{
    //Set up GPIO B UART 1 Config
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1;

    GPIO_PORTB_AFSEL_R |= (BIT0 | BIT1); // UART1 TX and RX
    GPIO_PORTB_PCTL_R |= 0x11; //Set port B pins 0,1 to Rx,Tx

    //Set up Tx Rx
    GPIO_PORTB_DEN_R |= (BIT1 | BIT0); //Set pins 0, 1 digital mode
    GPIO_PORTB_DIR_R &= ~BIT0; // Set pin 0 (Rx) to input (0)
    GPIO_PORTB_DIR_R |= BIT1; // Set pin 1 (Tx) to output (1)
    UART1_CTL_R &= ~(UART_CTL_UARTEN); //Control Enable
    UART1_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN); //RX Enable

    //Set baud rate (9600 Baud)
    //UART1_IBRD_R = 104; //16,000,000 / (16 * 9600) = 104.16666
    //UART1_FBRD_R = 11; // .1666*64+.5 = 11.16666
    //Set baud rate (115200)
    UART1_IBRD_R = 8;
    UART1_FBRD_R = 44;
    UART1_CC_R = UART_CC_CS_SYSCLK; //Use system clock as UART clock source
    UART1_LCRH_R = UART_LCRH_WLEN_8;

}

void uart_sendChar(char data)
{

    while (UART1_FR_R & 0x20)
    {
        //waiting to send until there is room
    }
    UART1_DR_R = data;

}

char uart_receive(void)
{
    char data = 0;
    while (UART1_FR_R & UART_FR_RXFE)
    {
        //wait to receive
    }
    data = (char) (UART1_DR_R & 0xFF);
    return data;

}

void uart_sendStr(const char *data)
{
    while (*data != '\0')
    {
        uart_sendChar(*data);
        data++;
    }
}

void My_UART1_Handler(void)
{
    int i = 1;
    if (UART1_MIS_R & UART_MIS_RXMIS)
    {
        while (1)
        {
            char data = uart_receive();

            char mssg[21];
            mssg[0] = data;
            uart_sendChar(mssg[0]);
            while (i < 20 && data != '\r')
            {
                data = uart_receive();

                if (data != '\r')
                {
                    mssg[i] = data;
                    uart_sendChar(mssg[i]);
                    i++;
                }
                else
                {
                    uart_sendChar('\r');
                    uart_sendChar('\n');
                }

            }

            mssg[i] = '\0';
            lcd_clear();
            lcd_printf(mssg);

            i = 1;

        }
        UART1_ICR_R |= UART_ICR_RXIC;
    }
    else if (UART1_MIS_R & UART_MIS_TXMIS)
    {
        while (1)
        {
            char data = uart_receive();

            char mssg[21];
            mssg[0] = data;
            uart_sendChar(mssg[0]);
            while (i < 20 && data != '\r')
            {
                data = uart_receive();

                if (data != '\r')
                {
                    mssg[i] = data;
                    uart_sendChar(mssg[i]);
                    i++;
                }
                else
                {
                    uart_sendChar('\r');
                    uart_sendChar('\n');
                }

            }

            mssg[i] = '\0';
            lcd_clear();
            lcd_printf(mssg);

            i = 1;

        }
        UART1_ICR_R |= UART_ICR_TXIC;

    }

}
void init_UART1(void)
{

    //Setup UART1 interrupts
    UART1_ICR_R |= (UART_ICR_TXIC | UART_ICR_RXIC); // Clear RX interrupt status flag
    UART1_IM_R |= UART_IM_TXIM | UART_IM_RXIM; // Enable RX interrupts

    //NVIC setup
    //Config NVIC to allow UART interrupts
    NVIC_PRI1_R |= 0x00200000; //Set UART1 IRQ pri to 1 (bits 15-13)
    NVIC_EN0_R = 0x00000040; //Enable UART1 IRQ (IRQ 5)

    IntRegister(INT_UART1, My_UART1_Handler);
    IntMasterEnable();
    UART1_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
}
