/**
 * main.c
 * @author:
 * @date:
 */

#include "lcd.h"
#include "button.h"
#include "timer.h"

volatile int button_event = 0; // Boolean to keep track of whether a hardware event has happened (button pressed)
volatile int button_num = 0; // keeps track of button pressed

/**
 * main.c
 * Prints the button that has been pressed
 */




int main(void) {

    lcd_init();
    button_init();
    init_button_interrupts(&button_event,&button_num);//(int *button_event_addr, int *button_num_addr)



    while (1)
    {
        if (button_event == 1){
            lcd_printf("Button pressed: %d",button_num);
        }
        /*if (button_getButton() == 6)
        {
            lcd_printf("Button: 6");
            button_num = 6;
        }

        if (button_getButton() == 5)
        {
            lcd_printf("Button: 5");
            button_num = 5;

        }

        if (button_getButton() == 4)
        {
            lcd_printf("Button: 4");
            button_num = 4;

        }
        if (button_getButton() == 3)
        {
            lcd_printf("Button: 3");
            button_num = 3;

        }

        if (button_getButton() == 2)
        {
            lcd_printf("Button: 2");
            button_num = 2;

        }

        if (button_getButton() == 1)
        {
            button_num = 1;
            lcd_printf("Button: 1");

        }
        if (button_getButton() == 0)
        {

            lcd_printf("No button pressed");
        }




        //else {
         //   lcd_clear();*/
       // }

    }

    //#warning "Unimplemented function: int main(void)" // delete warning after implementing
    // Hint: You may need to use pointers to return the button that has been pressed
}
