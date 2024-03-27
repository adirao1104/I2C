/*
This is pseudo code Using C Programming Language to facilitate 
a I2C Communication between Master and slave

Microntoller uC <-----I2C----------> LIS3MDL 3 Axis Mangnetrometer

*/

#include <stdio.h>
#include "i2c.h"

#define SDA 7U // GPIO 7 ON THE I2C PORT
#define SCL 8U // GPIO 8 ON THE I2C PORT


//////// FUNTION TO INITIATE THE I2C BUS /////////////

int I2C_INIT(void){
    Enable_clock(100U); // 100Khz
    set_I2C_Address(0x0A); // Masters address
    set_I2C_Adress_mode(I2C_ADDRESS_7BIT); //7 bit Adressing mode
    set_GPIO_I2C_SDA(SDA); // Set pin for SDA
    set_GPIO_I2C_SCL(SCL);// SET PIN FOR SCL

}

//////// FUNTION TO START THE I2C BUS /////////////

void I2C_Start(){
    SDA_Start();
    SCL_Start();
    delay(50); //50 milli seconds DELAY
    SDA_Stop();
    
}

//////// FUNTION TO STOP THE I2C BUS /////////////

void I2C_Stop(){
    SDA_Stop();
    SCL_Start();
    delay(50); //50 milli seconds
    SDA_Start();
}


//////// FUNTION TO WRITE TO A SELECTED DEVIVE ON THE I2C BUS /////////////

int i2c_write(uint8_t bus_address, uint8_t register_address, const uint8_t* data, size_t length) {
    
    I2C_Start(); // Start I2C transmission
    
    I2C_Transmit_Adress(bus_address << 1 | 0); // 7 bit address and 1 bit for R/W 

    // Send register address
    I2C_Transmit_Adress(register_address);
    
    // Write the data bytes recieved from the Device 
    for (size_t i = 0; i < length; i++) {
        I2C_Transmit_Data(data[i]);
    }

    I2C_Stop(); // Stop  Transmission

    if(!data)  return STATUS_ERROR; // if the data is NULL return Error
    

    return STATUS_OK;

}

//////// FUNTION TO READ FROM A SELECTED DEVIVE ON THE I2C BUS /////////////

int8_t read_I2C(uint8_t bus_address, uint8_t register_address, size_t length){
      int8_t data = 0;

      I2C_Start(); // Start  Transmission

      I2C_Transmit_Adress(bus_address << 1 | 0); // 7 bit address and 1 bit for R/W 

      I2C_Transmit_Adress(register_address);

       I2C_Start(); // Start  Transmission

      I2C_Transmit_Adress(bus_address << 1 | 1);
      // Write the data bytes recieved from the Bus
      for (size_t i = 0; i < length; i++) {
        data[i] = I2C_Receive_Data(i < (length - 1)); 
    }

    I2C_Stop(); // Stop  Transmission

    return data;

}