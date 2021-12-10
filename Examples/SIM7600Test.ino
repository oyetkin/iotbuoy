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

Measurement voltmsr = {0, 0.01, "Volts", "voltage", 0, 100, "Volt Meter"};

String device_name = "Porcupine_2"; // Name your station

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
  String json = "{\"key\":\"" + device_name + "\",\"measurement_name\":\"" + m.type + "\",\"unit\":\"" + m.unit + "\",\"value\":" + String(dataval) + ",\"timestamp\":\"11/11/2021 11:11:11\",\"lat\":\"30\",\"lon\":\"30\"}";
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


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)

  Serial1.begin(115200); //Begin serial communication with Arduino and SIM808

  delay(100);

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

  Serial1.println("AT+SAPBR=3,1,Contype,GPRS"); // Set connection type to LTE

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

}

void loop() {
  // put your main code here, to run repeatedly:
  
  UplinkData(voltmsr, 40);

}
