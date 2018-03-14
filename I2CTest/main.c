#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "lcd/lcd_functions.h"
#include "lcd/i2c_setup.h"
#include "delay.h"



int main(void)
{
    const char *greeting = "Hello World\0";
    const char *clrScreen = "Clearing scrn\0";
    const char *rstCursor = "Reset Cursor\0";

    char letter = 0x21;
    init_i2c0();
    i2c_send(0x27, 1, 0x00);
    setup_lcd();
    backlight_on();
    //test_lcd();
    //print_char_4bit_mode('a');
    //print_char_4bit_mode('b');
    //print_char_4bit_mode('c');
    clear_screen();
    cursor_home();

    print_string_4bit_mode(greeting);


    while(1)
    {
     /*
     print_char_4bit_mode(letter);
     delayMs(100);
     letter++;
     if (letter> 0x7E)
         letter = 0x21;
    */
    }

    return 0;
}

