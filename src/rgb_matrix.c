#include "rgb_matrix.h"

void APP_RGBMatrix_Init(void)  {
    xTaskCreate(TASK_ButtonMatrix_Scan, (const portCHAR *)"ButtonMatrix_Scan", configMINIMAL_STACK_SIZE, NULL, PRIORITY_TASK_BUTTON_MATRIX_SCAN, NULL);
}

void APP_RGBMatrix_Process_Color_Change_Message(mios32_midi_package_t midi_package)  {
    int col = MATRIX_NUM_COLS - 1 - (midi_package.note - 36) % MATRIX_NUM_COLS; //flipping, since (0,0) is in the upper left corner
    int row = MATRIX_NUM_ROWS - 1 - (midi_package.note - 36) / MATRIX_NUM_COLS;

    s32 status = -1;
    while(status < 0)  {
        if(midi_package.type == NoteOn && midi_package.velocity > 0)  {
            MIOS32_MIDI_SendDebugMessage("send light on command.");
            u8 payload[4] = { row, col, 0x01, midi_package.velocity };
            status = i2c_send(IIC_PORT, MATRIX_MCU_IIC_ADDR, &payload[0], sizeof(payload));
        }
        else if((midi_package.type == NoteOff) || (midi_package.type == NoteOn && midi_package.velocity == 0))  {
            MIOS32_MIDI_SendDebugMessage("send light out command.");
            u8 payload[4] = { row, col, 0x00, midi_package.velocity };
            status = i2c_send(IIC_PORT, MATRIX_MCU_IIC_ADDR, &payload[0], sizeof(payload));
        }
        else
            status = 1; //not a package which we need to send via I2C

        if(status < 0)
            MIOS32_MIDI_SendDebugMessage("WARNING: Could not send via I2C.\n");
    }
}

static void TASK_ButtonMatrix_Scan(void *pvParameters)  {
    portTickType xLastExecutionTime;

    // Initialise the xLastExecutionTime variable on task entry
    xLastExecutionTime = xTaskGetTickCount();

    ButtonEvent buttonEvent;
    while(1)  {
        vTaskDelayUntil(&xLastExecutionTime, 50 / portTICK_RATE_MS);

        s32 status;
        if((status = i2c_receive(IIC_PORT, MATRIX_MCU_IIC_ADDR, (u8 *) &buttonEvent, sizeof(buttonEvent))) >= 0)  {
            if(buttonEvent.column != 0xFF) //column is 0xFF when the MCU detected no button press
                APP_RGBMatrix_BUTTON_NotifyToggle(buttonEvent.column, buttonEvent.row, buttonEvent.isPressed);
        }
        else
            MIOS32_MIDI_SendDebugMessage("WARNING: Could not receive via I2C.\n");
    }
}

void APP_RGBMatrix_BUTTON_NotifyToggle(u8 column, u8 row, u8 pressed)  {
    // calculate the note for the given button passed on its row and column
    int matrixButton = (MATRIX_NUM_COLS * row + column);
    int note_number = MATRIX_NUM_BUTTONS - matrixButton + 35;

    // ensure valid note range
    if(note_number > 127)
        note_number = 127;
    else if(note_number < 0)
        note_number = 0;

    int velocity;
    if(pressed)
        velocity = 127;
    else
        velocity = 0;

    MIOS32_MIDI_SendNoteOn(MATRIX_MIDI_PORT, MATRIX_MIDI_CHN, note_number, velocity);
}
