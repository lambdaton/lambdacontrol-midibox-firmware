#ifndef _ENCODERS_H
#define _ENCODERS_H

#include <mios32.h>

#include "midi_output_config.h"

#define NUM_ENCODERS 10

// Initialize the encoders s.t. they trigger the APP_ENC_NotifyChange function
void APP_ENC_Init(void);

// Currently the encoder buttons are our only digital buttons in the hole setup so simply
// overwrite the APP_DIN_NotifyToggle function s.t. it outputs all buttons input on a
// separate MIDI channel
void APP_DIN_NotifyToggle(u32 pin, u32 pin_value);

// an encoder has been moved
// incrementer is positive when encoder has been turned clockwise, else it is negative
void APP_ENC_NotifyChange(u32 encoder, s32 incrementer);

#endif
