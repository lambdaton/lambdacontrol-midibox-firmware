#include "encoders.h"

void APP_ENC_Init(void)  {
    // initialize rotary encoders of the same type (DETENTED2)
    int enc;
    for(enc=0; enc < NUM_ENCODERS; ++enc)  {
        u8 pin_sr = enc >> 2; // each DIN SR has 4 encoders connected
        u8 pin_pos = (enc & 0x3) << 1; // Pin position of first ENC channel: either 0, 2, 4 or 6

        mios32_enc_config_t enc_config = MIOS32_ENC_ConfigGet(enc);
        enc_config.cfg.type = DETENTED3; // see mios32_enc.h for available types
        enc_config.cfg.sr = pin_sr + 1; //first DIN SR is 1!
        enc_config.cfg.pos = pin_pos;
        enc_config.cfg.speed = NORMAL;
        enc_config.cfg.speed_par = 0;
        MIOS32_ENC_ConfigSet(enc, enc_config);
    }
}

void APP_DIN_NotifyToggle(u32 pin, u32 pin_value)  {
    MIOS32_MIDI_SendNoteOn(DIGITAL_MIDI_PORT, DIGITAL_MIDI_CHN, pin & 0x7f, pin_value ? 0x00 : 0x7f);
}

void APP_ENC_NotifyChange(u32 encoder, s32 incrementer)  {
    // special treatmeant for the encoder at the master fader
    // send button presses instead of enc values
    // s.t. we can use it to scroll up and down in the clip list
    if(encoder == 0)  {
        u8 note = 1; // one note for up; one for down
        if(incrementer < 0)
            note = 0;
        MIOS32_MIDI_SendNoteOn(DIGITAL_MIDI_PORT, DIGITAL_MIDI_CHN, note, 0x7f); //on
        MIOS32_MIDI_SendNoteOn(DIGITAL_MIDI_PORT, DIGITAL_MIDI_CHN, note, 0x00); //off
    }
    else  {
        int value = 64 + incrementer; // determine relative value: 64 +/- <incrementer>
        if(value < 0) // ensure that value is in range of 0..127
            value = 0;
        else if(value > 127)
            value = 127;

        MIOS32_MIDI_SendCC(DIGITAL_MIDI_PORT, DIGITAL_MIDI_CHN, encoder, value);
    }
}

