/*
Author: Marcellin Barbeau
Date Modified: 01.20.2024
Description:

    This is the dive code for umich HPS Marlin Sensor suite.
        --> MicroSD card writing
        --> Pressure/depth, IMU
        --> LCD display

    Baudrate = 115200

*/

//_____________________ Libraries _____________________


#include <Arduino.h>
#include <Wire.h>   // Library for I2C communication
#include <SPI.h>    // for SD card
#include <SD.h>     // for SD card
#include "MS5837.h" // Library for Pressure

#include <LiquidCrystal_I2C.h> // Library for LCD

// #include <Servo.h> // Library for Servo <-- NOT NEEDED FOR PHASE 1


//__________________________________________ Inititialization __________________________________________
// mission switch
int mission_go = 0;
const byte switchPin = 13;

// SD Card
File testfile;
String fileName = "blank.txt";
volatile int int_iter = 0;

char filename[16]; // SD card and file names - test

//  IMU:
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ; // variables for accelerometer and gyro raw data
int16_t temperature; // variables for temperature data

char tmp_str[7]; // temporary variable used in convert function

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

// //  Pressure:
MS5837 sensor;


//__________________________________________ setup __________________________________________
void setup() {
    Serial.begin(115200); // Set baud rate to 115200
    Serial.println("Setup started");

    //Pressure:
    while (!sensor.init()) {
        Serial.println("Init failed!");
        Serial.println("Are SDA/SCL connected correctly?");
        Serial.println("Blue Robotics Bar30: White=SDA, Green=SCL");
        Serial.println("\n\n\n");
        delay(5000);
    }
    sensor.setModel(MS5837::MS5837_30BA);
    sensor.setFluidDensity(997);

    //IMU:
    Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0); // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);

    // SD Card

    if (!SD.begin(53)) {
        Serial.println("No SD Module Detected");
        while (1);
    }
    // see if test file exists, delete it if it does
    // then prints headers and starts new one
    int n = 0;

    snprintf(filename, sizeof(filename), "data_%03d.csv", n); // includes a three-digit sequence number in the file name
    while(SD.exists(filename)) {
        n++;
        snprintf(filename, sizeof(filename), "data_%03d.csv", n);
    }


    if (SD.exists(fileName)){
        Serial.println(fileName+" exists, deleting and starting new");
        SD.remove(fileName);
    }
    

    testfile = SD.open(filename, FILE_WRITE);
    
    if (testfile) {
        // save headers to file
        testfile.println("Timestamp,Iteration,Pressure,Temperature,Depth,aX,aY,aZ,gX,gY,gZ,Errors");
        testfile.close();
    } else {
        // if the file didn't open, print an error:
        Serial.println("error opening file");
    }
}

//__________________________________________ main loop __________________________________________
int it = 0;
void loop() {
    if (digitalRead(switchPin) == LOW){
        // Serial.println("mission started");
        mission_go = 1;
    }
    else{
        // Serial.println("WAITING FOR MISISON GO");
        mission_go = 0;
    }

    
    Serial.println("\n");
    Serial.println("START :"+ String(it)+", "+String(mission_go));
    // Pressure: read
    sensor.read();

    // IMU: read
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);  
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR,12,true);  
    AcX=Wire.read()<<8|Wire.read();    
    AcY=Wire.read()<<8|Wire.read();  
    AcZ=Wire.read()<<8|Wire.read();  
    GyX=Wire.read()<<8|Wire.read();  
    GyY=Wire.read()<<8|Wire.read();  
    GyZ=Wire.read()<<8|Wire.read();  

    // Serial.print("Accelerometer: ");
    // Serial.print("X = "); Serial.print(AcX);
    // Serial.print(" | Y = "); Serial.print(AcY);
    // Serial.print(" | Z = ");  Serial.println(AcZ); 

    // Serial.print("Gyroscope: ");
    // Serial.print("X  = "); Serial.print(GyX);
    // Serial.print(" | Y = "); Serial.print(GyY);
    // Serial.print(" | Z = "); Serial.println(GyZ);
    // Serial.println(" ");

    testfile = SD.open(filename, FILE_WRITE);
    if (testfile) {
    // save a different number each loop
    testfile.println(String(millis())+","+String(it)+","+String(sensor.pressure())+","+String(sensor.temperature())+","+String(sensor.depth())+","+convert_int16_to_str(AcX)+","+convert_int16_to_str(AcY)+","+convert_int16_to_str(AcZ)+","+convert_int16_to_str(GyX)+","+convert_int16_to_str(GyY)+","+convert_int16_to_str(GyZ));
    testfile.close();
    Serial.println("Saving "+String(int_iter));
    } else {
        Serial.println("error opening file");
    }
    Serial.println("END :"+ String(it));

//sleep
    it++;
    delay(1000);
}



/* LEAK FORM loop
  leak = digitalRead(leakPin);   // Read the Leak Sensor Pin
  digitalWrite(ledPin, leak);  // Sets the LED to the Leak Sensor's Value

  if (leak == 1) {
    Serial.println("Leak Detected!");
  }
  else{
    Serial.println("No Leak");
  }

  delay(250);




/*


// Pressure:
  sensor.read();

// IMU:
  
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
  
//LCD:
  //lcd.clear(); // if the positioning of the cells change, then it leaves them filled with the last input: if 500 -> 1000, the last zero is left without clearing... but this is slow

  lcd.setCursor(0, 0); 
  lcd.print("Pressure:"); 
  lcd.print(sensor.pressure());
  lcd.print("mbar");
  
  lcd.setCursor(0, 1); 
  lcd.print("Temp: "); 
  lcd.print(sensor.temperature());
  lcd.print(" deg C");

  lcd.setCursor(0, 2);
  lcd.print("Depth: "); 
  lcd.print(sensor.depth());
  lcd.print(" m");

  lcd.setCursor(2, 3); 
  lcd.print("pedal harder!");
  //lcd.print(X_val);
  lcd.print("  ");
  //lcd.print(Y_val);
  
  testfile = SD.open(filename, FILE_WRITE);
  if (testfile) {
    // save a different number each loop
    testfile.println(String(millis())+","+String(int_iter)+","+String(sensor.pressure())+","+String(sensor.temperature())+","+String(sensor.depth())+","+String(accelerometer_x)+","+String(accelerometer_y)+","+String(accelerometer_z)+","+String(gyro_x)+","+String(gyro_y)+","+String(gyro_z));
    testfile.close();
    Serial.println("Saving "+String(int_iter));
  } else {
    Serial.println("error opening file");
  }
  int_iter += 1;




*/