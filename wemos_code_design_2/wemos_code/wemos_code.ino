/*
  E122 - Wemos With MQTT and DHT11 - Version 0.1
  Updated: February 20th, 2018. at 4:07 PM.

  Integrated from components picked off the net by Prof.KP.
  Check  the configuration section for what you can tinker with.
  Modify code on your own risk.... But, ... do take risks....

********/
/*  Installation of drivers and other set up needed - Check CANVAS...

  To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"
*/


#include <ESP8266WiFi.h>
#include "PubSubClient.h"
#include "info.h"
#include "DHT.h"
// Your sketch must #include this library, and the Wire library.
// (Wire is a standard library included with Arduino.):

#include <SFE_BMP180.h>
#include <Wire.h>

// CONFIGURATION SETTINGS ....BEGIN

//Wifi Settings
//const char* ssid = "DLabsPrivate1";
//const char* password = "L3tsM@keSometh1n";
const char* ssid = "Stevens-Media";
const char* password = "Stevens1870";
// ANY WEMOS WITH A STICKER ON THE BACK IS REGISTERED TO THE NETWORK...
// THOSE WITHOUT THE STICKERS DO NOT WORK...


//MQTT Settings
const char* mqtt_server = "155.246.18.226";
const char* MQusername = "jojo";
const char* MQpassword = "hereboy";
// This magic word is added to the topic for control messages E122/<MAC4>/Control/MAGIC_WORD Param, Value
// Params Accepted PUBLISH_DELAY  VALUE in ms
//                 SLEEP_DELAY VALUE in ms
//
const char* MAGIC_WORD = "XYZZYPQQRT";
#define PUBLISH_DELAY  10000
#define SLEEP_DELAY 2000
#define DEEP_SLEEP_SECONDS  10
//const char* mqtt_server = "broker.hivemq.com"; //This is a public server - no username/pwd
// Sleep delay is how long Wemos goes into sleep mode before re-checking --
// May help conserve power in the field -- you may have to check.
// Want to put it in Deepsleep while in field -else will burn through batteries. - power conserve mode...
// convert to microseconds
//ESP.deepSleep(sleepSeconds * 1000000);



//Set up the DHT11
#define DHTPIN 4 //This is GPIO4 which is WeMos D2. Probably just hide this from students?????
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);






//Set up anemometer
#define signalPin 13
//GPIO13 in  WeMos D1 R2 is D7
bool mode_1_rpm = false;
bool mode_2_rpm = not mode_1_rpm;
bool mode_1_speed = false;
bool mode_2_speed = not mode_1_speed;

double current_time_rpm = 0;
double previous_time_rpm = 0;
bool print_now_rpm = false;
double current_time_speed = 0;
double previous_time_speed = 0;
bool print_now_speed = false;

unsigned int diameter = 1; //in feet
unsigned int num_decimal = 2;
unsigned int rpm_pin = 2;
unsigned int speed_pin = 3;
unsigned int delay_time = 10; //ms
double rpm_data = 0;
double speed_data = 0;







//Set-up BMP180 Temp Altimeter sensor




int measured_altitude = 0;
int measured_temp = 0;
int measured_pressure = 0;

// You will need to create an SFE_BMP180 object, here called "pressure":

SFE_BMP180 pressure;

#define ALTITUDE 7.925 // Altitude of Hoboken, NJ, in meters

void setup_alt_temp()
{
  Serial.begin(9600);
  Serial.println("REBOOT");

  // Initialize the sensor (it is important to get calibration values stored on the device).

  if (pressure.begin())
    Serial.println("BMP180 init success");
  /*
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }
  */
}








//MQTT  - 5000 ms is 5 sec.


//
//Note that since this is a real Wemos board -- it runs forever as opposed to
// the fakemos -- http://www.dmi.stevens.edu/fakemos/

// CONFIGURATION SETTINGS ....END

WiFiClient espClient;
info board_info;
PubSubClient client(espClient);
long lastMsg = 0;
char msg1[20], msg2[20];
char MQTopic1[50], MQTopic2[50];
char ControlTopic[50];
char BoardMac4[5];
int value = 0;
float temp, hum, freq = 0;
int tm = 0;
int dt, ta, ha;


