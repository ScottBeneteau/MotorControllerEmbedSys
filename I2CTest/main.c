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
#include "lcd_functions.h"
#include "i2c_setup.h"
#include "delay.h"



int main(void)
{
    const char *test = "Hello World\0";

    init_i2c0();
    setup_lcd();
    backlight_on();
    //test_lcd();
    //print_char_4bit_mode('a');
    //print_char_4bit_mode('b');
    //print_char_4bit_mode('c');

    print_string_4bit_mode(test);
    while(1)
    {
        delayMs(1000);
        print_char_4bit_mode('x');

    }
    return 0;
}


