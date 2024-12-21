#include <SPI.h>
#include <SD.h>

const int chipSelect = 4; // Change this to match your SD card module's CS pin

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("Initialization failed!");
    return;
  }
  Serial.println("Initialization done.");

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  if (dataFile) {
    for (int i = 1; i <= 1000; i++) {
      dataFile.print("Record ");
      dataFile.println(i);
    }
    dataFile.close();
    Serial.println("Data written to datalog.txt");
  } else {
    Serial.println("Error opening datalog.txt");
  }
}

void loop() {
  // Nothing to do here
}