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
#include "lab5_scan_data.h"



int main()
{

    uart_init();
    char sendstr[60];
    int i;

    // prepare the header
        sprintf(sendstr, "%s,%s,%s,\r\n", "Degrees", "IR Distance (cm)", "Sonar Distance(cm)");
    // send the header
        uart_sendStr(sendstr);
    
    //allocate space for struct
        struct reading reading_array[181];
        

    //get the reading data
        get_reading("dataset1.csv", reading_array);
    
    //print to PuTTy
        for(i =0; i<181;i++) {
    
        //arrange each line of data
            sprintf(sendstr, "%d,%f,%f,\r\n", i, reading_array[i].ir_distance, reading_array[i].sonar_distance);
        //send data through UART
            uart_sendStr(sendstr);
        }



}

