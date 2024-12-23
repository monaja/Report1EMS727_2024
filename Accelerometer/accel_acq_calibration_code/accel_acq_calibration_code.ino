
#include <Wire.h>
#include <dht.h>
#include <SPI.h>
#include <SD.h>
int fileCounter = 0;

double temperature = 0.0;
const int chipSelect = 4;

const int numAngles = 21;
const int angles[numAngles] = { 0 }; //here we add the code to test one at a time
// const int angles[numAngles] = {0,36, 72, 108, 144, 180, 216, 252, 288, 324, 360, 396, 432, 468, 504, 540, 576, 612, 648, 684, 720 };
float readings[numAngles];
#define outputA 2
#define outputB 3

#define DHT11_PIN 8
#define DATA_SIZE 1
#define Y_SAMPLE_SIZE 1000


int counter = 0;
int aState;
int aLastState;
int currentAngle = 360;

const int MPU = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;


double data_x[DATA_SIZE];
float data_y[DATA_SIZE];

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  // Initialize the rotary encoder
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA);


  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

String createFileName() {
  char fileName[15];
  snprintf(fileName, sizeof(fileName), "DATA3%03d.TXT", fileCounter++);
  return String(fileName);
}

void loop() {
  for (int i = 0; i < numAngles; i++) {
    Serial.print("Move to angle: ");
    Serial.print(angles[i]);
    Serial.println(" and enter 1 to continue");
    while (Serial.read() != '1') {
      delay(100);
    }
    waitForAngle(angles[i]);
    delay(1000);

    readings[i] = getAverageReading();
  }
  displayResults();

  //cabrate the code 
  /**
  what do i need ? compute the slope and the offset so we are using linear regression

  */
}

void readEncoder() {
  aState = digitalRead(outputA);
  if (aState != aLastState) {
    if (digitalRead(outputB) != aState) {
      counter++;
    } else {
      counter--;
    }
    Serial.print("Position: ");
    Serial.println(counter);
    Serial.print("Angle: ");
    currentAngle = 0 + (counter * 12); //change to 360 after 360 angles
    Serial.println(currentAngle);
  }
  aLastState = aState;
}
void waitForAngle(int targetAngle) {
  while (true) {
    readEncoder();  // Normalize angle to 0-359
    Serial.print("Current angle: ");
    Serial.println(currentAngle);
    if (currentAngle == targetAngle) {
      break;
    }
  }
}

float getAverageReading() {
  float sum = 0, average = 0;

  String fileName = createFileName();
  Serial.print("Creating file: ");
  Serial.println(fileName);

  // Serial.println("Data written to file.");
  File dataFile = SD.open(fileName, FILE_WRITE);

  if (dataFile) {

    dataFile.print(currentAngle);
    dataFile.println("degrees,");
    for (int i = 0; i < Y_SAMPLE_SIZE; i++) {
      Wire.beginTransmission(MPU);
      Wire.write(0x3B);
      Wire.endTransmission(false);
      Wire.requestFrom(MPU, 12, true);
      AcX = Wire.read() << 8 | Wire.read();
      AcY = Wire.read() << 8 | Wire.read();
      AcZ = Wire.read() << 8 | Wire.read();
      GyX = Wire.read() << 8 | Wire.read();
      GyY = Wire.read() << 8 | Wire.read();
      GyZ = Wire.read() << 8 | Wire.read();
      Serial.print("Accelerometer: ");
      Serial.print(" | Z = ");
      Serial.println(AcZ);
      sum += AcZ;
      delay(30);
      dataFile.print(AcZ);
      dataFile.println(",");
      if (i % 50 == 0) { dataFile.flush(); }
    }
  } else {
    Serial.println("error opening datalog1.csv");
  }
  dataFile.close();

  average = sum / 1000;
  Serial.print("|Average: ");
  Serial.println(average);
  return average;
}

void displayResults() {
  Serial.println("Angle, Reading");
  for (int i = 0; i < numAngles; i++) {
    Serial.print(angles[i]);
    Serial.print(", ");
    Serial.println(readings[i]);
  }
}