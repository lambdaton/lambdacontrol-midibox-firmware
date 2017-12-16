#ifndef _ANALOG_INPUTS_H
#define _ANALOG_INPUTS_H

#include <mios32.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <ainser.h>

#include "midi_output_config.h"

// define priority level for AINSER_SCAN task:
// use same priority as MIOS32 specific tasks (3)
#define PRIORITY_TASK_AINSER_SCAN (tskIDLE_PRIORITY + 3)

static void TASK_AINSER_Scan(void *pvParameters); //pots and faders

// Initialize the analog input processing
void APP_AINSER_Init(void);

// called when an analog input has been moved
static void APP_AINSER_NotifyChange(u32 module, u32 pin, u32 pin_value);

#endif
