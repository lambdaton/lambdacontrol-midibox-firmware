#include "app.h"

// called after start up
void APP_Init(void)  {
    // initialize all LEDs
    MIOS32_BOARD_LED_Init(0xffffffff);

    MIOS32_IIC_Init(0); //I2C connection is for example used to communicate with the button matrix MCU

    // start processing tasks
    APP_AINSER_Init();
    APP_RGBMatrix_Init();
    APP_ENC_Init(); // rotary encoder processing

    // limit the number of DIN/DOUT SRs which will be scanned for faster scan rate
    MIOS32_SRIO_ScanNumSet(8);
}

// endless background task
void APP_Background(void)  {
    MIOS32_MIDI_SendDebugMessage("LambdaControl started.");
    while(1);
}

// called each ms after scanning the inputs
void APP_Tick(void)  {
    // PWM modulate the status LED (this is a sign of life)
    u32 timestamp = MIOS32_TIMESTAMP_Get();
    MIOS32_BOARD_LED_Set(1, (timestamp % 20) <= ((timestamp / 100) % 10));
}

// called when a MIDI package is received
void APP_MIDI_NotifyPackage(mios32_midi_port_t port, mios32_midi_package_t midi_package)  {
    APP_RGBMatrix_Process_Color_Change_Message(midi_package);
}

//unsued functions from MIOS
void APP_MIDI_Tick(void) {}
void APP_AIN_NotifyChange(u32 pin, u32 pin_value) {}
void APP_SRIO_ServicePrepare(void) {}
void APP_SRIO_ServiceFinish(void) {}
