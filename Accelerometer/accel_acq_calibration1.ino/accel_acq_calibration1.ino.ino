/*
 Arduino code to read acceleratometer data for Z-axis. 
 Francis Monaja & Anush Maria
*/
#include <Wire.h>
const int numAngles = 21;
const int angles[numAngles] = {540};
// const int angles[numAngles] = {0,36, 72, 108, 144, 180, 216, 252, 288, 324, 360, 396, 432, 468, 504, 540, 576, 612, 648, 684, 720 };
float readings[numAngles];
#define outputA 2
#define outputB 3

int counter = 0;
int aState;
int aLastState;
int currentAngle = 360;

const int MPU = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

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
}

void loop() {
  for (int i = 0; i < numAngles; i++) {
    Serial.print("Move to angle ");
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
  while (1)
    ;
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
    currentAngle = 3(counter * 12);
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
  for (int i = 0; i < 1000; i++) {
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
  }
  average = sum / 1000;
  Serial.print("|Average: ");
  Serial.println(average);
  return average;
}
'




void displayResults() {
  Serial.println("Angle, Reading");
  for (int i = 0; i < numAngles; i++) {
    Serial.print(angles[i]);
    Serial.print(", ");
    Serial.println(readings[i]);
  }
}