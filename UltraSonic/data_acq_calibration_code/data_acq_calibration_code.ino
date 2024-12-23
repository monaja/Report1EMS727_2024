#include <dht.h>

#include <SPI.h>
#include <SD.h>
int fileCounter = 0; 

//int arrays y -> yTimetaken (us)
bool isReadNext = true;
bool isStop = false;
bool isRecalibrate = false;
float beta = 0.0;
float alpha = 0.0;
double temperature = 0.0;
const int chipSelect = 4;
// File dataFile;
//initialize variales 2:
// dht dhtTemp;
#define DHT11_PIN 8
#define DATA_SIZE 1
#define Y_SAMPLE_SIZE 1000
int trigPin = 5;
int echoPin = 6;

double data_x[DATA_SIZE];
float data_y[DATA_SIZE];
void setup() {
  // put your setup code here, to run once:

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  // Serial.println(dhtTemp.read11(DHT11_PIN));
  // Serial.print("Calibrating Ultrasonic Sensor::Getting Started at ");
  // Serial.print(dhtTemp.temperature);
  // Serial.println(" degrees celcius");

  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  // dataFile = SD.open("data.csv", FILE_WRITE);

  // if (!dataFile) { Serial.println("error initalizing file."); }
}

String createFileName(int currentAngle) {
  char fileName[15]; 
  snprintf(fileName, sizeof(fileName), "DATA_%dd.csv", currentAngle);
  return String(fileName);
}
void loop() {
  delay(500);

  // Serial.print("Enter 'r' to recalibrate: ");
  // char recalChar = Serial.read();
  //     Serial.println(recalChar);

  // if(recalChar == 'r'){
  //   isStop = false;
  // }
  delay(500);  // wait for a second

  while (!isStop) {
    delay(100);

    //collecting the data to be used for calibrating the sensors
    for (int i = 0; i < DATA_SIZE; i++) {
      float data_raw[Y_SAMPLE_SIZE];

      String fileName = createFileName(currentAngle);
      Serial.print("Creating file: ");
      Serial.println(fileName);

      // Serial.println("Data written to file.");
      File dataFile = SD.open(fileName, FILE_WRITE);


      Serial.print("Enter value ");
      Serial.print(i + 1);
      Serial.print("/");
      Serial.print(DATA_SIZE);
      Serial.print(" for distance in cm: ");
      float distValue;
      while (Serial.available() == 0) {
        distValue = Serial.parseFloat();
      }
      Serial.read();

      Serial.println(distValue);
      data_x[i] = distValue;
      Serial.print("Please the obstacle at ");
      Serial.print(distValue);
      Serial.print(" cm from the sensor and enter 1 to continue: ");
      boolean isContinue = false;
      while (Serial.available() == 0) {
        isContinue = Serial.parseInt() == 1;
      }
      Serial.read();
      Serial.println(isContinue);
      if (!isContinue) {
        Serial.println("invalid choice. breaking.");
        break;
      }
      delay(3000);
      long trigEchoTravelTimeTotal = 0;

      if (dataFile) {  

          dataFile.print(distValue);
          dataFile.println("cm,");

          for (int i = 0; i < Y_SAMPLE_SIZE; i++) {

            digitalWrite(trigPin, HIGH);
            delay(10);
            digitalWrite(trigPin, LOW);

            long trigEchoTravelTime = pulseIn(echoPin, HIGH);
            // trigEchoTravelTimeTotal += trigEchoTravelTime;
            dataFile.print(trigEchoTravelTime);
            dataFile.println(",");
            if (i % 50 == 0) { dataFile.flush(); }

            //  data_raw[i] = trigEchoTravelTime;
            Serial.print("Reading...");
            // Serial.print(j + 1);
            // Serial.print("/");
            // Serial.print(1000);
            // Serial.print(" Value ");
            Serial.print(trigEchoTravelTime);
            Serial.println(" ms");
          }
 
      } else {
        Serial.println("error opening datalog1.csv");
      }
      dataFile.close();


      delay(1000);
      // Dynamically create a file name
      // String fileName = createFileName();
      // Serial.print("Creating file: ");
      // Serial.println(fileName);

      // // Open or create the file



      float avrTimeTaken = trigEchoTravelTimeTotal / 1000;
      data_y[i] = avrTimeTaken;
      Serial.print("Avg Timetaken for distance ");
      Serial.print(distValue);
      Serial.print(" cm is ");
      Serial.print(avrTimeTaken);
      Serial.println(" ms");
    }
    Serial.println("Done Collecting the data.");
    Serial.println("Calibrating...");
    isStop = true;




    // int dht11Checksum = dhtTemp.read11(DHT11_PIN);
    // temperature = dhtTemp.temperature;
    // // put your main code here, to run repeatedly:
    // if (dht11Checksum == 0) {
    //   Serial.print(temperature);
    //   Serial.println(" degrees celcius");
    // } else {
    //   Serial.print("checksum error ");
    //   Serial.print(dht11Checksum);
    //   Serial.print(" and temperature ");
    //   Serial.print(temperature);
    //   Serial.println(" degrees celcius");
    // }
  }



  // // Function to create a unique file name
}
