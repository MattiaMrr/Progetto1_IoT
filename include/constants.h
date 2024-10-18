#ifndef CONSTANTS_H
#define CONSTANTS_H

// Definisci le costanti per i pin dei bottoni
#define BTN1 2
#define BTN2 3
#define BTN3 10
#define BTN4 9

// Definisci le costanti per i pin dei LED
#define LS 8   // PWM pin
#define L1 4
#define L2 5
#define L3 6
#define L4 7

#define POT A0

// Definisci le costanti per gli stati
#define STARTUP 0
#define DEEP_SLEEP 1
#define PREPARE_ROUND 2
#define ROUND 3
#define ROUND_WIN 4
#define GAME_OVER 5

// Definisci le dimensioni degli array
#define BUTTON_COUNT 4
#define LED_COUNT 5

#endif // CONSTANTS_H