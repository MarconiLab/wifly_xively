//Author: Rodrigo Carbajales MarconiLab
#include <SoftwareSerial.h>
#include <HttpClient.h>
#include <Xively.h>
#include <WiFlyClient.h>

#define SSID      "MarconiLab"
#define KEY       "marconi-lab"
#define AUTH      WIFLY_AUTH_WPA2_PSK
int keyIndex = 0;            // your network key Index number (needed only for WEP)

// Your Xively key to let you upload data
char xivelyKey[] = "oJ4Uwv72MJx64uasw32iMMm8Jj5f0ygjnJkJxXSClEqtWg64";

// Analog pin which we're monitoring (0 and 1 are used by the Ethernet shield)
int sensorPin = 2;

// Define the strings for our datastream IDs
char sensorId[] = "Sound";
XivelyDatastream datastreams[] = {
  XivelyDatastream(sensorId, strlen(sensorId), DATASTREAM_FLOAT),
};
// Finally, wrap the datastreams into a feed
XivelyFeed feed(863474413, datastreams, 1 /* number of datastreams */);

WiFlyClient wiFlyClient;
XivelyClient xivelyclient(wiFlyClient);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  Serial.println("Starting single datastream upload to Xively...");
  Serial.println();
  
  // wait for initilization of wifly
  delay(3000);
  
  // attempt to connect to Wifi network:
  Serial.println("Join " SSID );
  while(!wiFlyClient.join(SSID, KEY, AUTH)) {
    Serial.println("connect network error! try again ...");
    delay(2000);
  }
}

void loop() {
//    Serial.println("Join " SSID );
//  while(!wiFlyClient.join(SSID, KEY, AUTH)) {
//    Serial.println("connect network error! try again ...");
//    delay(2000);
//  }
  int sensorValue = analogRead(sensorPin);
  //int sensorValue = 130;
  datastreams[0].setFloat(sensorValue);

  Serial.print("Read sensor value ");
  Serial.println(datastreams[0].getFloat());
//delay(5000);
  Serial.println("Uploading it to Xively");
  int ret = xivelyclient.put(feed, xivelyKey);
  Serial.print("xivelyclient.put returned ");
  Serial.println(ret);

  Serial.println();
//  wiFlyClient.sleep();
  delay(15000);
}
