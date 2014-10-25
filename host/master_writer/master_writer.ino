// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup()
{
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
}

uint8_t idx = 0;
void loop()
{
  for(int i=0; i<60; i++)
  {
    testCommand(0);
    delay(5);
  }
  delay(1000);
  
  testCommand(1);
  delay(1000);
  
  testCommand(2);
  delay(1000);  
  
}

void testCommand(uint8_t cmd)
{
  switch(cmd)
  {
    case 0:
      Wire.beginTransmission(4); // transmit to device #4
      Wire.write("[");           // sends one byte  
      Wire.write(0);
      Wire.write(idx++);         // sends one byte
      Wire.write(255);           // sends one byte
      Wire.write(0);             // sends one byte  
      Wire.write(0);             // sends one byte    
      Wire.write("]");           // sends one byte  
      Wire.endTransmission();    // stop transmitting
      delay(5);
      Wire.requestFrom(4, 1);    // request 1 bytes from slave device #4    
      while(Wire.available())    // slave may send less than requested
      { 
        int status = Wire.read();       // receive status byte
        if(!status)
          Serial.println("WE GOOD!");
        else
          Serial.println("ERROR");         // print the character
      }      
      if(idx==60)
        idx=0;      
      break;
      
    case 1:
      Wire.beginTransmission(4); // transmit to device #4    
      Wire.write("[");           // sends one byte  
      Wire.write(1);
      Wire.write(0);           // sends one byte
      Wire.write(255);           // sends one byte  
      Wire.write(0);          // sends one byte    
      Wire.write("]");           // sends one byte  
      Wire.endTransmission();    // stop transmitting
      break;

    case 2:
      Wire.beginTransmission(4); // transmit to device #4    
      Wire.write("[");           // sends one byte  
      Wire.write(2);   
      Wire.write("]");           // sends one byte  
      Wire.endTransmission();    // stop transmitting    
      break;

    case 3:
      Wire.beginTransmission(4); // transmit to device #4    
      Wire.write("[");           // sends one byte  
      Wire.write(3);   
      Wire.write(1);         
      Wire.write("]");           // sends one byte  
      Wire.endTransmission();    // stop transmitting        
      break;

    default:
      break;    
  }  
}
