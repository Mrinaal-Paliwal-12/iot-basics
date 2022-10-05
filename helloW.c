#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

int main(void)
{
    /* Stop Watchdog */
    MAP_WDT_A_holdTimer();//watch dog timer , this timer starts when kit is given power
    // if it stops it will cause kit to reset
    int i;
    GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN0); // port is combination of 8 pins 0-7 , means 8 bits , 8 bits forms a port
    // this MC has 10 ports
    // this func tells mc to make PORT2, pin 0  as OUTPUT pin
    // GPIO means general purpose input output

    while(1) // super loop
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN0);//setting the pin as HIGH
        for(i=0;i<10000;i++); // random delay
        GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0);//setting the pin as LOW
        for(i=0;i<100000;i++); //random delay
    }
}
