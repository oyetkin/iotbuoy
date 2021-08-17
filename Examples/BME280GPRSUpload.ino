/*
 * Install the following libraries:
 * Adafruit BME280
 * Adafruit Unified Sensor
 *
 * Author: Alex Horvath, Analytical Mechanics Associates
 * With code contributed from Arjun Tambe
 *
 */

#include <SoftwareSerial.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

//Create software serial object to communicate with SIM808. Pin 7 is RX on GPRS/GPS/GSM shield and pin 8 is TX for the robotshop GPS/GPRS/GSM shield here
// https://www.robotshop.com/en/sim808-gps-gprsgsm-arduino-shield-mkf.html?gclid=EAIaIQobChMIl-Hpytn58QIVdGxvBB3DMgZVEAQYDSABEgJUg_D_BwE
// If you are using a different GSM/GPS/GPRS module, use the RX/TX pins given in the board specification.
SoftwareSerial mySerial(7, 8); 

Adafruit_BME280 bme; // Create a BME 280 instance

String device_name = "IoT_Station_1"; // Name your station

float lat = 38.0;
float lon = -76.0;

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
  Serial.begin(38400); //Begin serial communication with Arduino and Arduino IDE (Serial Monitor) 
  
  mySerial.begin(38400); //Begin serial communication with Arduino and SIM808
  
  bme.begin(); // Initialize the BME 280
  
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  
  updateSerial(); // Return the response to the serial port for display purposes, and print anything from either serial or SoftwareSerial. May be able to remove in actual deployment pending testing
  
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  
  delay(3000);
  
  updateSerial();
  
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged in
  
  delay(1000);
  
  updateSerial();
  
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  
  delay(1000);
  
  updateSerial();
  
  mySerial.println("AT+CGREG?"); // Check to see if the device is registered again
  
  delay(1000);
  
  updateSerial();
  
  mySerial.println("AT+COPS?"); // Returns the mobile network name i.e. T-mobile
  
  delay(1000);
  
  updateSerial();
  
  mySerial.println("AT+cgatt=1"); 
  
  delay(1000);
  
  updateSerial();
  
  mySerial.println("AT+CMGF=1"); // Set to SMS text mode
  
  delay(3000);
  
  updateSerial();
  
  mySerial.println("AT+SAPBR=3,1,Contype,GPRS"); // 
  
  delay(3000);
  
  updateSerial();
  
  mySerial.println("AT+SAPBR=3,1,APN,TM"); // Change "TM" to the APN provided by your carrier
  
  delay(3000);
  
  updateSerial();
  
  mySerial.println("AT+CGACT=1,1"); // Perform GPRS attach, which must occur befpre PDP context can be established
  
  delay(3000);
  
  updateSerial();
  
  mySerial.println("AT+SAPBR=1,1"); // Enable bearer 1
  
  delay(3000);
  
  updateSerial();
  
  mySerial.println("AT+SAPBR=2,1"); // Check whether bearer 1 is open
  
  delay(3000);
  
  updateSerial();
  
  mySerial.println("AT+HTTPINIT"); // Initialize HTTP service
  
  delay(3000);
  
  updateSerial();
  
  mySerial.println("AT+HTTPPARA=CID,1"); // Set bearer profile ID
  
  delay(3000);
  
  updateSerial();
  
  mySerial.println("AT+HTTPPARA=URL,http://52.26.55.255:8080/api/v0p1/sensor"); // Server address
  
  delay(3000);
  
  updateSerial();
  
  mySerial.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  
  delay(3000);
  
  updateSerial();
}

void updateSerial()
{
  delay(20);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}

void UplinkData(float dataval, Measurement m)
{
  Serial.flush(); // Make sure that serial is flushed
  
  mySerial.flush(); // Make sure software serial is flushed
  
  String json = "{\"key\":\"" + device_name + "\",\"measurement_name\":\"" + m.type + "\",\"unit\":\"" + m.unit + "\",\"value\":" + String(dataval) + "}"; // Creates post string
  
  const char *fulljson = json.c_str(); // Because SoftwareSerial truncates pure strings, save json as a char
  
  mySerial.println("AT+HTTPDATA=120,100000"); // How many bytes the server should expect , how many seconds/1000 the server should wait for those bytes. Set to 120 bytes for now, trouble calculating sizeof(json)
  
  delay(1000);
  
  updateSerial();
  
  mySerial.println(fulljson); // Send the json string
  
  delay(5000);
  
  mySerial.println("AT+HTTPACTION=1"); // 1 for post, 0 for get
  
  delay(5000);
  
  updateSerial();
  
  mySerial.println("AT+HTTPREAD"); // Read response, should be 1, 500, 21 and also will say Internal server error even though data has uploaded
  
  delay(5000);
  
  updateSerial();

//  mySerial.println("AT+HTTPTERM"); // Terminate HTTP session

//  delay(1000);

//  updateSerial();

//  mySerial.println("AT+SAPBR=0,1"); // Close bearer

//  updateSerial();

}

void DownlinkData()
{
  mySerial.println("AT+HTTPACTION=0"); // 1 for post, 0 for get
 
  delay(5000);  
  
  updateSerial();
  
  mySerial.println("AT+HTTPREAD"); // Read response, should be 0, 200, number of bytes/bits? transmitted
  
  delay(5000);
  
  updateSerial();
  
  mySerial.println("AT+HTTPTERM"); // Terminate HTTP session
  
  delay(1000);
  
  updateSerial();
  
  mySerial.println("AT+SAPBR=0,1"); // Close bearer
  
  updateSerial();
}


void loop()
{
  UplinkData(bme.readTemperature(),temperature); // Read temperature
  
  delay(20);
  
  UplinkData(bme.readPressure(), pressure); // Read pressure
  
  delay(20);
  
  UplinkData(bme.readHumidity(), humidity); // Read humidity
  
  delay(20);
}
