import serial                           #import the pySerial library for easy access to serial ports
import time                             #import the time library  

ser = serial.Serial('/dev/ttyACM0', 115200)     #open serial port 'ttyACM0' at a baudrate of 115200 Bd/s with pySerial

'''This demo code uses an infinte loop which should get some break conditions in the final program.'''

while 1:
        '''The following segment gets data send from the Arduino and displays it on the Python Shell.'''

        
        response = ser.readlines(1)    #readlines() with timeout set to 1 to prevent blocking the serial port forever

        '''This is the place where the data received from the sensors via serial port
           from the Arduino is processed to determine the positions of both the sail
           and the rudder servo motor.

           Implementing and testing this code is part of the exercise for the school classes
           as part of the regatta.'''

        print response                 #print serial port output to shell

        '''The following part gives an example to control the sail servo motor by sending
           defined commands via serial port from the Raspberry Pi to the Arduino.

           In the final program the positions will be determined by the data gathered from the sensors.'''

        '''print("send s180")
        ser.write('s180')               #send command to Arduino to move sail servo motor to 180 degrees
        print("wait for servo")
        time.sleep(5)                   #wait to give servo motor time to move
        print("send s0")
        ser.write('s0')                 #send command to Arduino to move sail servo motor to 0 degrees
        print("wait for servo")
        time.sleep(5)                   #wait to give servo motor time to move'''
        
