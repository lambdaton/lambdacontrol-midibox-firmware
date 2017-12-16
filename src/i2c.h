#ifndef _I2C_H
#define _I2C_H

#include <mios32.h>

#include "i2c_config.h"

// sends the payload at the given addr with the specified size
// over I2C to the device at the iic_addr
s32 i2c_send(u8 port, u8 iic_addr, u8 *payload, size_t size);

// reads by size specified bytes via I2C from the desired I2C device
// and stores the returned data inside the read_addr
s32 i2c_receive(u8 port, u8 iic_addr, u8 *read_addr, size_t size);

#endif
