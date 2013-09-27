#include <Wire.h>

/***BEGIN L3G4200D***/

int gyroAddress = 0x69;         //I2C address of the L3G4200D gyroscope

#define GYRO_CTRL_REG1 0x20    //L3G4200D output data rate selection, bandwidth selection, set power down mode, enable x,y,z axis
#define GYRO_CTRL_REG2 0x21    //L3G4200D high-pass-filter (HPF) and operations mode settings
#define GYRO_CTRL_REG3 0x22    //L3G4200D interrupt, push - pull and FIFO queue settings, boot status availability
#define GYRO_CTRL_REG4 0x23    //L3G4200D set datat update, selection and scale, self test, SPI mode selection [not set because of I2C use]
#define GYRO_CTRL_REG5 0x24    //L3G4200D rebootmemory content, FIFO and output configuration

int gyroX;          //hold the respective values
int gyroY;
int gyroZ;

const int gyroX_Thresh = 3;         //noise threshold for the respective readings - subject to change
const int gyroY_Thresh = 10;
const int gyroZ_Thresh = 31;

const int gyroDelay = 500;            //delay between consecutive readings - subject to change
const int gyroResolution = 2000;      //int value 250, 500 or 2000 setting deg/sec

/***END L3G4200D***/


/***BEGIN ADXL345***/

int accAddress = 0xA7 >> 1;        //I2C address of the ADXL345 accelerometer

#define ACC_POWER_CTL_REG 0x2D     //power control register
#define ACC_DATA_FORMAT_REG 0x31   //data format register

int accX;                    //hold the respective values
int accY;
int accZ;

const int accX_Thresh = 257;         //noise threshold for the respective readings - subject to change
const int accY_Thresh = 3;
const int accZ_Thresh = 28;

const int accDelay = 500;            //delay between consecutive readings - subject to change

/***END ADXL345***/


/***BEGIN HMC5883L***/

int magAddress = 0x1E;        //I2C address of the HMC5883L magnetometer

#define MAG_CONFIG_REGISTER_A 0x00    //configuration register A [set data putput rate and measurement configuration]
#define MAG_CONFIG_REGISTER_B 0x01    //configuration register B [set the device gain]
#define MAG_MODE_REGISTER 0x02      //mode register [set operation mode]

int magX;                    //hold the respective values
int magY;
int magZ;

const int magX_Thresh = 0;         //noise threshold for the respective readings - subject to change
const int magY_Thresh = 0;
const int magZ_Thresh = 0;

const int magDelay = 500;            //delay between consecutive readings - subject to change

/***END HMC5883L***/


void setup()
{
  Wire.begin();                              //start I2C bus [normal mode 100 kHz]
  Serial.begin(115200);                     //start serial bus with given data rate
 
/***BEGIN SETUP L3G4200D***/
  
  Serial.println("Init I2C L3G4200D");
  
  initGyro(gyroResolution);         //initialize gyroscope
  
  delay(1500);                      //give sensor time for the initialisation
  
  Serial.println("Finished Init I2C L3G4200D");
  
/***END SETUP L3G4200D***/


/***BEGIN SETUP ADXL345***/

  Serial.println("Init I2C ADXL345");

  initAcc();                        //initialize accelerometer

  delay(1500);                      //give sensor time for the initialisation

  Serial.println("Finished Init I2C ADXL345");

/***END SETUP ADXL345***/


/***BEGIN SETUP HMC5883L***/

  Serial.println("Init I2C HMC5883L");

  initMag();                        //initialize magnetometer

  delay(1500);                      //give sensor time for the initialisation

  Serial.println("Finished Init I2C HMC5883L");

/***END SETUP HMC5883L***/
}

void loop()
{
/***BEGIN GET L3G4200D VALUES***/

  getGyroValues();
  printGyroValues();
  delay(gyroDelay);
  
/***END GET L3G4200D VALUES***/


/***BEGIN GET ADXL345 VALUES***/

getAccValues();
printAccValues();
delay(accDelay);

/***END GET ADXL345 VALUES***/


/***BEGIN GET HMC5883L VALUES***/

getMagValues();
printMagValues();
delay(magDelay);

/***END GET HMC5883L VALUES***/
}


/***BEGIN L3G4200D FUNCTIONS***/


