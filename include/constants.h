#ifndef CONSTANTS_H
#define CONSTANTS_H

// Definisci le costanti per i pin dei bottoni
#define BTN1 2
#define BTN2 3
#define BTN3 4
#define BTN4 5

// Definisci le costanti per i pin dei LED
#define LS 6   // PWM pin
#define L1 8
#define L2 9
#define L3 10
#define L4 11

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
#define LED_COUNT 4

#endif // CONSTANTS_H