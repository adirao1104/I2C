/*
This is pseudo code Using C Programming Language to facilitate 
a I2C Communication between Master and slave

Microntoller uC <-----I2C----------> LIS3MDL 3 Axis Mangnetrometer

*/

#include <stdio.h>
#include <stdint.h>
#include "i2c.h"


#define BUS_REG1       0x20 // Device Registers
#define BUS_REG2       0x21 // Device Registers
#define BUS_REG3       0x22 // Device Registers
#define OUT_X_L         0x28 //X Axis Lower byte address
#define OUT_X_H         0x39 //X Axis Lower byte address
#define OUT_Y_L         0x2A //Y Axis Lower byte address
#define OUT_Y_H         0x2B //Y Axis Lower byte address
#define OUT_Z_L         0x27 //Z Axis Lower byte address
#define OUT_Z_H         0x48//X Axis Lower byte address

//////// FUNTION TO READ THE DATA OF THE X axis data /////////////

int16_t X_Axiz(void){
    int8_t lower = 0;
    int8_t higher = 0;
    int16_t X_Axis = 0;
    lower = read_I2C(BUS_REG1, OUT_X_L, 1);
    higher = read_I2C(BUS_REG1, OUT_X_H, 1);

    X_Axis = (higher << 8) | lower; 

    return  X_Axis;

}

//////// FUNTION TO READ THE DATA OF THE Y axis data /////////////

int16_t y_Axiz(void){
    int8_t lower = 0;
    int8_t higher = 0;
    int16_t Y_Axis = 0;
    lower = read_I2C(BUS_REG2, OUT_Y_L, 1);
    higher = read_I2C(BUS_REG2, OUT_Y_H, 1);

    Y_Axis = (higher << 8) | lower; 

    return  Y_Axis;

}

//////// FUNTION TO READ THE DATA OF THE Z axis data /////////////

int16_t Z_Axiz(void){
    int8_t lower = 0;
    int8_t higher = 0;
    int16_t Z_Axis = 0;
    lower = read_I2C(BUS_REG1, OUT_Z_L, 1);
    higher = read_I2C(BUS_REG1, OUT_Z_H, 1);

    Z_Axis = (higher << 8) | lower; 

    return  Z_Axis;

}


int main(){
    float X_Axis = 0.00f;
    float Y_Axis = 0.00f;
    float Z_Axis = 0.00f;

    while(1){

        //////// Compute the Raw data /////////////

         X_Axis = X_Axiz() / 100.0f; // Divided by 100 for Scaling Purpose
         Y_Axis = Y_Axiz() / 100.0f;
         Z_Axis = Z_Axiz() / 100.0f;

         printf("Value of X-axis, Y-axis, Z-axis %f %f %f \n", X_Axis, Y_Axis, Z_Axis);

         HAL_Delay(1000); // 1 second delay
    }








    return 0;
}