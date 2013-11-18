#include <GY80.h>

GY80::GY80()
: gyroAddress(0x69), accAddress(0xA7 >> 1), magAddress(0x1E)
{}


void GY80::initialize()
{                           
  initGyro(gyroResolution);         
  delay(1500);                     
  initAcc();                       
  delay(1500);                  

  initMag();        
  delay(1500);                 
}


int GY80::initGyro(int scale)       
{                                         
  writeRegister(gyroAddress, GYRO_CTRL_REG1, 0b00001111);    

  writeRegister(gyroAddress, GYRO_CTRL_REG2, 0b00000000);    

  writeRegister(gyroAddress, GYRO_CTRL_REG3, 0b00001000); 

  if(scale == 250){                                          
    writeRegister(gyroAddress, GYRO_CTRL_REG4, 0b00000000);
  }else if(scale == 500){
    writeRegister(gyroAddress, GYRO_CTRL_REG4, 0b00010000);
  }else{
    writeRegister(gyroAddress, GYRO_CTRL_REG4, 0b00110000);
  }

  writeRegister(gyroAddress, GYRO_CTRL_REG5, 0b00000000);    
}


void GY80::getGyroValues()
{
  byte xGyroValMSB = readRegister(gyroAddress, 0x29);    
  byte xGyroValLSB = readRegister(gyroAddress, 0x28);    
  gyroX = ((xGyroValMSB << 8) | xGyroValLSB);           

  byte yGyroValMSB = readRegister(gyroAddress, 0x2B);   
  byte yGyroValLSB = readRegister(gyroAddress, 0x2A);   
  gyroY = ((yGyroValMSB << 8) | yGyroValLSB);          

  byte zGyroValMSB = readRegister(gyroAddress, 0x2D);     
  byte zGyroValLSB = readRegister(gyroAddress, 0x2C);     
  gyroZ = ((zGyroValMSB << 8) | zGyroValLSB);            
}


void GY80::printGyroValues()                       
{
  if (gyroX >= gyroX_Thresh)                 
  {
    Serial.print("gyroX = ");
    Serial.println(gyroX);
  }
  else                                        
  {
    Serial.println("gyroX = 0");
  }
  if (gyroY >= gyroY_Thresh)                  
  {
    Serial.print("gyroY = ");
    Serial.println(gyroY);
  }
  else                                        
  {
    Serial.println("gyroY = 0");
  }
  if (gyroZ >= gyroZ_Thresh)                  
  {
    Serial.print("gyroZ = ");
    Serial.println(gyroZ);
  }
  else                                        
  {
    Serial.println("gyroZ = 0");
  }
  Serial.println("--------");
}


int GY80::initAcc()
{
  writeRegister(accAddress, ACC_POWER_CTL_REG, 0b00001000);      
  
  writeRegister(accAddress, ACC_DATA_FORMAT_REG, 0b00001001);    
}

void GY80::getAccValues()
{
  byte xAccValMSB = readRegister(accAddress, 0x33);    
  byte xAccValLSB = readRegister(accAddress, 0x32);    
  accX = ((xAccValMSB << 8) | xAccValLSB);             
  
  byte yAccValMSB = readRegister(accAddress, 0x35);    
  byte yAccValLSB = readRegister(accAddress, 0x34);    
  accY = ((yAccValMSB << 8) | yAccValLSB);            
  
  byte zAccValMSB = readRegister(accAddress, 0x37);    
  byte zAccValLSB = readRegister(accAddress, 0x36);    
  accZ = ((zAccValMSB << 8) | zAccValLSB);            
}

void GY80::printAccValues()                       
{
  if (abs(accX) >= accX_Thresh)             
  {
    Serial.print("accX = ");
    Serial.println(accX);
  }
  else                                       
  {   
    Serial.println("accX = 0");
  }
  if (abs(accY) >= accY_Thresh)              
  {
    Serial.print("accY = ");
    Serial.println(accY);
  }
  else                                       
  {
    Serial.println("accY = 0");
  }
  if (abs(accZ) >= accZ_Thresh)              
  {
    Serial.print("accZ = ");
    Serial.println(accZ);
  }
  else                                      
  {
    Serial.println("accZ = 0");
  }
  Serial.println("--------");
}


int GY80::initMag()
{
  writeRegister(magAddress, MAG_CONFIG_REGISTER_A, 0b00010000);    
  
  writeRegister(magAddress, MAG_CONFIG_REGISTER_B, 0b00110000);    
  
  writeRegister(magAddress, MAG_MODE_REGISTER, 0b00000000);       
}

void GY80::getMagValues()
{
  byte xMagValMSB = readRegister(magAddress, 0x03);    
  byte xMagValLSB = readRegister(magAddress, 0x04);    
  magX = ((xMagValMSB << 8) | xMagValLSB);             
  
  byte yMagValMSB = readRegister(magAddress, 0x07);    
  byte yMagValLSB = readRegister(magAddress, 0x08);    
  magY = ((yMagValMSB << 8) | yMagValLSB);            
  
  byte zMagValMSB = readRegister(magAddress, 0x05);    
  byte zMagValLSB = readRegister(magAddress, 0x06);   
  magZ = ((zMagValMSB << 8) | zMagValLSB);        
}

void GY80::printMagValues()
{
  if (abs(magX) >= magX_Thresh)    
  {
    Serial.print("magX = ");
    Serial.println(magX);
  }
  else                             
  {
    Serial.println("magX = 0");
  }
  if (abs(magY) >= magY_Thresh)     
  {
    Serial.print("magY = ");
    Serial.println(magY);
  }
  else                          
  {
    Serial.println("magY = 0");
  }
  if (abs(magZ) >= magZ_Thresh)  
  {
    Serial.print("magZ = ");
    Serial.println(magZ);
  }
  else                            
  {
    Serial.println("magZ = 0");
  }
  Serial.println("--------");
}



void GY80::writeRegister(int deviceAddress, byte address, byte val) 
{
    Wire.beginTransmission(deviceAddress);   
    Wire.write(address);                     
    Wire.write(val);                       
    Wire.endTransmission();               
}


int GY80::readRegister(int deviceAddress, byte address)
{

    int register_value;
    Wire.beginTransmission(deviceAddress);   
    Wire.write(address);                     
    Wire.endTransmission();                  

    Wire.requestFrom(deviceAddress, 1);       

    while(!Wire.available()) {}            

    register_value = Wire.read();          
    return register_value;                 
}


int GY80::getGyroDelay()
{
	return gyroDelay; 
}
int GY80::getAccDelay()
{
	return accDelay; 
}
int GY80::getMagDelay()
{
	return magDelay; 
}