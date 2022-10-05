#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include<SLFS.h>
#include<WiFi.h>
#include<WiFiClient.h>
#include<WiFiServer.h>
#include<WiFiUdp.h>
// combinaton of energia and ccs functios
IPAddress shieldIP,subnetMask,gatewayIP; //IPAddress is a datatype , all others are variables of type IPAddress
uint8_t rssi;//unsigned interger of 8 bits
uint8_t networkId;
byte macAddr[6];// mac address is 6 bytes // physical address of device is mac add
byte encryptionType;

char ssid[]="vivoY73";// my cell phone
//char ssid[]="VK";
/*
 char ssid[]="vK";
 char password[]="";
 */

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);//Serial is class and begin is method all present in SPI library
    //putty is a terminal emulator
    //it will connnect the port and device at a given speed
    Serial.print("connecting to WIFI..");
    while(WiFi.begin(ssid)!=WL_CONNECTED)//for cell phone //WL_CONNECTED while it is not connected
        //while(WiFi.begin(ssid.password)!=WL_CONNECTED)
    {
        Serial.print(".");
        delay(1);
    }
    Serial.println("");
    Serial.print("Wifi Connected , Fetching Wifi Sheild's IP address :");
    while(WiFi.localIP()==INADDR_NONE){
        Serial.print(".");
        delay(1);
    }
    shieldIP = WiFi.localIP();//WIFI Method , local IP takes IP address and stores in var in IPADRESS DATATYPE
    Serial.println(shieldIP);

    Serial.print("Access Point name:");
    Serial.println(ssid);

    Serial.print("Signal Strength");//
    rssi=WiFi.RSSI();//it fecthes the signal strength
    Serial.println(rssi); //RSSI-Recived signal strength indication

    uint8_t networkId= WiFi.scanNetworks();
    Serial.print("number of access points in range:");
    Serial.println(networkId);
    for(int i=1;i<=networkId;i++){
        Serial.print("Name of Access points and encryption type:");
        Serial.print(WiFi.SSID(i));
        Serial.print(",");
        encryptionType=WiFi.encryptionType(i);
        //Serial.println(encryptionType,HEX);
        Serial.println(encryptionType,DEC);
    }

    subnetMask = WiFi.subnetMask();
    Serial.print("Subnet Mask:");
    Serial.println(subnetMask);

    gatewayIP=WiFi.gatewayIP();
    Serial.print("Gateway IP Address:");
    Serial.println(gatewayIP);

    WiFi.macAddress(macAddr);
    Serial.print("Mac Address of Sheild:");
    for(int i=0;i<6;i++){
        Serial.print(macAddr[i],HEX);
        if(i<=4)
            Serial.print(':');
        else
            Serial.println();
    }
//ADC CODE STARTS
    GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2);//its NOT a digital OR operator,we want to use all 3 pins thats why we used Pipe operator
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,GPIO_PIN7,GPIO_TERTIARY_MODULE_FUNCTION);//potentiometer is connect in port 4 ,
                                                                                                                //pin 7 becoz ADC exists in PIN 7 of port 4 and then digital signal goes to LED
            ADC14_initModule(ADC_CLOCKSOURCE_MCLK,ADC_PREDIVIDER_1,ADC_PREDIVIDER_1,ADC_NOROUTE);//initModule requires 4 parameters//clock is started //predivider is divding the clock to make it small//master clock is 3 MHz which is divider by 2 divders // ADC Noroute means use ADC to connect to that pin // more the predivider more the numbers we can get
            ADC14_configureSingleSampleMode(ADC_MEM6,true);//ADC_MEM6 internal memory for storing converted result
            ADC14_configureConversionMemory(ADC_MEM6,ADC_VREFPOS_AVCC_VREFNEG_VSS,ADC_INPUT_A6,false);//2nd parameter is 3.3v i.e the refrences voltage  , 3rd para is use that channel 6 inside MC and store it to the mem 6  , false is it will run only once
/*changing the vaules to 64 to 32 and 4*/ADC14_setSampleHoldTime(ADC_PULSE_WIDTH_32,ADC_PULSE_WIDTH_4);//it will hold the signal for 64 clock cycle , 2 times becoz it require 2 parameter ; our MC is 32bit so it divided into 16-16 bits channels 2nd para is useless as of now
            ADC14_setResolution(ADC_12BIT);
            ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);//it will run automatically
            ADC14_enableModule();//for activating the module
            ADC14_enableConversion();//start conversion
            ADC14_toggleConversionTrigger();// trigger the conversion again and again

    // ADC has to be given some reference voltage means range of voltage to work

}
void loop() {
  // put your main code here, to run repeatedly: 
    int result,regressedData1;
    float regressedData;

            while(!ADC14_isBusy());//it will wait till the dADC works to convert the signals
            result=ADC14_getResult(ADC_MEM6);
            P2OUT=result>>8;//right shift operator , for using multiple colors by changing bits
            Serial.println(result);
            delay(500);
            ADC14_toggleConversionTrigger();// trigger the conversion again and again

}
