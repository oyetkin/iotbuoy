/*
   Install the following libraries:
   Adafruit BME280
   Adafruit Unified Sensor
   Author: Alex Horvath, Analytical Mechanics Associates
   With code contributed from Arjun Tambe and Oguz Yetkin
*/

#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <TinyGPS++.h>
#include <avr/wdt.h>

#include <Adafruit_ADS1X15.h>

#define DONEPIN  12 // Set the pin to send the done signal to the TPL5110 watchdog

//Create software serial object to communicate with SIM808. Pin 7 is RX on GPRS/GPS/GSM shield and pin 8 is TX for the robotshop GPS/GPRS/GSM shield here
// https://www.robotshop.com/en/sim808-gps-gprsgsm-arduino-shield-mkf.html?gclid=EAIaIQobChMIl-Hpytn58QIVdGxvBB3DMgZVEAQYDSABEgJUg_D_BwE
// If you are using a different GSM/GPS/GPRS module, use the RX/TX pins given in the board specification.

//Adafruit_BME280 bme; // Create a BME 280 instance
//TinyGPSPlus gps;
String device_name = "Ursula_2"; // Name your station
String dataout;

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */

adsGain_t gain[6] = {GAIN_TWOTHIRDS, GAIN_ONE, GAIN_TWO, GAIN_FOUR, GAIN_EIGHT, GAIN_SIXTEEN};  // create an array of type adsGain_t, which is a struct in the Adafruit_ADS1015.h library
int g = 1;      // set gain to one to begin with
float adc;
float volt;

const int FluorADS = 2;

const int NumSamples = 5; // How many samples do you want each sensor to take
float samples = 0; // This object collects a sum of each sample data, which is then divided by the number of samples to get the average.

//This struct defines a category of measurement, like "temperature" or "humidity."
struct measurement {
  float min_value; //min recordable by senseor
  float resolution; //sensor resolution
  String unit; //e.g. "Celsius"
  String type; //e.g. "temperature"
  float graph_lower; //lowest value to display on graph
  float graph_upper; //highest value for graph
  String hardware_name; //optionally, hardware used to collect the measurement
};

typedef struct measurement Measurement;

//Create an instance of Measurement for each of the kinds of measurements your sensor will record
//the format is {min_value, increment, units, measurement name, graph_min, graph_max, hardware name}

Measurement fluorescence = {0, 0.01, "Relative %", "fluorescence", 0, 100, "Fluorometer"};

void updateSerial()
{
  delay(20);
  while (Serial.available())
  {
    Serial1.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (Serial1.available())
  {
    Serial.write(Serial1.read());//Forward what Software Serial received to Serial Port
  }
}

void UplinkData(measurement m, float dataval)
{
  Serial.flush(); // Make sure that serial is flushed

  Serial1.flush(); // Make sure software serial is flushed

  delay(2000);

  String json = "{\"key\":\"" + device_name + "\",\"measurement_name\":\"" + m.type + "\",\"unit\":\"" + m.unit + "\",\"value\":" + String(dataval) + ",\"timestamp\":\"11/11/11 11:11:11\",\"lat\":\"30\",\"lon\":\"30\"}";
  //  const char *fulljson = json.c_str(); // Because SoftwareSerial truncates pure strings, save json as a char

  // How many bytes the server should expect , how many seconds/1000 the server should wait for those bytes. Set to 120 bytes for now, trouble calculating sizeof(json)
  // Set to 89 if no date time
  // Set to 120 if date time
  Serial1.println("AT+HTTPDATA=" + String(json.length()) + ",10000");

  delay(2000);

  updateSerial();

  delay(2000);
  updateSerial();
  Serial1.println(json);
  delay(5000);
  updateSerial();
  Serial1.println("AT+HTTPACTION=1"); // 1 for post, 0 for get

  delay(5000);

  updateSerial();

  Serial1.println("AT+HTTPREAD"); // Read response, should be 1, 500, 21 and also will say Internal server error even though data has uploaded

  delay(5000);

  updateSerial();

  delay(1000);

}


float readFluorescence()
{
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
  Serial.println(volt);
  return volt;
}


float voltage(float adc, int gain)
{
  float V;
  switch (gain)
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


int SetGain(int ADS1115Pin) {

  while (1) // this function constantly adjusts the gain to an optimum level
  {
    adc = ads.readADC_SingleEnded(2);   // get avg ADC value
    Serial.println(g);
    if (adc >= 30000 && g > 0) // if ADC is getting pegged at maximum value and is not the widest voltage range already, reduce the gain
    {
      g--;
      ads.setGain(gain[g]);
    }
    else if (adc <= 7000 && g < 5)
    {
      g++;
      ads.setGain(gain[g]);
    }
    else
      return g;
  }
}


void setup()
{
  //
//  digitalWrite(DONEPIN, LOW);
  Serial.begin(57600); //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)

  Serial1.begin(57600); //Begin serial communication with Arduino and SIM808

  delay(100);

  ads.begin();

  Serial1.println("AT"); //Once the handshake test is successful, it will back to OK

  updateSerial(); // Return the response to the serial port for display purposes, and print anything from either serial or SoftwareSerial. May be able to remove in actual deployment pending testing

  Serial1.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best

  delay(1000);

  updateSerial();

  Serial1.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged in

  delay(1000);

  updateSerial();

  Serial1.println("AT+CREG?"); //Check whether it has registered in the network

  delay(1000);

  updateSerial();

  Serial1.println("AT+CGREG?"); // Check to see if the device is registered again

  delay(1000);

  updateSerial();

  Serial1.println("AT+COPS?"); // Returns the mobile network name i.e. T-mobile

  delay(1000);

  updateSerial();

  Serial1.println("AT+cgatt=1");

  delay(1000);

  updateSerial();

  Serial1.println("AT+CMGF=1"); // Set to SMS text mode

  delay(3000);

  updateSerial();

  Serial1.println("AT+SAPBR=3,1,Contype,GPRS"); // Set connection type to GPRS

  delay(3000);

  updateSerial();

  Serial1.println("AT+SAPBR=3,1,APN,hologram"); // Change "TM" to the APN provided by your carrier

  delay(3000);

  updateSerial();

  Serial1.println("AT+CGACT=1,1"); // Perform GPRS attach, which must occur befpre PDP context can be established

  delay(3000);

  updateSerial();

  Serial1.println("AT+SAPBR=1,1"); // Enable bearer 1

  delay(3000);

  updateSerial();

  Serial1.println("AT+SAPBR=2,1"); // Check whether bearer 1 is open

  delay(3000);

  updateSerial();

  Serial1.println("AT+HTTPINIT"); // Initialize HTTP service

  delay(3000);

  updateSerial();

  Serial1.println("AT+HTTPPARA=CID,1"); // Set bearer profile ID

  delay(3000);

  updateSerial();

  Serial1.println("AT+HTTPPARA=URL,http://52.26.55.255:8080/api/v0p1/sensor"); // Server address

  delay(3000);

  updateSerial();

  Serial1.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");

  delay(3000);

  updateSerial();

  delay(1000);

  UplinkData(fluorescence, readFluorescence());

  delay(4000);

  pinMode(DONEPIN, OUTPUT);
  
  digitalWrite(DONEPIN, HIGH);
}

void loop(){
  
}
