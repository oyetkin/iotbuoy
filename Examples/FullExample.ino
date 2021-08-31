/*
 * Install the following libraries:
 * Adafruit BME280
 * Adafruit Unified Sensor
 *
 * Author: Alex Horvath, Analytical Mechanics Associates
 * With code contributed from Arjun Tambe
 *
 */

#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <TinyGPS++.h>
#include <avr/wdt.h>
#include "RTClib.h"
#include <SPI.h>
#include <SD.h>

//Create software serial object to communicate with SIM808. Pin 7 is RX on GPRS/GPS/GSM shield and pin 8 is TX for the robotshop GPS/GPRS/GSM shield here
// https://www.robotshop.com/en/sim808-gps-gprsgsm-arduino-shield-mkf.html?gclid=EAIaIQobChMIl-Hpytn58QIVdGxvBB3DMgZVEAQYDSABEgJUg_D_BwE
// If you are using a different GSM/GPS/GPRS module, use the RX/TX pins given in the board specification.

Adafruit_BME280 bme; // Create a BME 280 instance
RTC_PCF8523 rtc; // Create a real time clock instance
TinyGPSPlus gps;
String device_name = "IoT_Station_2"; // Name your station
String dataout;
File myFile;

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
Measurement pressure = {80000.0, 1.0, "Pa", "pressure", 30000, 140000, "BME280"};
Measurement temperature = {0.0, 0.01, "Celsius", "temperature", -40, 85, "BME280"};
Measurement humidity = {0, 0.01, "Relative %", "humidity", 0, 100, "BME280"};

void setup()
{    
    
    if (! rtc.begin()) { // Flush serial, this is necessary for the program to work
    Serial.flush();
    abort();
  }
  rtc.start();  

  Serial.begin(57600); //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  
  Serial1.begin(57600); //Begin serial communication with Arduino and SIM808

  delay(100);
  
  }


void Initialize()
{ 
  bme.begin(); // Initialize the BME 280
  
  Serial1.println("AT"); //Once the handshake test is successful, it will back to OK
  
  updateSerial(); // Return the response to the serial port for display purposes, and print anything from either serial or SoftwareSerial. May be able to remove in actual deployment pending testing
  
  Serial1.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  
  delay(3000);
  
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
  
  Serial1.println("AT+SAPBR=3,1,APN,TM"); // Change "TM" to the APN provided by your carrier
  
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

//  if (!SD.begin()) {
//    while (1);
//  }
//  if (SD.exists("data.txt")){
//  SD.remove("data.txt");
//  }
}

void updateSerial()
{
  delay(20);
  while (Serial.available()) 
  {
    Serial1.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(Serial1.available()) 
  {
    Serial.write(Serial1.read());//Forward what Software Serial received to Serial Port
  }
}

void UplinkData(measurement m, float dataval)
{
  Serial.flush(); // Make sure that serial is flushed
  
  Serial1.flush(); // Make sure software serial is flushed
    
  delay(2000);
  DateTime now = rtc.now();
  String json = "{\"key\":\"" + device_name + "\",\"measurement_name\":\"" + m.type + "\",\"unit\":\"" + m.unit +"\",\"value\":" + String(dataval) + ",\"timestamp\":\"" + String(now.month()) + "/" + String(now.day()) + "/" + String(now.year()) + " " + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + "\",\"lat\":\"" +  String(gps.location.lat()) + "\",\"lon\":\"" + String(gps.location.lng()) + "\"}";
  //  const char *fulljson = json.c_str(); // Because SoftwareSerial truncates pure strings, save json as a char

  // How many bytes the server should expect , how many seconds/1000 the server should wait for those bytes. Set to 120 bytes for now, trouble calculating sizeof(json)
  // Set to 89 if no date time
  // Set to 120 if date time
  Serial1.println("AT+HTTPDATA=" + String(json.length()) + ",10000"); 
  
  delay(2000);
  
  updateSerial();
  
  delay(2000);
  updateSerial();
  Serial1.println("{\"key\":\"" + device_name + "\",\"measurement_name\":\"" + m.type + "\",\"unit\":\"" + m.unit +"\",\"value\":" + String(dataval) + ",\"timestamp\":\"" + String(now.month()) + "/" + String(now.day()) + "/" + String(now.year()) + " " + String(now.hour()) + "-" + String(now.minute()) + "-" + String(now.second()) + "\",\"lat\":\"" +  String(gps.location.lat()) + "\",\"lon\":\"" + String(gps.location.lng()) + "\"}"); // Send the json string
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

void DownlinkData()
{
  Serial1.println("AT+HTTPACTION=0"); // 1 for post, 0 for get
 
  delay(5000);  
  
  updateSerial();
  
  Serial1.println("AT+HTTPREAD"); // Read response, should be 0, 200, number of bytes/bits? transmitted
  
  delay(5000);
  
  updateSerial();
  
  Serial1.println("AT+HTTPTERM"); // Terminate HTTP session
  
  delay(1000);
  
  updateSerial();
  
  Serial1.println("AT+SAPBR=0,1"); // Close bearer
  
  updateSerial();
}


void SDWrite(String device_name, Measurement m, float dataval, String timestr, String coords){

  myFile = SD.open("data.txt", FILE_WRITE);
  myFile.println("{\"key\":\"" + device_name + "\",\"measurement_name\":\"" + m.type + "\",\"unit\":\"" + m.unit + "\",\"value\":" + String(dataval) + "\",\"timestamp\":\"" + "\",\"lat\":\"" +  String(gps.location.lat()) + "\",\"lon\":\"" + String(gps.location.lng()) + "}"); // Creates post string
  myFile.close();
}

String SDRead(){
  myFile = SD.open("data.txt");
  while (myFile.available()) {
  dataout = String(myFile.read());
    }
  myFile.close();
  SD.remove("data.txt");
  return dataout;
}

void loop()
{
  Initialize();

  delay(1000);  
  
  UplinkData(temperature, bme.readTemperature()); // Read temperature
  
  delay(1000);
  
  UplinkData(pressure, bme.readPressure()); // Read pressure

  delay(1000);
  
  UplinkData(humidity, bme.readHumidity()); // Read humidity
  
  delay(1000);

}
