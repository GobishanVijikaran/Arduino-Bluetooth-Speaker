/* Bluetooth Speaker with LED Lights

4 x 3W 40mm (4 ohm)Speaker Driver Unit 
1 x 3.7V 3000 mAh LiPo Battery 
2 x 3W PAM8403 Audio Amplifier

*/
#include <ShiftPWM.h>

int currentValue; 
int maxValue; 
int minValue; 
int timer2;
unsigned long timer;

float brightness;
int hue;
int saturation;

const int ShiftPWM_latchPin=8;
const bool ShiftPWM_invertOutputs = false;
const bool ShiftPWM_balanceLoad = false;

int sampleSpan = 5; // Value in milliseconds to sample data

int volume; // Range: 0-700
int threshold;

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
int numRegisters = 2;
int numRGBleds = numRegisters*8/3;

void setup()
{
  Serial.begin(9600);
  ShiftPWM.SetAmountOfRegisters(numRegisters);
  ShiftPWM.SetPinGrouping(1);
  ShiftPWM.Start(pwmFrequency,maxBrightness);
  resetValues();
}

void loop()
{    
  threshold = map(analogRead(A1),0,1024,0,200);
  currentValue = analogRead(A0);
    if (currentValue < minValue) 
    {
        minValue = currentValue;
    } 
    
    if (currentValue > maxValue) 
    {
        maxValue = currentValue;
    }
    
    if (millis() - timer >= sampleSpan) 
    {
        volume = maxValue - minValue;
        brightness = 0;
        Serial.println(volume);
        resetValues();
    }
    
      if(volume > threshold)
      {
        brightness = map(volume,0,200,0,255);
        Serial.println("yes");
      }

      if(brightness<=0)
      {
        brightness = 0;
      }
      
      ShiftPWM.SetHSV(random(numRGBleds),random(360),255,brightness);
}

void resetValues()
{
    currentValue = analogRead(A0);
    maxValue = 0;
    minValue = 1024;
    timer = millis(); 
}
