//Oguz Yetkin OY 8/4/2021
//self-calibrating sensor for Buoy project.  
//each blank measurement will be subtracted from the immediately read color 

#include <Wire.h>
//#include <Adafruit_ADS1015.h>
#include <Adafruit_ADS1X15.h>
//#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use thi for the 12-bit version */

int red_led = 5;
int green_led = 6;
int blue_led = 7;

int16_t blank_valuer = 0;
int16_t red_value = 0;
int16_t blank_valueg = 0;
int16_t green_value = 0;
int16_t blank_valueb = 0;
int16_t blue_value =  0;
int16_t blank_value2r = 0;
int16_t red_value2 = 0;
int16_t blank_value2g = 0;
int16_t green_value2 = 0;
int16_t blank_value2b = 0;
int16_t blue_value2 =  0;
int delay_intersample = 400;
int delay_intertest = 500;
int delay_blank = 5;  //keep this short
void setup(void)
{
  Serial.begin(9600);
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
  digitalWrite(red_led, LOW);
  digitalWrite(green_led, LOW);
  digitalWrite(blue_led, LOW);
  //Serial.println("Hello!");

  //  Serial.println("Getting single-ended readings from AIN0..3");
  //  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");

  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  //ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  //ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

  ads.begin();
  Serial.println();
  Serial.println("red_value,green_value,blue_value,red_value2,green_value2,blue_value2");
}

void loop(void)
{
  int16_t adc0, adc1, adc2, adc3;

  blank_valuer = ads.readADC_SingleEnded(0);
  blank_value2r = ads.readADC_SingleEnded(1);
  //blank_value2 = ads.readADC_SingleEnded(1);

  delay(delay_blank);
  digitalWrite(red_led, HIGH);
  delay(1000);
  red_value = ads.readADC_SingleEnded(0);
  red_value2 = ads.readADC_SingleEnded(1);
  digitalWrite(red_led, LOW);
  delay(delay_intersample);

  blank_valueg = ads.readADC_SingleEnded(0);
  blank_value2g = ads.readADC_SingleEnded(1);
  //blank_value2 = ads.readADC_SingleEnded(1);
  delay(delay_blank);
  digitalWrite(green_led, HIGH);
    delay(1000);
  green_value = ads.readADC_SingleEnded(0);
  green_value2 = ads.readADC_SingleEnded(1);
  digitalWrite(green_led, LOW);
  delay(delay_intersample);


  blank_valueb = ads.readADC_SingleEnded(0);
  blank_value2b = ads.readADC_SingleEnded(1);
  //blank_value2 = ads.readADC_SingleEnded(1);
  delay(delay_blank);
  digitalWrite(blue_led, HIGH);
  delay(1000);
  blue_value = ads.readADC_SingleEnded(0);
  blue_value2 = ads.readADC_SingleEnded(1);
  digitalWrite(blue_led, LOW);
  delay(delay_intersample);


  //  int16_t red_v=(red_value-blank_value);
  //  int16_t green_v= (green_value-blank_value);
  //  int16_t blue_v= ( blue_value - blank_value);
//  Serial.print(blank_valuer); Serial.print(", ");
//  Serial.print(red_value); Serial.print(", ");
//  Serial.print(blank_valueg); Serial.print(", ");
//  Serial.print(green_value); Serial.print(", ");
//  Serial.print(blank_valueb); Serial.print(", ");
//  Serial.print(blue_value); Serial.print(", ");
//  Serial.print(blank_value2r); Serial.print(", ");
//  Serial.print(red_value2); Serial.print(", ");
//  Serial.print(blank_value2g); Serial.print(", ");
//  Serial.print(green_value2); Serial.print(", ");
//  Serial.print(blank_value2b); Serial.print(", ");
//  Serial.print(blue_value2);


  //Serial.print(blank_valuer); Serial.print(", ");
  Serial.print(red_value-blank_valuer); Serial.print(", ");
  //Serial.print(blank_valueg); Serial.print(", ");
  Serial.print(green_value-blank_valueg); Serial.print(", ");
  //Serial.print(blank_valueb); Serial.print(", ");
  Serial.print(blue_value-blank_valueb); Serial.print(", ");
  //Serial.print(blank_value2r); Serial.print(", ");
  Serial.print(red_value2-blank_value2r); Serial.print(", ");
  //Serial.print(blank_value2g); Serial.print(", ");
  Serial.print(green_value2-blank_value2g); Serial.print(", ");
  //Serial.print(blank_value2b); Serial.print(", ");
  Serial.print(blue_value2-blank_value2b);

  Serial.println();


  //  adc1 = ads.readADC_SingleEnded(1);
  //  adc2 = ads.readADC_SingleEnded(2);
  //  adc3 = ads.readADC_SingleEnded(3);
  //  Serial.print("AIN0: "); Serial.println(adc0);
  //  Serial.print("AIN1: "); Serial.println(adc1);
  //  Serial.print("AIN2: "); Serial.println(adc2);
  //  Serial.print("AIN3: "); Serial.println(adc3);
  //  Serial.println(" ");
  // Serial.println(adc0);

  delay(1);
}