int initGyro(int scale)       //by Jim Lindblom [Sparkfun]
{                                         
  writeRegister(gyroAddress, GYRO_CTRL_REG1, 0b00001111);     //enable x,y,z axis and disable power down mode 

  writeRegister(gyroAddress, GYRO_CTRL_REG2, 0b00000000);     //disable HPF (high-pass-filter) enables measurement of long rotations and stopping

  writeRegister(gyroAddress, GYRO_CTRL_REG3, 0b00001000);     //set CTRL_REG3 to generate data ready interrupt on INT2 - no interrupts used on INT1

  if(scale == 250){                                            //set full-scale range according initGyro value [250, 500, 2000 deg/sec]
    writeRegister(gyroAddress, GYRO_CTRL_REG4, 0b00000000);
  }else if(scale == 500){
    writeRegister(gyroAddress, GYRO_CTRL_REG4, 0b00010000);
  }else{
    writeRegister(gyroAddress, GYRO_CTRL_REG4, 0b00110000);
  }

  writeRegister(gyroAddress, GYRO_CTRL_REG5, 0b00000000);      //disable HPF (high-pass-filter) on outputs
}


void getGyroValues()
{
  byte xGyroValMSB = readRegister(gyroAddress, 0x29);    //read register x-axis high byte
  byte xGyroValLSB = readRegister(gyroAddress, 0x28);    //read register x-axis low byte
  gyroX = ((xGyroValMSB << 8) | xGyroValLSB);            //get x-axis value as int by combining high and low byte 

  byte yGyroValMSB = readRegister(gyroAddress, 0x2B);   //read register y-axis high byte
  byte yGyroValLSB = readRegister(gyroAddress, 0x2A);   //read register y-axis low byte
  gyroY = ((yGyroValMSB << 8) | yGyroValLSB);           //get y-axis value as int by combining high and low byte

  byte zGyroValMSB = readRegister(gyroAddress, 0x2D);     //read register z-axis high byte
  byte zGyroValLSB = readRegister(gyroAddress, 0x2C);     //read register z-axis low byte
  gyroZ = ((zGyroValMSB << 8) | zGyroValLSB);             //get z-axis value as int by combining high and low byte
}


void printGyroValues()                        //print respective values [angular rate per axis in deg/s] to the serial bus
{
  if (gyroX >= gyroX_Thresh)                  //if the value of the x-axis is greater than the respective threshold print it to the serial bus
  {
    Serial.print("gyroX = ");
    Serial.println(gyroX);
  }
  else                                        //else print 0 to the serial bus
  {
    Serial.println("gyroX = 0");
  }
  if (gyroY >= gyroY_Thresh)                  //if the value of the y-axis is greater than the respective threshold print it to the serial bus
  {
    Serial.print("gyroY = ");
    Serial.println(gyroY);
  }
  else                                        //else print 0 to the serial bus
  {
    Serial.println("gyroY = 0");
  }
  if (gyroZ >= gyroZ_Thresh)                  //if the value of the z-axis is greater than the respective threshold print it to the serial bus
  {
    Serial.print("gyroZ = ");
    Serial.println(gyroZ);
  }
  else                                        //else print 0 to the serial bus
  {
    Serial.println("gyroZ = 0");
  }
  Serial.println("--------");
}

/***END L3G4200D FUNCTIONS***/


/***BEGIN ADXL345 FUNCTIONS***/

int initAcc()
{
  writeRegister(accAddress, ACC_POWER_CTL_REG, 0b00001000);      //disable sleep mode and enable measurement mode
  
  writeRegister(accAddress, ACC_DATA_FORMAT_REG, 0b00001001);    //set full resolution mode with g range set to +/- 4g with a 4 mg/LSB scale factor
}

void getAccValues()
{
  byte xAccValMSB = readRegister(accAddress, 0x33);    //read register x-axis high byte
  byte xAccValLSB = readRegister(accAddress, 0x32);    //read register x-axis low byte
  accX = ((xAccValMSB << 8) | xAccValLSB);             //get x-axis value as int by combining high and low byte 
  
  byte yAccValMSB = readRegister(accAddress, 0x35);    //read register y-axis high byte
  byte yAccValLSB = readRegister(accAddress, 0x34);    //read register y-axis low byte
  accY = ((yAccValMSB << 8) | yAccValLSB);             //get y-axis value as int by combining high and low byte 
  
  byte zAccValMSB = readRegister(accAddress, 0x37);    //read register z-axis high byte
  byte zAccValLSB = readRegister(accAddress, 0x36);    //read register z-axis low byte
  accZ = ((zAccValMSB << 8) | zAccValLSB);             //get z-axis value as int by combining high and low byte  
}

