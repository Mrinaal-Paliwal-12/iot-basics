/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/******************************************************************************
 * MSP432 Empty Project
 *
 * Description: An empty project that uses DriverLib. In this project, DriverLib
 * is built from source instead of the usual library.
 *
 *                MSP432P401
 *             ------------------
 *         /|\|                  |
 *          | |                  |
 *          --|RST               |
 *            |                  |
 *            |                  |
 *            |                  |
 *            |                  |
 *            |                  |
 * Author: 
*******************************************************************************/
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

int main(void)
{
    uint16_t cResult;//16 bits var, because result is in 12bits
        /* Stop Watchdog *///system is reset
        MAP_WDT_A_holdTimer();
        GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2);//its NOT a digital OR operator,we want to use all 3 pins thats why we used Pipe operator
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,GPIO_PIN7,GPIO_TERTIARY_MODULE_FUNCTION);//potentiometer is connect in port 4 ,
                                                                                                            //pin 7 becoz ADC exists in PIN 7 of port 4 and then digital signal goes to LED
        ADC14_initModule(ADC_CLOCKSOURCE_MCLK,ADC_PREDIVIDER_1,ADC_PREDIVIDER_1,ADC_NOROUTE);//initModule requires 4 parameters//clock is started //predivider is divding the clock to make it small//master clock is 3 MHz which is divider by 2 divders // ADC Noroute means use ADC to connect to that pin // more the predivider more the numbers we can get
        ADC14_configureSingleSampleMode(ADC_MEM6,true);//ADC_MEM6 internal memory for storing converted result
        ADC14_configureConversionMemory(ADC_MEM6,ADC_VREFPOS_AVCC_VREFNEG_VSS,ADC_INPUT_A6,false);//2nd parameter is 3.3v i.e the refrences voltage  , 3rd para is use that channel 6 inside MC and store it to the mem 6  , false is it will run only once
        ADC14_setSampleHoldTime(ADC_PULSE_WIDTH_64,ADC_PULSE_WIDTH_64);//it will hold the signal for 64 clock cycle , 2 times becoz it require 2 parameter ; our MC is 32bit so it divided into 16-16 bits channels 2nd para is useless as of now
        ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);//it will run automatically
        ADC14_enableModule();//for activating the module
        ADC14_enableConversion();//start conversion
        ADC14_toggleConversionTrigger();// trigger the conversion again and again

// ADC has to be given some reference voltage means range of voltage to work
        while(1)
        {
            while(!ADC14_isBusy());//it will wait till the dADC works to convert the signals
            cResult=ADC14_getResult(ADC_MEM6);
            P2OUT=cResult>>8;//right shift operator , for using multiple colors by changing bits
            ADC14_toggleConversionTrigger();// trigger the conversion again and again
        }
    }
