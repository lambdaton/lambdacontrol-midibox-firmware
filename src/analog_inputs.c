#include "analog_inputs.h"

void APP_AINSER_Init(void)  {
    // initialize the AINSER module(s)
    AINSER_Init(0);

    xTaskCreate(TASK_AINSER_Scan, (const portCHAR *)"AINSER_Scan", configMINIMAL_STACK_SIZE, NULL, PRIORITY_TASK_AINSER_SCAN, NULL);
}

static void TASK_AINSER_Scan(void *pvParameters)  {
    portTickType xLastExecutionTime;

    // Initialise the xLastExecutionTime variable on task entry
    xLastExecutionTime = xTaskGetTickCount();

    while(1)  {
        vTaskDelayUntil(&xLastExecutionTime, 1 / portTICK_RATE_MS);
        AINSER_Handler(APP_AINSER_NotifyChange);
    }
}

static void APP_AINSER_NotifyChange(u32 module, u32 pin, u32 pin_value)  {
    u8 value_7bit = pin_value >> 5; // convert 12bit value to 7bit value

    value_7bit = ~value_7bit & 0x7f; //invert the value s.t. the lowest position is 0

    MIOS32_MIDI_SendCC(ANALOG_MIDI_PORT, ANALOG_MIDI_CHN, pin + 0x10, value_7bit);
}

