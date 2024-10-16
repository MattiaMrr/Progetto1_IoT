#ifndef BUTTONS_CONTROLLER_H
#define BUTTONS_CONTROLLER_H

#include "constants.h"

extern const int buttonPins[];
extern int lastButtonState[BUTTON_COUNT];

// Inizializza i bottoni
void initButtons();

// Gestisce la pressione dei bottoni, chiamata dagli interrupt.
// ...

// Toglie il bounce dei bottoni.
// ...

#endif // BUTTONS_CONTROLLER_H