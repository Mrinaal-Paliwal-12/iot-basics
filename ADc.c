#include <stdint.h>
#include <stdbool.h>
int main(void)
{
//Analog to digital conversion
uint16_t cResult; //to holds 12 bits ADC
/* Stop Watchdog */
MAP_WDT_A_holdTimer();
GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2); //Pipe
symbols are used for redirecting to the next port here | set output because LED shows output
GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,GPIO_PIN7,GPIO_TERTIAR
Y_MODULE_FUNCTION); //potentiometer is connected to port 4 pin 7
ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1,
ADC_PREDIVIDER_1, ADC_NOROUTE); //Multiple predividers are required to get a lower
number | predivider_1 is dividing the clock by 1| Nouroute specifies the external connection -
using ADC to connect to the pin1
ADC14_configureSingleSampleMode(ADC_MEM6,true); // ADC_MEM6 is the memory
location associated with the particular port
ADC14_configureConversionMemory(ADC_MEM6,
ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A6, false); //A6 is the channel | using
port 3.3v for the reference voltage with ADC_VREFPOS
ADC14_setSampleHoldTime(ADC_PULSE_WIDTH_64, ADC_PULSE_WIDTH_64);
//Sampling and Holding signal | there are two ADC_PULSE_WIDTH_64 used becuase the API
requires two parameters
ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION); //specifies that the timer is
running automatically
ADC14_enableModule(); //activating the module
ADC14_enableConversion(); //final conversion
ADC14_toggleConversionTrigger(); //Triggering the conversion continously
while(1)
{
while(!ADC14_isBusy()); //while the ADC is busy the other inputs should wait
cResult=ADC14_getResult(ADC_MEM6); //12 bits results for 12 bit ADC | values should
be continuously stored in MEM6
P2OUT=cResult>>8;
ADC14_toggleConversionTrigger();
}
}