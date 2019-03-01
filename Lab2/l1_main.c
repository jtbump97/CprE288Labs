#include "movement.h"
#include "open_interface.h"

/**
 * main.c
 */

int main(void)
{
    lcd_init();
    int distance = 0;
    oi_t *sensor_data = oi_alloc(); //allocate memory for struct for sensor data
    oi_init(sensor_data); //initialize struct for sensor data



    lab2Bump(sensor_data,2000); //call for movement functions (data struct, distance)

    oi_free(sensor_data); //clear struct for sensor data

    }