void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // Board Last 4.
  BoardMac4[0] = board_info.mac()[12];
  BoardMac4[1] = board_info.mac()[13];
  BoardMac4[2] = board_info.mac()[15];
  BoardMac4[3] = board_info.mac()[16];
  BoardMac4[4] = '\0';
  //
  // Need the null termination for the string stuff to work, declare 1 extra character...
  //
  Serial.println(" MAC  4 of the board");
  Serial.println(BoardMac4);
  sprintf(MQTopic1, "E122/%4s/Temperature", BoardMac4);
  sprintf(MQTopic2, "E122/%4s/Humidity", BoardMac4);
  sprintf(ControlTopic, "E122/%4s/control/%s", BoardMac4, MAGIC_WORD);
  Serial.println("Setting the topics");
  Serial.println(MQTopic1);
  Serial.println(MQTopic2);
  Serial.println("This Wemos Control channel is");
  Serial.println(ControlTopic);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), MQusername, MQpassword)) {
      //    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish(MQtopic1, "00000");
      // ... and resubscribe ---- Dont subscribe KP
      // Wemos subscribes to its control channel E122/<mac4>/control
      client.subscribe(ControlTopic);
      // #KP - No announcements --- No Subscribes.
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode (signalPin, INPUT);
  Serial.begin(115200);
  delay(1000);
  Serial.println("********************************************************");
  Serial.println("* E 122 Design II: Field Sustainable Systems           *");
  Serial.println("*                                                      *");
  Serial.println("* Wemos Firmware with MQTT and DHT11 Support           *");
  Serial.println("*                                                      *");
  Serial.println("* Version 0.1  Feb 20 2018  (Stevens)                  *");
  Serial.println("********************************************************");
  Serial.print("Board Mac Address:");
  Serial.println(board_info.mac());
  setup_wifi();
  //setup_alt_temp();
  dht.begin();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  dt = now - lastMsg ;

  if (dt > PUBLISH_DELAY) {
    lastMsg = now;
    temp = dht.readTemperature(true);
    hum = dht.readHumidity();
    snprintf (msg1, 20, "%d", (int) temp);
    snprintf (msg2, 20, "%d", (int) hum);
    Serial.print("Published :" );
    Serial.print(MQTopic1);
    Serial.print(" with value: " );
    Serial.println(msg1);
    client.publish(MQTopic1, msg1);
    Serial.print("Published :" );
    Serial.print(MQTopic2);
    Serial.print(" with value: " );
    Serial.println(msg2);
    client.publish(MQTopic2, msg2);
    //loop_alt_temp();
    get_rpm_and_speed();
    //print the data:
    int avg_temp = (temp + measured_temp) / 2;
    Serial.println("Data:" + String(rpm_data, num_decimal) + "," + String(speed_data, num_decimal) + "," + String(avg_temp, num_decimal) + "," + String(hum, num_decimal) + "," + String(measured_altitude, num_decimal) + "," + String(measured_pressure, num_decimal) + ",");
  }
  //ESP.deepSleep(DEEP_SLEEP_SECONDS * 1000000);
  //digitalWrite(BUILTIN_LED, LOW);
  delay(SLEEP_DELAY);
  //digitalWrite(BUILTIN_LED, HIGH);
}













void get_rpm_and_speed() {
  // put your main code here, to run repeatedly:
  //RPM data input
  mode_1_rpm = digitalRead(signalPin);
  if (mode_1_rpm == mode_2_rpm) {
    mode_2_rpm = not mode_1_rpm;
    current_time_rpm = micros();
    if (print_now_rpm == true) {
      rpm_data = (1000000 * 60 / (current_time_rpm - previous_time_rpm)); //print the rpm
      print_now_rpm = not print_now_rpm;
    }
    else {
      print_now_rpm = not print_now_rpm;
    }
    previous_time_rpm = current_time_rpm;
  }

  //speed data input
  mode_1_speed = digitalRead(signalPin);
  if (mode_1_speed == mode_2_speed) {
    mode_2_speed = not mode_1_speed;
    current_time_speed = micros();
    if (print_now_speed == true) {
      //mph = rpm * 60min/hr * pi * diameter_of_wheel (feet) / 5280 ft/mile
      speed_data = (1000000 * 60 / (current_time_speed - previous_time_speed)) * (60 * PI * diameter / 5280); //print the rpm
      print_now_speed = not print_now_speed;
    }
    else {
      print_now_speed = not print_now_speed;
    }
    previous_time_speed = current_time_speed;
  }

  rpm_data = 700;
  speed_data = 60.55;
}



























//BMP 180 Temperature pressure sensor:



