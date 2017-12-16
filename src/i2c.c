#include "i2c.h"

//used to send the received color information to the matrix MCU
s32 i2c_send(u8 port, u8 iic_addr, u8 *payload, size_t size)  {
    s32 status;

    if((status=MIOS32_IIC_TransferBegin(port, IIC_Blocking)) < 0)
        MIOS32_MIDI_SendDebugMessage("IIC%d: MIOS32_IIC_TransferBegin failed with %d!\n", port, status);
    else {
        if( (status=MIOS32_IIC_Transfer(port, IIC_Write, iic_addr, payload, size)) < 0 )
            MIOS32_MIDI_SendDebugMessage("IIC%d: MIOS32_IIC_Transfer failed with %d!\n", port, status);
        else {
            if( (status=MIOS32_IIC_TransferWait(port)) < 0 )
                MIOS32_MIDI_SendDebugMessage("IIC%d: MIOS32_IIC_TransferWait failed with %d!\n", port, status);
            else
                MIOS32_IIC_TransferFinished(port);
        }
    }

    return status;
}

// reads by size specified bytes via I2C from the desired I2C device
// and stores the returned data inside the read_addr
s32 i2c_receive(u8 port, u8 iic_addr, u8 *read_addr, size_t size)  {
    s32 status;

    if((status=MIOS32_IIC_TransferBegin(port, IIC_Blocking)) < 0)
        MIOS32_MIDI_SendDebugMessage("IIC%d: MIOS32_IIC_TransferBegin failed with %d!\n", port, status);
    else {
        if((status=MIOS32_IIC_Transfer(port, IIC_Read, iic_addr, (u8 *) read_addr, size)) < 0)
            MIOS32_MIDI_SendDebugMessage("IIC%d: MIOS32_IIC_Transfer failed with %d!\n", port, status);
        else {
            if((status=MIOS32_IIC_TransferWait(port)) < 0)
                MIOS32_MIDI_SendDebugMessage("IIC%d: MIOS32_IIC_TransferWait failed with %d!\n", port, status);
            else
                MIOS32_IIC_TransferFinished(port);
        }
    }

    return status;
}
