#include <WiFi.h>
#include <SPI.h>
//#define SSID "octanauts"
//#define PASSWORD "aditya30"
IPAddress shieldIP,subnetMask,gatewayIP; //IPAddress is a datatype , all others are variables of type IPAddress
uint8_t rssi;//unsigned interger of 8 bits
uint8_t networkId;
byte macAddr[6];// mac address is 6 bytes // physical address of device is mac add
byte encryptionType;
//char ssid[]="vivoY73";// my cell phone
char ssid[]="VK";
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
}
void loop() {
  // put your main code here, to run repeatedly: 
}