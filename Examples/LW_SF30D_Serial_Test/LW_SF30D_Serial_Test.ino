// www.Lightware.co.za          July 2020
// Lightware example code using the lw_sf30.h library
// This library enables the use of the I2C and Serial Interface

// This library is designed to use 2 Serial ports on the Arduino

#include <lw_sf30d.h>
#include <Wire.h>

LW_SF30 sf30(Serial1, Serial);

float distance=0;

void setup() {
  //this is the serial port for the terminal window
  Serial.begin(115200);

  // Setup the Serial port for the sf30 interface
  Serial1.begin(115200);

  // Request the sf30 Hardware Name
  sf30.readRequestHardwareName();
  delay(100);
  // Read the data sent from the sf30
  sf30.ProcessSerialInput(1);
  delay(100);

  // Disable any possible streaming data
  sf30.writeDataStreamType(0);
  delay(100);
  // Read the data sent from the sf30
  sf30.ProcessSerialInput(1);
  delay(100);

  
  // Request the sf30 Hardware Name
  sf30.readRequestHardwareName();
  delay(100);
  // Read the data sent from the sf30
  sf30.ProcessSerialInput(1);
  delay(100);

  // Request the sf30 Firmware Version
  sf30.readRequestFirmwareVersion();
  delay(100);
  // Read the data sent from the sf30
  sf30.ProcessSerialInput(1);
  delay(100);

  // Request the streaming output distance data selection
  sf30.writeDistOutConfig(255);
  //sf30.readRequestDistOutConfig();
  delay(100);
  // Read the data sent from the sf30
  sf30.ProcessSerialInput(1);
  delay(100);
  
  // Set the streaming to distance in cm
  sf30.writeDataStreamType(5);
  delay(100);
  // Read the data sent from the sf30
  sf30.ProcessSerialInput(1);
  delay(100);
  
}

void loop() {
  uint8_t new_data = 0;
  // Every cycle check the Serial recieve buffer for data and then process it
  new_data = sf30.ProcessSerialInput(0);

  // if new data was recieved, then display the following first and last distance
  if (new_data == 1){
    Serial.print(sf30.firstRaw_cm,DEC);
    Serial.print(" ");
    Serial.print(sf30.firstFiltered_cm,DEC);
    Serial.print(" ");
    Serial.print(sf30.firstStrength_cm,DEC);
    Serial.print(" ");
    Serial.print(sf30.lastRaw_cm,DEC);
    Serial.print(" ");
    Serial.print(sf30.lastFiltered_cm,DEC);
    distance = sf30.lastFiltered_cm;
    Serial.print(" ");
    Serial.print(sf30.lastStrength_cm,DEC);
    Serial.print(" ");
    Serial.print(sf30.backgroundNoise,DEC);
    Serial.print(" ");
    Serial.println(sf30.APDTemperature,DEC);
    new_data = 0;
  }
  
  // put your main code here, to run repeatedly:
  
}
