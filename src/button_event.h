#ifndef _BUTTON_EVENT_H
#define _BUTTON_EVENT_H

//represent a button press/depress inside the RGB button matrix
typedef struct {
    u8 column;
    u8 row;
    u8 isPressed;
} ButtonEvent;

#endif