/* SFE_BMP180 library example sketch
This sketch shows how to use the SFE_BMP180 library to read the
Bosch BMP180 barometric pressure sensor.
https://www.sparkfun.com/products/11824
Like most pressure sensors, the BMP180 measures absolute pressure.
This is the actual ambient pressure seen by the device, which will
vary with both altitude and weather.
Before taking a pressure reading you must take a temparture reading.
This is done with startTemperature() and getTemperature().
The result is in degrees C.
Once you have a temperature reading, you can take a pressure reading.
This is done with startPressure() and getPressure().
The result is in millibar (mb) aka hectopascals (hPa).
If you'll be monitoring weather patterns, you will probably want to
remove the effects of altitude. This will produce readings that can
be compared to the published pressure readings from other locations.
To do this, use the sealevel() function. You will need to provide
the known altitude at which the pressure was measured.
If you want to measure altitude, you will need to know the pressure
at a baseline altitude. This can be average sealevel pressure, or
a previous pressure reading at your altitude, in which case
subsequent altitude readings will be + or - the initial baseline.
This is done with the altitude() function.
Hardware connections:
- (GND) to GND
+ (VDD) to 3.3V
(WARNING: do not connect + to 5V or the sensor will be damaged!)
You will also need to connect the I2C pins (SCL and SDA) to your
Arduino. The pins are different on different Arduinos:
Any Arduino pins labeled:  SDA  SCL
Uno, Redboard, Pro:        A4   A5
Mega2560, Due:             20   21
Leonardo:                   2    3
Leave the IO (VDDIO) pin unconnected. This pin is for connecting
the BMP180 to systems with lower logic levels such as 1.8V
Have fun! -Your friends at SparkFun.
The SFE_BMP180 library uses floating-point equations developed by the
Weather Station Data Logger project: http://wmrx00.sourceforge.net/
Our example code uses the "beerware" license. You can do anything
you like with this code. No really, anything. If you find it useful,
buy me a beer someday.
V10 Mike Grusin, SparkFun Electronics 10/24/2013
V1.1.2 Updates for Arduino 1.6.4 5/2015
*/

void loop_alt_temp()
{
  char status;
  double T,P,p0,a;

  // Loop here getting pressure readings every 10 seconds.

  // If you want sea-level-compensated pressure, as used in weather reports,
  // you will need to know the altitude at which your measurements are taken.
  // We're using a constant called ALTITUDE in this sketch:
  
  /*
  Serial.println();
  Serial.print("provided altitude: ");
  Serial.print(ALTITUDE,0);
  Serial.print(" meters, ");
  Serial.print(ALTITUDE*3.28084,0);
  Serial.println(" feet");
  */
  
  // If you want to measure altitude, and not pressure, you will instead need
  // to provide a known baseline pressure. This is shown at the end of the sketch.

  // You must first get a temperature measurement to perform a pressure reading.
  
  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      measured_temp = (9.0/5.0)*T+32.0; //deg F
      /*
      // Print out the measurement:
      Serial.print("temperature: ");
      Serial.print(T,2);
      Serial.print(" deg C, ");
      Serial.print((9.0/5.0)*T+32.0,2);
      Serial.println(" deg F");
      */
      
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          /*
          // Print out the measurement:
          Serial.print("absolute pressure: ");
          Serial.print(P,2);
          Serial.print(" mb, ");
          Serial.print(P*0.0295333727,2);
          Serial.println(" inHg");
          */
          // The pressure sensor returns abolute pressure, which varies with altitude.
          // To remove the effects of altitude, use the sealevel function and your current altitude.
          // This number is commonly used in weather reports.
          // Parameters: P = absolute pressure in mb, ALTITUDE = current altitude in m.
          // Result: p0 = sea-level compensated pressure in mb

          p0 = pressure.sealevel(P,ALTITUDE); // we're at 1655 meters (Boulder, CO)
          /*
          Serial.print("relative (sea-level) pressure: ");
          Serial.print(p0,2);
          Serial.print(" mb, ");
          Serial.print(p0*0.0295333727,2);
          Serial.println(" inHg");
          */
          measured_pressure = p0*0.0295333727; //in Hg

          // On the other hand, if you want to determine your altitude from the pressure reading,
          // use the altitude function along with a baseline pressure (sea-level or other).
          // Parameters: P = absolute pressure in mb, p0 = baseline pressure in mb.
          // Result: a = altitude in m.
          a = pressure.altitude(P,p0);
          /*
          Serial.print("computed altitude: ");
          Serial.print(a,0);
          Serial.print(" meters, ");
          Serial.print(a*3.28084,0);
          Serial.println(" feet");
          */
          measured_altitude = a*3.28084; //in feet from sea level
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");

  delay(5000);  // Pause for 5 seconds.
}
