#ifndef _RGB_MATRIX_H
#define _RGB_MATRIX_H

#include <mios32.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include "midi_output_config.h"
#include "button_event.h"
#include "i2c.h"

// matrix constants
#define MATRIX_NUM_COLS 10
#define MATRIX_NUM_ROWS 6

// maximum number of supported buttons
#define MATRIX_NUM_BUTTONS (MATRIX_NUM_COLS * MATRIX_NUM_ROWS)
#define MATRIX_NUM_BUTTONS_ROUNDED 64

//0x08 shifted by one to the left (mios specific)
#define MATRIX_MCU_IIC_ADDR 0x10

#define PRIORITY_TASK_BUTTON_MATRIX_SCAN (tskIDLE_PRIORITY + 3)

// communicates with the RGB matrix MCU and asks for new button presses
static void TASK_ButtonMatrix_Scan(void *pvParameters);

// Initialize the task which communicates with the RGB button matrix MCU
void APP_RGBMatrix_Init(void);

// Process the change color messages from Ableton Live
void APP_RGBMatrix_Process_Color_Change_Message(mios32_midi_package_t midi_package);

// called when a RGB matrix button press or depress has been detected
// creates and sends the corresponding MIDI message
void APP_RGBMatrix_BUTTON_NotifyToggle(u8 column, u8 row, u8 pressed);

#endif
