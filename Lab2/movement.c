#include "lcd.h"
#include "movement.h"

void move_forward(oi_t *sensor_data,int distance) //forward movement function
{
    int sum = 0;
    oi_setWheels(100, 100); //move forward @ speed
    while (sum < distance) //loop to run until distance met
    {
        oi_update(sensor_data); //pull sensor data
        sum += sensor_data->distance; //iterate up to distance value
        lcd_printf("Total Distance: %d", sum); //display on lcd
    }
}
void move_backward(oi_t *sensor_data,int distance)  //backward movement function
{
    distance = -1 * distance; //swap sing for subtractive iteration

    int sum = 0;
    oi_setWheels(-100, -100); //move backward @ speed
    while (sum > distance) //loop to run until distance met
    {
        oi_update(sensor_data); //pull sensor data
        sum += sensor_data->distance; //iterate down to distance value
        lcd_printf("Total Distance: %d", sum); //display on lcd
    }
}

void lab2Bump(oi_t *sensor_data,int distance)
{
    int sum = 0;

    oi_setWheels(100, 100); //move forward full speed
    while (sum < distance)
    {

        if (sensor_data->bumpLeft) //detect bump
        {

            move_backward(sensor_data,150); //reverse(distance)
            turn_right(80); //turn(distance)
            move_forward(sensor_data,250); //move(distance)
            turn_left(80); //turn(distance)

            sum -= 150; //correct distance value

        }

        else if (sensor_data->bumpRight) //detect bump
        {

            move_backward(sensor_data,150); //reverse(distance)
            turn_left(80); //turn(distance)
            move_forward(sensor_data,250); //move(distance)
            turn_right(80);

            sum -= 150; //correct distance value

        }

        oi_setWheels(150, 150); //resume movement

        oi_update(sensor_data); //pull sensor data
        sum += sensor_data->distance; // keeps running sum of distance traveled

        lcd_printf("Total Distance: %d", sum); //lcd dsiplay
    }

    oi_setWheels(0, 0); //stop

}

void turn_right(int degrees) //turn (degrees)
{

    degrees = degrees * -1;

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    int sum = 0;
    oi_setWheels(-150, 150); //move forward @ speed
    while (sum > degrees)
    {
        oi_update(sensor_data);
        sum += sensor_data->angle;
        lcd_printf("Total angle: %d", sum);
    }

    oi_setWheels(0, 0); //stop

}

void turn_left(int degrees)
{

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    int sum = 0;
    oi_setWheels(150, -150); //move forward full speed
    while (sum < degrees)
    {
        oi_update(sensor_data);
        sum += sensor_data->angle;
        lcd_printf("Total angle: %d", sum);
    }

    oi_setWheels(0, 0); //stop

}
