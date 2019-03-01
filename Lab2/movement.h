
/*
*Movement.h
*/


#ifndef MOVEMENT_H_
#define MOVEMENT_H_


#include <stdio.h>
#include "lcd.h"
#include "open_interface.h"

#include <inc/tm4c123gh6pm.h>
#include <stdint.h>

void move_forward(oi_t *sensor_data,int distance);

void move_backward(oi_t *sensor_data,int distance);

void lab2Bump(oi_t *sensor_data,int distance);

void turn_right(int degrees);

void turn_left(int degrees);

#endif /* MOVEMENT_H_ */



