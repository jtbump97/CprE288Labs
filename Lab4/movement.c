#include "lcd.h"
#include "movement.h"
#include "uart.h"

void move_forward(oi_t *sensor_data, int distance) //forward movement function
{
    int sum = 0;
    oi_setWheels(100, 100); //move forward @ speed
    while (sum < distance) //loop to run until distance met
    {
        oi_update(sensor_data); //pull sensor data
        sum += sensor_data->distance; //iterate up to distance value

    }
    oi_setWheels(0,0);
    lcd_printf("forward, %d", sum); //display on lcd
    uart_sendStr("Forward ");
    char sum_char[4];
    sprintf(sum_char,"%d",sum);
    uart_sendStr(sum_char);
    uart_sendStr(" travelled\r\n");
}
void move_backward(oi_t *sensor_data, int distance) //backward movement function
{


    int sum = 0;
    oi_setWheels(-100, -100); //move backward @ speed
    while (sum < distance) //loop to run until distance met
    {
        oi_update(sensor_data); //pull sensor data
        sum -= sensor_data->distance; //iterate down to distance value

    }
     oi_setWheels(0,0);
    lcd_printf("backward, %d", sum); //display on lcd
    uart_sendStr("Backward ");
    char sum_char[4];
    sprintf(sum_char,"%d",sum);
    uart_sendStr(sum_char);
    uart_sendStr(" travelled\r\n");
}

//void lab2Bump(oi_t *sensor_data, int distance)
//{
//    int sum = 0;
//
//    oi_setWheels(100, 100); //move forward full speed
//    while (sum < distance)
//    {
//
//        if (sensor_data->bumpLeft) //detect bump
//        {
//
//            move_backward(sensor_data, 150); //reverse(distance)
//            turn_right(80); //turn(distance)
//            move_forward(sensor_data, 250); //move(distance)
//            turn_left(80); //turn(distance)
//
//            sum -= 150; //correct distance value
//
//        }
//
//        else if (sensor_data->bumpRight) //detect bump
//        {
//
//            move_backward(sensor_data, 150); //reverse(distance)
//            turn_left(80); //turn(distance)
//            move_forward(sensor_data, 250); //move(distance)
//            turn_right(80);
//
//            sum -= 150; //correct distance value
//
//        }
//
//        oi_setWheels(150, 150); //resume movement
//
//        oi_update(sensor_data); //pull sensor data
//        sum += sensor_data->distance; // keeps running sum of distance traveled
//
//        lcd_printf("Total Distance: %d", sum); //lcd dsiplay
//    }
//
//    oi_setWheels(0, 0); //stop
//
//}

void turn_right(oi_t*sensor_data, int degrees) //turn (degrees)
{

       int sum = 0;
       oi_setWheels(-150, 150); //move forward @ speed
       while (sum < degrees)
       {
           oi_update(sensor_data);
           sum -= sensor_data->angle;


    }

    lcd_printf("Right,%d degrees", sum);
    uart_sendStr("Turned ");
    char sum_char[4];
    sprintf(sum_char,"%d",sum);
    uart_sendStr(sum_char);
    uart_sendStr(" right\r\n");

    oi_setWheels(0, 0); //stop

}

void turn_left(oi_t*sensor_data, int degrees)
{


    int sum = 0;
    oi_setWheels(150, -150); //move forward full speed
    while (sum < degrees)
    {
        oi_update(sensor_data);
        sum += sensor_data->angle;

    }

    lcd_printf("Left,%d degrees", sum);
    uart_sendStr("Turned ");
    char sum_char[4];
    sprintf(sum_char,"%d",sum);
    uart_sendStr(sum_char);
    uart_sendStr(" left\r\n");
    oi_setWheels(0, 0); //stop

}