void printAccValues()                        //print respective values [4 mg/LSB with a g range of +/- 4g] to the serial bus
{
  if (abs(accX) >= accX_Thresh)              //if the absolute value of the x-axis is greater than the respective threshold print it to the serial bus
  {
    Serial.print("accX = ");
    Serial.println(accX);
  }
  else                                       //else print 0 to the serial bus
  {   
    Serial.println("accX = 0");
  }
  if (abs(accY) >= accY_Thresh)              //if the absolute value of the y-axis is greater than the respective threshold print it to the serial bus
  {
    Serial.print("accY = ");
    Serial.println(accY);
  }
  else                                       //else print 0 to the serial bus 
  {
    Serial.println("accY = 0");
  }
  if (abs(accZ) >= accZ_Thresh)              //if the absolute value of the z-axis is greater than the respective threshold print it to the serial bus
  {
    Serial.print("accZ = ");
    Serial.println(accZ);
  }
  else                                       //else print 0 to the serial bus 
  {
    Serial.println("accZ = 0");
  }
  Serial.println("--------");
}

/***END ADXL345 FUNCTIONS***/

int initMag()
{
  writeRegister(magAddress, MAG_CONFIG_REGISTER_A, 0b00010000);    //set data output rate to 15Hz and normal measurement mode [no forced currents forced across the resistive load] [default register configuration]
  
  writeRegister(magAddress, MAG_CONFIG_REGISTER_B, 0b00110000);    //set sensor field range to +/- 2.5Ga, gain to 660 and digital resolution to 1.52 mG/LSb - output range is -2048 to 2047
  
  writeRegister(magAddress, MAG_MODE_REGISTER, 0b00000000);        //set continuous measurement mode
}

void getMagValues()
{
  byte xMagValMSB = readRegister(magAddress, 0x03);    //read register x-axis high byte
  byte xMagValLSB = readRegister(magAddress, 0x04);    //read register x-axis low byte
  magX = ((xMagValMSB << 8) | xMagValLSB);             //get x-axis value as int by combining high and low byte 
  
  byte yMagValMSB = readRegister(magAddress, 0x07);    //read register y-axis high byte
  byte yMagValLSB = readRegister(magAddress, 0x08);    //read register y-axis low byte
  magY = ((yMagValMSB << 8) | yMagValLSB);             //get y-axis value as int by combining high and low byte 
  
  byte zMagValMSB = readRegister(magAddress, 0x05);    //read register z-axis high byte
  byte zMagValLSB = readRegister(magAddress, 0x06);    //read register z-axis low byte
  magZ = ((zMagValMSB << 8) | zMagValLSB);             //get z-axis value as int by combining high and low byte
}

void printMagValues()
{
  if (abs(magX) >= magX_Thresh)      //if the absolute value of the x-axis is greater than the respective threshold print it to the serial bus
  {
    Serial.print("magX = ");
    Serial.println(magX);
  }
  else                               //else print 0 to the serial bus
  {
    Serial.println("magX = 0");
  }
  if (abs(magY) >= magY_Thresh)      //if the absolute value of the y-axis is greater than the respective threshold print it to the serial bus
  {
    Serial.print("magY = ");
    Serial.println(magY);
  }
  else                               //else print 0 to the serial bus
  {
    Serial.println("magY = 0");
  }
  if (abs(magZ) >= magZ_Thresh)      //if the absolute value of the z-axis is greater than the respective threshold print it to the serial bus
  {
    Serial.print("magZ = ");
    Serial.println(magZ);
  }
  else                               //else print 0 to the serial bus
  {
    Serial.println("magZ = 0");
  }
  Serial.println("--------");
}

/***BEGIN HMC5883L FUNCTIONS***/



/***END HMC5883L FUNCTIONS***/


/***BEGIN GLOBAL FUNCTIONS***/

void writeRegister(int deviceAddress, byte address, byte val) 
{
    Wire.beginTransmission(deviceAddress);   //start transmission to device 
    Wire.write(address);                     //send register address
    Wire.write(val);                         //send value to write
    Wire.endTransmission();                  //end transmission
}


int readRegister(int deviceAddress, byte address){

    int register_value;
    Wire.beginTransmission(deviceAddress);    //start transmission to device
    Wire.write(address);                      //set specific register to read
    Wire.endTransmission();                   //end transmission

    Wire.requestFrom(deviceAddress, 1);       //request one byte from set register on device with respective address

    while(!Wire.available()) {}               //wait until wire is available to fulfill read request

    register_value = Wire.read();             //store received byte
    return register_value;                    //return byte to caller
}

/***END GLOBAL FUNCTIONS***/
