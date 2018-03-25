/*
 * keypad.c
 *
 *  Created on: Mar 16, 2018
 *      Author: eric
 */

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

#include "keypad.h"

uint8_t prev;
void init_keypad(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)){}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)){}

    GPIOPinTypeGPIOInput(ROW_BASE, ROW_PINS);
    GPIOPadConfigSet(ROW_BASE, ROW_PINS, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPD);

    GPIOPinTypeGPIOOutput(COL_BASE,  COL_PINS);
    GPIOPadConfigSet(COL_BASE, COL_PINS, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD);

    prev = 0x00;
}


/*      +-------UPPER-------+------LOWER--------+
 *        08   04   02   01   08   04   02   01
 *      +----+----+----+----+----+----+----+----+
 *      | R1 | R2 | R3 | R0 | C2 | C0 | C1 | xx |
 * BIT7 +----+----+----+----+----+----+----+----+ BIT0
 *      | C7 | C6 | C5 | C4 | E3 | E2 | E1 | xx |
 *
 */

uint8_t scan_keypad()
{
    uint8_t read;
    uint8_t key;
    key = 0x20; //Default to ascii space


    uint8_t upper;
    uint8_t lower;

    //Read selected row
    GPIOPinWrite(COL_BASE, COL_PINS, 0x0E);
    upper = GPIOPinRead(ROW_BASE, ROW_PINS);

    //Switch pin roles and read selected column
    GPIOPinTypeGPIOOutput(ROW_BASE, ROW_PINS);
    GPIOPadConfigSet(ROW_BASE, ROW_PINS, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD);
    GPIOPinTypeGPIOInput(COL_BASE,  COL_PINS);
    GPIOPadConfigSet(COL_BASE, COL_PINS, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPD);

    GPIOPinWrite(ROW_BASE, ROW_PINS, upper);

    lower = GPIOPinRead(COL_BASE, COL_PINS);

    //Restore previous pin settings.
    GPIOPinTypeGPIOInput(ROW_BASE, ROW_PINS);
    GPIOPadConfigSet(ROW_BASE, ROW_PINS, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPD);
    GPIOPinTypeGPIOOutput(COL_BASE,  COL_PINS);
    GPIOPadConfigSet(COL_BASE, COL_PINS, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD);

    read = upper | lower;

    if (read != prev)
    {
        delayMs(40);

        switch (read)
        {
        case KP_ASTERISK:
            key = '*';
            break;
        case KP_POUND:
            key = '#';
            break;
        case KP_ONE:
            key = '1';
            break;
        case KP_TWO:
            key = '2';
            break;
        case KP_THREE:
            key = '3';
            break;
        case KP_FOUR:
            key = '4';
            break;
        case KP_FIVE:
            key = '5';
            break;
        case KP_SIX:
            key = '6';
            break;
        case KP_SEVEN:
            key = '7';
            break;
        case KP_EIGHT:
            key = '8';
            break;
        case KP_NINE:
            key = '9';
            break;
        case KP_ZERO:
            key = '0';
            break;
        default:
            key = 'x';
        }
    }
    return key;
}
