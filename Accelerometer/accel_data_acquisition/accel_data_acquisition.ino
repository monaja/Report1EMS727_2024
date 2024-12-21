/* 
writing code to prompt user to enter the angle they want to measure. 
+ please enter the angle you want to measure. 
+ please position you your accelerometer to the angle
+ if position is correct. 
+ Wait for 1 second. 
+ Reading... 
+ read about 1000 data points from the sensor. Need to store the data to disk as file.
+ 
*/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SD.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
const int chipSelect = 10;

void setup() {
    Serial.begin(9600);
    if (!accel.begin()) {
        Serial.println("No ADXL345 detected");
        while (1);
    }
    if (!SD.begin(chipSelect)) {
        Serial.println("SD card initialization failed!");
        while (1);
    }
    Serial.println("Please enter the angle you want to measure:");
}

void loop() {
    if (Serial.available() > 0) {
        String angle = Serial.readStringUntil('\n');
        Serial.print("Please position your accelerometer to the angle: ");
        Serial.println(angle);
        delay(1000);
        Serial.println("Reading...");
        
        File dataFile = SD.open("accel_data.txt", FILE_WRITE);
        if (dataFile) {
            for (int i = 0; i < 1000; i++) {
                sensors_event_t event;
                accel.getEvent(&event);
                dataFile.print(event.acceleration.x);
                dataFile.print(",");
                dataFile.print(event.acceleration.y);
                dataFile.print(",");
                dataFile.println(event.acceleration.z);
                delay(1);
            }
            dataFile.close();
            Serial.println("Data saved to accel_data.txt");
        } else {
            Serial.println("Error opening accel_data.txt");
        }
        while (1);
    }
}
