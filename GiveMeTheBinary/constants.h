#ifndef CONSTANTS_H
#define CONSTANTS_H

// Definisci le costanti per i pin dei bottoni
#define B1 5
#define B2 4
#define B3 3
#define B4 2

// Definisci le costanti per i pin dei LED
#define LS 6    // PWM pin
#define L1 11
#define L2 10
#define L3 9
#define L4 8

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