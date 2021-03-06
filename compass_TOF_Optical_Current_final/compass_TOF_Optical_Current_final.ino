#include <INA219.h>
#include "Adafruit_VL53L0X.h"
#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "Bitcraze_PMW3901.h"

// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31

// set the pins to shutdown
#define SHT_LOX1 4
#define SHT_LOX2 5

#define SHUNT_MAX_V 0.16
#define BUS_MAX_V 20
#define MAX_CURRENT 16
#define SHUNT_R 0.01

// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
// objects for mag sensor
Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345);

// Using digital pin 10 for chip select
Bitcraze_PMW3901 flow(10);

INA219 ina219;

int32_t power=0;
//float voltage=0;
//float current=0;

byte dataPacket[14];

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;

int range1=0;
int range2=0;

// Sets the two TOF sensor IDs.
void setID();
// Reads two TOF sensors.
void read_dual_sensors();
// Reads compass.
void read_compass();

int heading=0;

// Reads deltax,y.
void read_dxdy();

const float Pi = 3.14159;
int16_t deltaX,deltaY;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  
  while(!Serial);
  
  Serial.setTimeout(2);

  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);

  //Serial.println("Shutdown pins inited...");

  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);

  //Serial.println("Both in reset mode...(pins are low)");
  //Serial.println("Starting...");
  setID();

  mag.begin();
  flow.begin();
  //Serial.println("TOF sensors initialized.");
  
  //delay(1000);

  //Serial.println("Initializing compass.\n");

  /* Initialise the sensor */
//  if (!mag.begin()) {
//    /* There was a problem detecting the LSM303 ... check your connections */
//    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
//    while(1);
//  }

//  delay(1000);
//
//  if (!flow.begin()) {
//    Serial.println("Initialization of the flow sensor failed");
//    while(1);
//  }

  ina219.begin();
  ina219.configure(INA219::RANGE_32V, INA219::GAIN_4_160MV, INA219::ADC_12BIT, INA219::ADC_12BIT, INA219::CONT_SH_BUS);
  ina219.calibrate(SHUNT_R,SHUNT_MAX_V,BUS_MAX_V,MAX_CURRENT);

  //Serial.println("Start");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //read_dual_sensors();
  //read_compass();
  //read_dxdy();

  flow.readMotionCount(&deltaX, &deltaY);
  power=ina219.busPower()*1000;

  sensors_event_t event;
  mag.getEvent(&event);
  // Calculate the angle of the vector y,x
  heading = int((atan2(event.magnetic.y, event.magnetic.x) * 180) / Pi);
  // Normalize to 0-360
  if (heading < 0) {
    heading = 360 + heading;
  }

  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
  if(measure1.RangeStatus != 4) {     // if not out of range
    //Serial.print(measure1.RangeMilliMeter);
    range1=measure1.RangeMilliMeter;
  } else {
    range1=-1;
  }
  if(measure2.RangeStatus != 4) {
    //Serial.print(measure2.RangeMilliMeter);
    range2=measure2.RangeMilliMeter;
  } else {
    range2=-1;
  }

  dataPacket[0]=byte(power>>24);
  dataPacket[1]=byte((power>>16)&255);
  dataPacket[2]=byte((power>8)&255);
  dataPacket[3]=byte(power&255);

  dataPacket[4]=byte(heading>>8);
  dataPacket[5]=byte(heading&255);

  dataPacket[6]=byte(deltaX>>8);
  dataPacket[7]=byte(deltaX&255);

  dataPacket[8]=byte(deltaY>>8);
  dataPacket[9]=byte(deltaY&255);

  dataPacket[10]=byte(range1>>8);
  dataPacket[11]=byte(range1&255);

  dataPacket[12]=byte(range2>>8);
  dataPacket[13]=byte(range2&255);

  if(Serial.available()>0)  {
    if(Serial.read()==48) {
      for(int i=0;i<14;i++) {
        Serial.write(dataPacket[i]);
      }
      Serial.flush();
    }
  }

  
//  current=ina219.shuntCurrent();
//  voltage=ina219.busVoltage();
  
  //Serial.println("\n\n");
  //Serial.println(power);
  //Serial.println(voltage);
  //Serial.println(current);
  //delay(200);
}

void setID() {
  // all reset
  digitalWrite(SHT_LOX1, LOW);    
  digitalWrite(SHT_LOX2, LOW);
  delay(10);
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  // activating LOX1 and reseting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);

  lox1.begin(LOX1_ADDRESS);
  lox2.begin(LOX2_ADDRESS);

  // initing LOX1
//  if(!lox1.begin(LOX1_ADDRESS)) {
//    Serial.println(F("Failed to boot first VL53L0X"));
//    while(1);
//  }
  delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  //initing LOX2
//  if(!lox2.begin(LOX2_ADDRESS)) {
//    Serial.println(F("Failed to boot second VL53L0X"));
//    while(1);
//  }
}

void read_dual_sensors() {
  
  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!

  // print sensor one reading
  Serial.print("1: ");
  if(measure1.RangeStatus != 4) {     // if not out of range
    Serial.print(measure1.RangeMilliMeter);
  } else {
    Serial.print("Out of range");
  }
  
  Serial.print(" ");

  // print sensor two reading
  Serial.print("2: ");
  if(measure2.RangeStatus != 4) {
    Serial.print(measure2.RangeMilliMeter);
  } else {
    Serial.print("Out of range");
  }
  
  Serial.println();
}

void read_compass(){
  sensors_event_t event;
  mag.getEvent(&event);

  // Calculate the angle of the vector y,x
  float heading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / Pi;

  // Normalize to 0-360
  if (heading < 0) {
    heading = 360 + heading;
  }
  Serial.print("Compass Heading: ");
  Serial.println(heading);
  delay(500);
}

void read_dxdy(){
  // Get motion count since last call
  flow.readMotionCount(&deltaX, &deltaY);

  Serial.print("X: ");
  Serial.print(deltaX);
  Serial.print(", Y: ");
  Serial.print(deltaY);
  Serial.print("\n");
}
