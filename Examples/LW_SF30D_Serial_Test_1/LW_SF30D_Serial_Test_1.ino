// www.Lightware.co.za          July 2020
// Lightware example code using the lw_sf30.h library
// This library enables the use of the I2C and Serial Interface

// This library is designed to use 2 Serial ports on the Arduino

#include <lw_sf30d.h>
#include <Wire.h>
#include <Nextion.h> 

LW_SF30 sf30(Serial1, Serial);

int distance=0;
int Green = 13; // the pin the LED is connected to
int Blue = 12; // the pin the LED is connected to
int Red = 11; // the pin the LED is connected to

void setup() {

//________________________________________________________
   pinMode(Green, OUTPUT); // Declare the LED as an output
   pinMode(Blue, OUTPUT); // Declare the LED as an output
   pinMode(Red, OUTPUT); // Declare the LED as an output

//__________________________________________________________
  
  //this is the serial port for the terminal window
  Serial.begin(115200);

  // Setup the Serial port for the sf30 interface
  Serial1.begin(115200);

  // Startup Nextion Serial
     Serial2.begin(9600); 

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
 /* if (new_data == 1){
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
    new_data = 0;
  }*/
  distance = sf30.lastRaw_cm;
  Serial.println(distance,DEC);

  // Decimal Display
  Serial2.print("x0.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial2.print(distance/10);  // This is the value you want to send to that screen as a decimal value. | divided by 10 is to convert 
  Serial2.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial2.write(0xff);
  Serial2.write(0xff);
// Gauge Display   
  Serial2.print("z0.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial2.print(distance/100);  // This is the value you want to send to that object and atribute mention before.
  Serial2.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial2.write(0xff);
  Serial2.write(0xff);

// Safe Zone        100m to 159m
            if ((distance >= 10000) && (distance <199999) )
          {
             digitalWrite(Green, HIGH); // Turn the LED on
             digitalWrite(Blue, LOW); // Turn the LED off
             digitalWrite(Red, LOW); // Turn the LED off
          } 

// Awareness         80m to 99m
            if ((distance <= 9900)  && (distance > 8000))
          {
             digitalWrite(Blue, LOW); // Turn the LED off
             digitalWrite(Red, LOW); // Turn the LED off
             digitalWrite(Green, HIGH); // Turn the LED on
             delay(20);
             digitalWrite(Green, LOW); // Turn the LED off
             delay(20);
          }
          
// Warning          20m to 79m
          if ((distance <=7900) && (distance > 2000))
          {
            digitalWrite(Green, LOW); // Turn the LED off
            digitalWrite(Red, LOW); // Turn the LED off
            digitalWrite(Blue, HIGH); // Turn the LED on
            delay(20);
            digitalWrite(Blue, LOW); // Turn the LED off
            delay(20);
          }
          
// Danger           less than 19m
          if ((distance <=1900) ){
             digitalWrite(Green, LOW); // Turn the LED off
             digitalWrite(Blue, LOW); // Turn the LED off
             digitalWrite(Red, HIGH); // Turn the LED on
             delay(20);
             digitalWrite(Red, LOW); // Turn the LED off
             delay(20);
          }

          
        if (distance >= 20000) 
        {
          Serial.println("Lost signal");
          digitalWrite(Blue, LOW); // Turn the LED on
          digitalWrite(Green, LOW); // Turn the LED on
          digitalWrite(Red, HIGH); // Turn the LED on
        } 

  // put your main code here, to run repeatedly:
  
}
