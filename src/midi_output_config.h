#ifndef _MIDI_OUTPUT_CONFIG_H
#define _MIDI_OUTPUT_CONFIG_H

// Port and channels used for the different types of MIDI messages
// possible ports: DEFAULT, USB0, UART0 or UART1

// messages related to the RGB button matrix
#define MATRIX_MIDI_PORT USB0
#define MATRIX_MIDI_CHN  Chn1

// messages related to the analog inputs (linear and rotary potentiometers)
#define ANALOG_MIDI_PORT USB0
#define ANALOG_MIDI_CHN  Chn2

// messages related to the digital inputs (encoders and encoder button presses)
#define DIGITAL_MIDI_PORT USB0
#define DIGITAL_MIDI_CHN  Chn3

#endif
