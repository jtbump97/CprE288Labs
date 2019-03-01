/**
 * main.c
 * @author: burnett
 * @date: 20/20/2019
 */

#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include "uart.h"
#include "open_interface.h"
#include "movement.h"

int main()
{
    //int i = 1;

    uart_init();
    lcd_init();
    // Part 3
    //init_UART1();

//Part One
//    while (1)
//    {
//        char data = uart_receive();
//
//        char mssg[21];
//        mssg[0] = data;
//        while (i < 20 && data!= '\r')
//        {
//            data = uart_receive();
//
//            if(data !='\r') {
//            mssg[i] = data;
//            i++;
//            }
//
//        }
//
//
//        mssg[i] = '\0';
//        lcd_clear();
//        lcd_printf(mssg);
//        i = 1;
//
//
//    }

//Part Two
//    while (1)
//    {
//        char data = uart_receive();
//
//        char mssg[21];
//        mssg[0] = data;
//        uart_sendChar(mssg[0]);
//        while (i < 20 && data != '\r')
//        {
//            data = uart_receive();
//
//        if(data !='\r')
//        {
//            mssg[i] = data;
//            uart_sendChar(mssg[i]);
//            i++;
//        }
//        else
//        {
//            uart_sendChar('\r');
//            uart_sendChar('\n');
//        }
//
//    }
//
//
//    mssg[i] = '\0';
//    lcd_clear();
//    lcd_printf(mssg);
//
//    i = 1;
//
//}

    oi_t *sensor_data = oi_alloc(); //allocate memory for struct for sensor data
    oi_init(sensor_data); //initialize struct for sensor data

    while (1)
    {

        char data = uart_receive();
        if (data != '\0' || data != '\r')
        {
            if (data == 'f')
            {
                move_forward(sensor_data, 200);


            }

            if (data == 'b')
            {
                move_backward(sensor_data, 200);

            }

            if (data == 'r')
            {
                turn_right(sensor_data, 90);

            }

            if (data == 'l')
            {
                turn_left(sensor_data, 90);
            }
        }
    }

}


