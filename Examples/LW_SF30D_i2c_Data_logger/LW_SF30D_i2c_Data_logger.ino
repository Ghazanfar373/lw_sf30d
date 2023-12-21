// www.Lightware.co.za          July 2020
// Lightware example code using the lw_sf30.h library
// This example enables the use of the I2C for communicaiton to the sf30
// and Serial Interface to the Serial Monitor on the Computer

// Refer to the Readme.txt file for the list of available function andvariables 

#include <lw_sf30d.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

LW_SF30 sf30(1, Serial);
//SD card setup---------------------------------------------------------------------------------
const int chipSelect = 4;
//int power = 9;


void setup() {
  //this is the serial port for the terminal window
  Serial.begin(115200);

  //--SD Card Setup--------------------------------------------------------------------------

    //pinMode(9, OUTPUT);
   // digitalWrite(power, HIGH);
    Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) 
  {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("Card initialized.");
//------------------------------------------------------------------------------------------

  //Switch I2C to Binary Mode
  //Have to send the three byte 0x78,0xAA,0xAA to unit at start to switch to Binary mode
  Wire.beginTransmission(sf30.I2CAddress);
  Wire.write(120);    // Set to Binary mode
  Wire.write(170);    // Set to Binary mode
  Wire.write(170);    // Set to Binary mode
  Wire.endTransmission();

  // read the Hardware model from the sf30. The 1 passed to the function
  // will enable the display of the result on the Serial Terminal.
  sf30.i2cReadHardwareModel(1);
  delay(100);
  sf30.i2cReadHardwareModel(1);
  delay(100);
  sf30.i2cReadHardwareVersion(1);
  delay(100);
  // Select default setting for distance output values
  sf30.i2cWriteSelectDistanceOutputValues(255); 
  delay(100);

  // Set the update rate
  sf30.i2cWriteSamplingRate(9);
  delay(100);

  // Enable the Median Filter
  sf30.i2cWriteMedianEnable(1);
  delay(100);

  // Change the Median Filtersize
  sf30.i2cWriteMedianFilter(32);
  delay(100);

  // Enable the Smoothing Filter
  sf30.i2cWriteSmoothingEnable(1);
  delay(100);

  // Change the Smoothing Filter size
  sf30.i2cWriteSmoothingFilter(90);
  delay(100);
}

void loop() {

  // request the distance values in cm over the I2C
  // The values will be saved in the global variables
  sf30.i2cReadDistanceOutputValues(0);
  
  // print the distances, save in the global variables, on the Serial Monitor
    Serial.print(sf30.firstRaw_cm,DEC);
    Serial.print(" ");
    Serial.print(sf30.firstFiltered_cm,DEC);
    Serial.print(" ");
    Serial.print(sf30.firstStrength_cm,DEC);
    Serial.print(" ");
    Serial.print(sf30.lastRaw_cm,DEC);
    Serial.print(" ");
    Serial.print(sf30.lastFiltered_cm,DEC);
    Serial.print(" ");
    Serial.print(sf30.lastStrength_cm,DEC);
    Serial.print(" ");
    Serial.print(sf30.backgroundNoise,DEC);
    Serial.print(" ");
    Serial.println(sf30.APDTemperature,DEC);

  delay(1);
  
  // put your main code here, to run repeatedly:
    float distance = sf30.lastRaw_cm;
    String dataString = "";
    dataString += String(distance);
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    dataFile.println(dataString);
    dataFile.close();
    delay(10);
 
}
