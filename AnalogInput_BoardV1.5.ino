 
#include <Wire.h>
#include <Adafruit_ADS1015.h>
 
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
 
 
 
const long interval = 1000;  //millisecond
unsigned long previousMillis = 0;
 
String dataJson = "";
 
boolean validEpoc = false;



Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */

int16_t adc0, adc1, adc2, adc3;
 
void _init() {

 

}

 

void setup(void)
{
  Serial.begin(115200);
 
  Serial.println("Load config...");
  SerialBT.begin("Analog_001"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  ads.begin();
  
  previousMillis = millis();
  
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  if ((in_max - in_min) + out_min != 0) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  } else {
    return 0;
  }
}

void loop(void)
{





  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    adc0 = ads.readADC_SingleEnded(0);
    adc1 = ads.readADC_SingleEnded(1);
    adc2 = ads.readADC_SingleEnded(2);
    adc3 = ads.readADC_SingleEnded(3);

    Serial.print(adc0); Serial.print(" ");  Serial.print(adc1); Serial.print(" ");   Serial.print(adc2); Serial.print(" ");  Serial.println(adc3);
    float val0 = mapfloat(adc0, 2128, 10560, 4, 20);
    float val1 = mapfloat(adc1, 2128, 10560, 4, 20);
    float val2 = mapfloat(adc2, 2128, 10560, 4, 20);
    float val3 = mapfloat(adc3, 2128, 10560, 4, 20);

  
    String udpData2 = "{\"Tn\":\"vpbHN0ulNCCptps6qRAk\",\"adc0\":";
    udpData2.concat(val0);
    udpData2.concat(",\"adc1\":");
    udpData2.concat(val1);
    udpData2.concat(",\"adc2\":");
    udpData2.concat(val2);
    udpData2.concat(",\"adc3\":");
    udpData2.concat(val3);
 
    udpData2.concat("}");
    Serial.println(udpData2);
    SerialBT.println(udpData2);
 
    previousMillis = currentMillis;

 

    previousMillis = currentMillis;
  }

  
}
