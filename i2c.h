#ifndef I2C_HEADER_H
#define I2C_HEADER_H

#include <stdint.h>
#include <stddef.h>

typedef enum {
    STATUS_OK = 0U,
    STATUS_ERROR
} status_t;

int i2c_write(uint8_t bus_address, uint8_t register_address, const uint8_t* data, size_t length);

int8_t read_I2C(uint8_t bus_address, uint8_t register_address, size_t length);

#endif