Other resources to complete this coursework
    https :                // create.arduino.cc/projecthub/Nicholas_N/how-to-use-the-accelerometer-gyroscope-gy-521-6dfc19
            https :        // www.youtube.com/watch?v=wTfSfhjhAU0
                    http : // www-robotics.cs.umass.edu/~grupen/503/Projects/ArduinoMPU6050-Tutorial.pdf

                           Acquisition Code
/*
Reading values from GY-521 accelerometer unit
*/
#include <Wire.h>
                           const int MPU = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
void setup()
{
    Wire.begin();
    Wire.beginTransmission(MPU);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
    Serial.begin(9600);
    Check your Arduino Board !You need to connect SCL and SDA(on the GY - 521) to corresponding SCL and SDA pins on the Arduino board.

                                                                                                        void
                                                                                                        loop()
    {
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
        Serial.print("X = ");
        Serial.print(AcX);
        Serial.print(" | Y = ");
        Serial.print(AcY);
        Serial.print(" | Z = ");
        Serial.println(AcZ);
        Serial.print("Gyroscope: ");
        Serial.print("X = ");
        Serial.print(GyX);
        Serial.print(" | Y = ");
        Serial.print(GyY);
        Serial.print(" | Z = ");
        Serial.println(GyZ);
        Serial.println(" ");
        delay(333);
    }

    Accelerometer calibration Code
        /*
        Analog Input: Program can be used to read signals from a simple
        accelerometer (with analogue output) to measure one's positioning
        accuracy. The program waits for the user to bring the
        accelerometer into a horizontal position; then requests the user to
        hold and reads in 100 accelerometer signals. The user is then
        required to move to the vertical position. The process is then
        repeated. Recorded values can be copied into the clipboard from
        the Monitor afterwards.
        created by Kaspar Althoefer; 30 Nov 2019
        */
        int sensorPin = A0;
    int k;
    sensor
        // select the input pin for the potentiometer
        // constant for counter
        int sensorValue = 0; // variable to store the value coming from the
    void setup()
    {
        // initialize serial communication:
        Serial.begin(9600);
    }

    void loop()
    {
        // read the value from the sensor:
        {
            = analogRead(sensorPin);
            // Start reading accelerometer signals when roughly
            in target area(horizontal) if (sensorValue > 348 - 20 && sensorValue < 348 + 20)
                Serial.println("wait ");
            delay(1000);
            Serial.println("hold "); // tell user to wait
            // wait for 1 second
            // tell user to hold steady
            for (k = 0; k < 99; k = k + 1)
            { // read in 100
                accelerometer samples while user is holding steady
                    sensorValue = analogRead(sensorPin); // read
                the value from the accelerometer
                    Serial.println(sensorValue); // show results
                in Monitor
            }
            Serial.println(" finished"); // tell user that
            reading is over and to move back to vertical position
                delay(1000); // wait for 1 second
        }
    }

    /*
    Reads single axis signal from an accelerometer. When user moves
    through a complete sweep from -1g to +1g, program will calibrate
    for the used sensor. After calibration the shown signals are
    calibrated as a function of g (gravity). --- created by Kaspar
    Althoefer 30 Nov 2019
    */
    int accel;          // Raw acceleration value measured
    int gMAX = 1;       // Maximum inclination (pointing downwards)
    int gMIN = -1;      // Minimum inclination (pointing upwards)
    double gACCEL;      // Variable to hold calibrated acceleration signals
    int gACCEL_1000;    // Calibrated accel. signals x 1000 (milli_g)
    double m;           // temporary variable
    double n;           // temporary variable
    int Calibrated_map; // Calibrated signal using “map” function
    int Max;            // temporary variable holding maximum / minimum
    int Min;            // accelerometer signal (continuously updated)
    void setup()
    {
        Serial.begin(9600); // initialize the serial communications
        Max = -1000;        // initialize variables Max and Min
        Min = 1000;
    }

    void loop()
    {
        
    
        for (int i=0; i < arraySize; i++)
        {
            accel = analogRead(A0); // read the accelerometer signal
        if (accel > Max)
        {
            Max = accel;
        }
        if (accel < Min)
        {
            Min = accel;
        }
        }
        // if current accelerometer value is larger
        // than Max then update Max
        // if current accelerometer value is smaller
        // than Min then update Min
        m = (Max - Min) / (gMAX - gMIN);                    // calculate slope of linear equation
        n = Max - m * gMAX;                                 // calculate offset of linear equation
        gACCEL = accel / m - n / m;                         // calibrate sensor using measured Min & Max
        gACCEL_1000 = gACCEL * 1000;                        // multiply with 1000 (milli_g)
        Calibrated_map = map(accel, Min, Max, -1000, 1000); // Do the calibrationusing built - in function map
        
        // print the sensor values:
        Serial.print(accel); // raw accelerometer signals
        Serial.print("\t");
        Serial.print(Min); // evolving Min value
        Serial.print("\t");
        Serial.print(Max); // evolving Max value
        Serial.print("\t");
        Serial.print(Calibrated_map); // Calibrated signal using function “map”
        Serial.print("\t");
        Serial.print(gACCEL_1000); // Calibrated signal from this program
        Serial.println();
        delay(50); // delay before next reading
    }

/*
Keyes 37 in 1 Sensor Kit Upgraded Version
Project 33
rotary encoder
By keyes
*/
#define CLK 2
#define DT 3
#define SW 4
    int counter = 0;
    int currentStateCLK;
    int lastStateCLK;
    String currentDir = "";
    unsigned long lastButtonPress = 0;
    void setup()
    {
        // Set encoder pins as inputs
        pinMode(CLK, INPUT);
        pinMode(DT, INPUT);
        pinMode(SW, INPUT_PULLUP);
        // Setup Serial Monitor
        Serial.begin(9600);
        // Read the initial state of CLK
        lastStateCLK = digitalRead(CLK);
    }
    void loop()
    {
        // Read the current state of CLK
        currentStateCLK = digitalRead(CLK);
        // If last and current state of CLK are different, then pulse occurred
        // React to only 1 state change to avoid double count
        if (currentStateCLK != lastStateCLK && currentStateCLK == 1)
        {
            // If the DT state is different than the CLK state then
            // the encoder is rotating CCW so decrement
            if (digitalRead(DT) != currentStateCLK)
            {
                counter--;
                currentDir = "CCW";
            }
            else
            {
                // Encoder is rotating CW so increment
                counter++;
                currentDir = "CW";
            }
            Serial.print("Direction: ");
            Serial.print(currentDir);
            Serial.print(" | Counter: ");
            Serial.println(counter);
        }
        // Remember last CLK state
        lastStateCLK = currentStateCLK;
        // Read the button state
        int btnState = digitalRead(SW);
        // If we detect LOW signal, button is pressed
        if (btnState == LOW)
        {
            // if 50ms have passed since last LOW pulse, it means that the
            // button has been pressed, released and pressed again
            if (millis() - lastButtonPress > 50)
            {
                Serial.println("Button pressed!");
            }
            // Remember last button press event
            lastButtonPress = millis();
        } // Put in a slight delay to help debounce the reading
        delay(1);
    }
