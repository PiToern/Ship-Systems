#ifndef _GY80_H_INCLUDED 
#define _GY80_H_INCLUDED


#include "Arduino.h"
#include <Wire.h>     

#define GYRO_CTRL_REG1 0x20 
#define GYRO_CTRL_REG2 0x21  
#define GYRO_CTRL_REG3 0x22 
#define GYRO_CTRL_REG4 0x23   
#define GYRO_CTRL_REG5 0x24   

#define ACC_POWER_CTL_REG 0x2D    
#define ACC_DATA_FORMAT_REG 0x31   

#define MAG_CONFIG_REGISTER_A 0x00   
#define MAG_CONFIG_REGISTER_B 0x01 
#define MAG_MODE_REGISTER 0x02    



class GY80
{
	public:

		GY80(); 
		void initialize(); 
		int initGyro(int scale); 
		void getGyroValues(); 
		void printGyroValues();   
		int initAcc(); 
		void getAccValues(); 
		void printAccValues(); 
		int initMag(); 
		void getMagValues(); 
		void printMagValues(); 
		void writeRegister(int deviceAddress, byte address, byte val);
		int readRegister(int deviceAddress, byte address); 
		int getGyroDelay(); 
		int getAccDelay(); 
		int getMagDelay(); 


	private:
		
		int gyroAddress;  

		int gyroX;                 
		int gyroY;
		int gyroZ;

		static const int gyroX_Thresh = 3;      
		static const int gyroY_Thresh = 10;
		static const int gyroZ_Thresh = 31;

		static const int gyroDelay = 500;      
		static const int gyroResolution = 2000;     

		int accAddress;     

		int accX;                
		int accY;
		int accZ;

		static const int accX_Thresh = 257;         
		static const int accY_Thresh= 3;
		static const int accZ_Thresh = 28;

		static const int accDelay = 500;          

		int magAddress;       

		int magX;                   
		int magY;
		int magZ;

		static const int magX_Thresh = 0;         
		static const int magY_Thresh = 0;
		static const int magZ_Thresh = 0;

		static const int magDelay = 500;            
		
}; 



#endif