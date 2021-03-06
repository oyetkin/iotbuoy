// ADS1115 auto-gain test - 4/21/2017
// Developed by AKstudios - https://github.com/AKstudios

// This code automatically sets the gain of the ADS1115 16-bit ADC depending on the input voltage (between 0-5V). 
// A range of 7,000-30,000 is defined for acceptable ADC readings for a particular gain setting. Anything higher or lower than this will make the code adjust the gain automatically.
// This code will allow analog devices of varying voltage ranges to be plugged in without the need to reconfigure the code.

#include <Wire.h>
#include <Adafruit_ADS1X15.h> // https://github.com/adafruit/Adafruit_ADS1X15

Adafruit_ADS1115 ads;
adsGain_t gain[6] = {GAIN_TWOTHIRDS, GAIN_ONE, GAIN_TWO, GAIN_FOUR, GAIN_EIGHT, GAIN_SIXTEEN};  // create an array of type adsGain_t, which is a struct in the Adafruit_ADS1015.h library
int g = 1;      // set gain to 16x to begin with
float adc, volt;

void setup()
{
  Serial.begin(57600);
  ads.begin();
  ads.setGain(gain[1]);
}

void loop()
{
  delay(100);
  while(1) // this function constantly adjusts the gain to an optimum level
  {
    adc = ads.readADC_SingleEnded(2);

    if(adc >= 30000 && g > 0)  // if ADC is getting pegged at maximum value and is not the widest voltage range already, reduce the gain
    {
      g--;
      ads.setGain(gain[g]);
    }
    else if(adc <= 70 && g < 5)
    {
      g++;
      ads.setGain(gain[g]);
    }
    else
      break;
  }
  adc = ads.readADC_SingleEnded(2);   // get avg ADC value from channel 2
  volt = voltage(adc, g);  // convert ADC value to a voltage reading based on the gain
  Serial.print(adc); Serial.print(",");
  Serial.print(g);  Serial.print(",");
  Serial.println(volt);
}

// Perform multiple iterations to get higher accuracy ADC values (reduce noise) ******************************************
float samples(int pin)
{
  float sum=0.0;  //store sum as a 32-bit number
  for(int i=0;i<4;i++)
  {
    float val1 = ads.readADC_SingleEnded(2);
    sum = sum + val1;
    delay(1); // makes readings slower - probably don't need this delay, but ??\_(???)_/??
  }
  float average = sum/5;   //store average as a 32-bit number with decimal accuracy
  return average;
}

// Get voltage ****************************************************************
float voltage(float adc, int gain)
{
  float V;
  switch(gain)
  {
    case 0:  // default 2/3x gain setting for +/- 6.144 V
      V = adc * 0.0001875;
      break;
    case 1:  // 1x gain setting for +/- 4.096 V
      V = adc * 0.000125;
      break;
    case 2:  // 2x gain setting for +/- 2.048 V
      V = adc * 0.0000625;
      break;
    case 3:  // 4x gain setting for +/- 1.024 V
      V = adc * 0.00003125;
      break;
    case 4:  // 8x gain setting for +/- 0.512 V
      V = adc * 0.000015625;
      break;
    case 5:  // 16x gain setting for +/- 0.256 V
      V = adc * 0.0000078125;
      break;

    default:
      V = 0.0;
  }
  return V;
}
